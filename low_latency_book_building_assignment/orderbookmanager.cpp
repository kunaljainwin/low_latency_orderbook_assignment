#include "orderbookmanager.h"
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QSet>
#include <QDebug>

OrderBookManager::OrderBookManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &OrderBookManager::processNextRecord);
}

bool OrderBookManager::loadFromCsv(const QString &path) {
    const QStringList candidatePaths = {
        path,
        "Dummy_TBT.csv",
        "./Dummy_TBT.csv",
        "../Dummy_TBT.csv",
        "../../Dummy_TBT.csv",
        QCoreApplication::applicationDirPath() + "/Dummy_TBT.csv",
        QCoreApplication::applicationDirPath() + "/../Dummy_TBT.csv"
    };

    QString resolvedPath;
    for (const QString &candidate : candidatePaths) {
        if (!candidate.trimmed().isEmpty() && QFileInfo::exists(candidate)) {
            resolvedPath = candidate;
            break;
        }
    }

    if (resolvedPath.isEmpty()) {
        qWarning() << "OrderBookManager: CSV file not found in search paths, initial path:" << path;
        return false;
    }

    QFile file(resolvedPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "OrderBookManager: Failed to open file:" << resolvedPath;
        return false;
    }

    reset();

    QSet<QString> uniqueSymbols;
    QTextStream in(&file);
    bool firstLine = true;

    while (!in.atEnd()) {
        const QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }

        const QStringList fields = line.split(',');
        if (firstLine) {
            firstLine = false;
            // Check if this is a header row
            if (!fields.isEmpty() && fields.at(0).trimmed().compare("Symbol", Qt::CaseInsensitive) == 0) {
                continue;
            }
        }

        TbtRecord rec(fields);
        if (rec.isValid()) {
            m_records.append(rec);
            uniqueSymbols.insert(rec.symbol);
        }
    }

    m_symbols = uniqueSymbols.values();
    m_symbols.sort();

    qInfo() << "OrderBookManager: Successfully loaded" << m_records.size()
            << "records across" << m_symbols.size() << "symbols from" << resolvedPath;
    return true;
}

void OrderBookManager::setUpdateInterval(int ms) {
    if (ms <= 0) {
        m_timer.stop();
    } else {
        m_timer.start(ms);
    }
}

void OrderBookManager::processNextRecord() {
    if (m_records.isEmpty()) {
        m_timer.stop();
        return;
    }

    if (m_currentIndex >= m_records.size()) {
        // Continuous replay: restart stream from beginning so ticks keep flowing
        m_currentIndex = 0;
        m_books.clear();
    }

    const auto &rec = m_records.at(m_currentIndex++);
    auto &book = m_books[rec.symbol];
    book.applyRecord(rec);

    const auto bids = book.getBids();
    const auto asks = book.getAsks();

    emit orderBookUpdated(rec.symbol, bids, asks);
}

QList<QPair<double, MarketDepth>> OrderBookManager::getBids(const QString &symbol) const {
    auto it = m_books.constFind(symbol);
    if (it != m_books.constEnd()) {
        return it.value().getBids();
    }
    return {};
}

QList<QPair<double, MarketDepth>> OrderBookManager::getAsks(const QString &symbol) const {
    auto it = m_books.constFind(symbol);
    if (it != m_books.constEnd()) {
        return it.value().getAsks();
    }
    return {};
}

QStringList OrderBookManager::getSymbols() const {
    return m_symbols;
}

void OrderBookManager::reset() {
    m_timer.stop();
    m_records.clear();
    m_books.clear();
    m_symbols.clear();
    m_currentIndex = 0;
}


