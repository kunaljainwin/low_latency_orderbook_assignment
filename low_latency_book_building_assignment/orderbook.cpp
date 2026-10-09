#include "orderbook.h"

void OrderBook::applyRecord(const TbtRecord &rec) {
    if (!rec.isValid()) {
        return;
    }

    auto &book = (rec.side == OrderSide::Buy) ? m_bids : m_asks;

    if (rec.instruction == OrderInstruction::Insert) {
        auto it = book.find(rec.price);
        if (it != book.end()) {
            it.value().addLevel(rec.size, 1);
        } else {
            book.insert(rec.price, MarketDepth(1, rec.size));
        }
    } else if (rec.instruction == OrderInstruction::Remove) {
        book.remove(rec.price);
    }
}

QList<QPair<double, MarketDepth>> OrderBook::getBids() const {
    QList<QPair<double, MarketDepth>> list;
    list.reserve(m_bids.size());

    // Descending order for bids (highest price first)
    auto it = m_bids.constEnd();
    while (it != m_bids.constBegin()) {
        --it;
        list.append(qMakePair(it.key(), it.value()));
    }
    return list;
}

QList<QPair<double, MarketDepth>> OrderBook::getAsks() const {
    QList<QPair<double, MarketDepth>> list;
    list.reserve(m_asks.size());

    // Ascending order for asks (lowest price first)
    for (auto it = m_asks.constBegin(); it != m_asks.constEnd(); ++it) {
        list.append(qMakePair(it.key(), it.value()));
    }
    return list;
}

void OrderBook::clear() {
    m_bids.clear();
    m_asks.clear();
}
