#ifndef ORDERBOOKWINDOW_H
#define ORDERBOOKWINDOW_H

#include <QWidget>
#include <QList>
#include <QPair>
#include <QString>
#include "ui_orderbookwindow.h"
#include "marketdepth.h"
class OrderBookWindow : public QWidget
{
    Q_OBJECT
public:
    explicit OrderBookWindow(QWidget *parent = nullptr);
    ~OrderBookWindow();

    void setSymbol(const QString &symbol); // assign which symbol this window is for
    void updateOrderBook(const QList<QPair<double,MarketDepth>> &bids,
                         const QList<QPair<double,MarketDepth>> &asks);

private:
    Ui::OrderBookWindow *ui;
    QString symbol;
};

#endif // ORDERBOOKWINDOW_H
