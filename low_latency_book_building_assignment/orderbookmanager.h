#pragma once

#include <QObject>
#include <QMap>
#include <QList>
#include <QPair>
#include <QStringList>
#include <QTimer>
#include "orderbook.h"
#include "tbtrecord.h"

class OrderBookManager : public QObject {
    Q_OBJECT
public:
    explicit OrderBookManager(QObject *parent = nullptr);

    bool loadFromCsv(const QString &path);
    void setUpdateInterval(int ms);
    QStringList getSymbols() const;

    int totalRecords() const { return m_records.size(); }
    int currentIndex() const { return m_currentIndex; }
    void reset();

signals:
    void orderBookUpdated(const QString &symbol,
                          const QList<QPair<double, MarketDepth>> &bids,
                          const QList<QPair<double, MarketDepth>> &asks);

private slots:
    void processNextRecord();

private:
    QList<TbtRecord> m_records;
    QMap<QString, OrderBook> m_books;
    QStringList m_symbols;
    int m_currentIndex = 0;
    QTimer m_timer;
};

