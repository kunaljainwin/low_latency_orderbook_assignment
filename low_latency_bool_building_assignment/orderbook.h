#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <QMap>
#include <QList>
#include <QPair>
#include "tbtrecord.h"
#include "marketdepth.h"

class OrderBook {
public:
    void applyRecord(const TbtRecord &rec);

    QList<QPair<double, MarketDepth>> getBids() const; // Will return descending
    QList<QPair<double, MarketDepth>> getAsks() const; // Already ascending

private:
    QMap<double, MarketDepth> bids; // ascending internally
    QMap<double, MarketDepth> asks; // ascending
};

#endif // ORDERBOOK_H
