#include "orderbookmanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

OrderBookManager::OrderBookManager(QObject *parent)
    : QObject(parent)
{
    connect(&timer, &QTimer::timeout, this, &OrderBookManager::processNextRecord);
}

bool OrderBookManager::loadFromCsv(const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList fields = line.split(",");
        records.append(TbtRecord(fields));
    }

    qDebug() << "Loaded" << records.size() << "records.";
    return true;
}

void OrderBookManager::setUpdateInterval(int ms) {
    if (ms == 0) {
        timer.stop();
    } else {
        timer.start(ms);
    }
}

void OrderBookManager::processNextRecord() {
    if (currentIndex >= records.size()) {
        timer.stop();
        return;
    }

    const auto &rec = records[currentIndex++];
    books[rec.symbol].applyRecord(rec);

    auto bids = books[rec.symbol].getBids();
    auto asks = books[rec.symbol].getAsks();

    emit orderBookUpdated(rec.symbol, bids, asks);
}
QStringList OrderBookManager::getSymbols(){
    QSet<QString> lset_Symbols;
    for(auto &it:records){
        lset_Symbols.insert(it.symbol);
    }
    return lset_Symbols.values();
}
