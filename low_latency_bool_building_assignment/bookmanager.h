#ifndef ORDERBOOKMANAGER_H
#define ORDERBOOKMANAGER_H

#include <QObject>
#include <QMap>
#include <QTimer>
#include "orderbook.h"
#include "tbtrecord.h"

class OrderBookManager : public QObject {
    Q_OBJECT
public:
    explicit OrderBookManager(QObject *parent = nullptr);

    // Load CSV into memory
    bool loadFromCsv(const QString &path);

    // Set update interval: 0 = real-time, >0 = throttled (ms)
    void setUpdateInterval(int ms);

signals:
    // Signal to update UI: symbol + current bids/asks
    void orderBookUpdated(const QString &symbol,
                          QList<QPair<double, qint64>> bids,
                          QList<QPair<double, qint64>> asks);

private slots:
    void processNextRecord();

private:
    QList<TbtRecord> records;         // All CSV records
    QMap<QString, OrderBook> books;   // Order book per symbol
    int currentIndex = 0;             // Processing index
    QTimer timer;                     // Throttle timer
};

#endif // ORDERBOOKMANAGER_H
