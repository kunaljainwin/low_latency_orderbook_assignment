#include "orderbookwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>

OrderBookWindow::OrderBookWindow(QWidget *parent)
    : QWidget(parent)
{
    // Create table views
    bidsView = new QTableView(this);
    asksView = new QTableView(this);

    // Create models
    bidsModel = new OrderBookModel(QStringList()<<"Total Orders" << "Buy Price" << "Buy Qty",this,true);
    asksModel = new OrderBookModel(QStringList()<<"Total Orders" << "Sell Price" << "Sell Qty",this,false);

    bidsView->setModel(bidsModel);
    asksView->setModel(asksModel);

    // Disable editing
    bidsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    asksView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Stretch columns
    bidsView->horizontalHeader()->setStretchLastSection(true);
    asksView->horizontalHeader()->setStretchLastSection(true);

    // Bottom labels for totals and timestamp
    totalBuyLabel = new QLabel("Total Buy Qty: 0", this);
    totalSellLabel = new QLabel("Total Sell Qty: 0", this);
    lastUpdatedLabel = new QLabel("Last Updated at: --:--:--", this);

    QHBoxLayout *tablesLayout = new QHBoxLayout();
    tablesLayout->addWidget(bidsView);
    tablesLayout->addWidget(asksView);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(totalBuyLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(totalSellLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(lastUpdatedLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(tablesLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setMinimumSize(800, 400);  // width = 800, height = 400
}

void OrderBookWindow::setSymbol(const QString &s)
{
    symbol = s;
    setWindowTitle("OB:" + symbol + "_NSE");
}

void OrderBookWindow::updateOrderBook(const QList<QPair<double, MarketDepth>> &bids,
                                      const QList<QPair<double, MarketDepth>> &asks)
{
    if (symbol.isEmpty()) return;

    // ✅ Only update if new data is available; else keep old snapshot
    if (!bids.isEmpty())
        bidsModel->setData(bids);

    if (!asks.isEmpty())
        asksModel->setData(asks);

    // Update total quantities
    double totalBuy = 0;
    for (auto &b : bids) totalBuy += b.second.volume();
    totalBuyLabel->setText(QString("Total Buy Qty: %1").arg(totalBuy));

    double totalSell = 0;
    for (auto &a : asks) totalSell += a.second.volume();
    totalSellLabel->setText(QString("Total Sell Qty: %1").arg(totalSell));

    // Update timestamp
    lastUpdatedLabel->setText("Last Updated at: " + QDateTime::currentDateTime().toString("hh:mm:ss"));
}
