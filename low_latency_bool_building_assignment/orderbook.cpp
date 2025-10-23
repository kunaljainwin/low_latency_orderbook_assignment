#include "orderbook.h"

void OrderBook::applyRecord(const TbtRecord &rec) {
    auto &book = (rec.side == 'B') ? bids : asks;

    if (rec.instruction == "INSERT") {
        if (book.contains(rec.price))
        {
            qint64 lcurrOrderCount=book[rec.price].volume();
            book[rec.price].setVolume(lcurrOrderCount+rec.size);
        }
        else{
            book.insert(rec.price,MarketDepth(1,rec.size));
        }
    } else if (rec.instruction == "REMOVE") {
        book.remove(rec.price);
    }
}

QList<QPair<double, MarketDepth>> OrderBook::getBids() const {
    QList<QPair<double, MarketDepth>> list;
    auto it = bids.constEnd();
    while (it != bids.constBegin()) {
        --it;
        list.append(qMakePair(it.key(), it.value()));
    }
    return list;
}

QList<QPair<double, MarketDepth>> OrderBook::getAsks() const {
    QList<QPair<double, MarketDepth>> list;
    for (auto it = asks.constBegin(); it != asks.constEnd(); ++it)
        list.append(qMakePair(it.key(), it.value()));
    return list;
}
