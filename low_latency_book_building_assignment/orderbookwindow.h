#pragma once

#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QList>
#include <QPair>
#include <QString>
#include "orderbookmodel.h"
#include "marketdepth.h"

class OrderBookWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OrderBookWindow(QWidget *parent = nullptr);

    void setSymbol(const QString &symbol);
    QString symbol() const { return m_symbol; }

    void updateOrderBook(const QList<QPair<double, MarketDepth>> &bids,
                         const QList<QPair<double, MarketDepth>> &asks);

private:
    void setupUi();
    void configureTableView(QTableView *view, OrderBookModel *model);

    QString m_symbol;
    QTableView *m_bidsView = nullptr;
    QTableView *m_asksView = nullptr;
    OrderBookModel *m_bidsModel = nullptr;
    OrderBookModel *m_asksModel = nullptr;

    QLabel *m_totalBuyLabel = nullptr;
    QLabel *m_totalSellLabel = nullptr;
    QLabel *m_lastUpdatedLabel = nullptr;
};

