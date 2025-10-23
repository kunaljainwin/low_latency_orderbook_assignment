#include "bookmanager.h"
#include <QDebug>

BookManager::BookManager(QObject *parent) : QObject(parent) {}

void BookManager::processRecord(const TbtRecord &r) {
    auto &book = m_books[r.symbol];
    QMap<double, qint64> *sideMap = (r.side == 'B') ? &book.bids : &book.asks;

    if (r.instruction == "INSERT") {
        (*sideMap)[r.price] += r.size;
    } else if (r.instruction == "REMOVE") {
        sideMap->remove(r.price);
    }

    emit bookUpdated(r.symbol);
}

const QMap<double, qint64> &BookManager::bids(const QString &symbol) const {
    return m_books[symbol].bids;
}

const QMap<double, qint64> &BookManager::asks(const QString &symbol) const {
    return m_books[symbol].asks;
}
