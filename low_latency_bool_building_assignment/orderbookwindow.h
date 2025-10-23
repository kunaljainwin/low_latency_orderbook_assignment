#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include "orderbookmodel.h"
#include "marketdepth.h"

class OrderBookWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OrderBookWindow(QWidget *parent = nullptr);
    void setSymbol(const QString &s);
    void updateOrderBook(const QList<QPair<double, MarketDepth>> &bids,
                         const QList<QPair<double, MarketDepth>> &asks);

private:
    QString symbol;
    QTableView *bidsView;
    QTableView *asksView;
    OrderBookModel *bidsModel;
    OrderBookModel *asksModel;

    QLabel *totalBuyLabel;
    QLabel *totalSellLabel;
    QLabel *lastUpdatedLabel;
};
