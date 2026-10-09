#pragma once

#include <QMap>
#include <QList>
#include <QPair>
#include "tbtrecord.h"
#include "marketdepth.h"

class OrderBook {
public:
    void applyRecord(const TbtRecord &rec);

    QList<QPair<double, MarketDepth>> getBids() const; // Descending by price
    QList<QPair<double, MarketDepth>> getAsks() const; // Ascending by price

    void clear();

private:
    QMap<double, MarketDepth> m_bids; // Ascending internally by price
    QMap<double, MarketDepth> m_asks; // Ascending internally by price
};

