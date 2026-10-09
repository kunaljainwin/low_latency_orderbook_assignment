#include "orderbookwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDateTime>
#include <QLocale>

namespace {
constexpr int MIN_WINDOW_WIDTH = 800;
constexpr int MIN_WINDOW_HEIGHT = 450;
}

OrderBookWindow::OrderBookWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void OrderBookWindow::configureTableView(QTableView *view, OrderBookModel *model)
{
    view->setModel(model);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setAlternatingRowColors(true);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->horizontalHeader()->setStretchLastSection(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->verticalHeader()->setVisible(false);
}

void OrderBookWindow::setupUi()
{
    m_bidsView = new QTableView(this);
    m_asksView = new QTableView(this);

    m_bidsModel = new OrderBookModel(QStringList() << "Orders" << "Buy Price" << "Buy Qty", this, true);
    m_asksModel = new OrderBookModel(QStringList() << "Orders" << "Sell Price" << "Sell Qty", this, false);

    configureTableView(m_bidsView, m_bidsModel);
    configureTableView(m_asksView, m_asksModel);

    m_totalBuyLabel = new QLabel("Total Buy Qty: 0", this);
    m_totalSellLabel = new QLabel("Total Sell Qty: 0", this);
    m_lastUpdatedLabel = new QLabel("Last Updated: --:--:--", this);

    QHBoxLayout *tablesLayout = new QHBoxLayout();
    tablesLayout->addWidget(m_bidsView);
    tablesLayout->addWidget(m_asksView);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addWidget(m_totalBuyLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_totalSellLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_lastUpdatedLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(tablesLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setMinimumSize(MIN_WINDOW_WIDTH, MIN_WINDOW_HEIGHT);
}

void OrderBookWindow::setSymbol(const QString &symbol)
{
    m_symbol = symbol;
    setWindowTitle("OB: " + m_symbol + " [NSE Depth]");
}

void OrderBookWindow::updateOrderBook(const QList<QPair<double, MarketDepth>> &bids,
                                      const QList<QPair<double, MarketDepth>> &asks)
{
    if (m_symbol.isEmpty()) {
        return;
    }

    m_bidsModel->setData(bids);
    m_asksModel->setData(asks);

    qint64 totalBuy = 0;
    for (const auto &b : bids) {
        totalBuy += b.second.volume();
    }

    qint64 totalSell = 0;
    for (const auto &a : asks) {
        totalSell += a.second.volume();
    }

    const QLocale locale;
    m_totalBuyLabel->setText("Total Buy Qty: " + locale.toString(totalBuy));
    m_totalSellLabel->setText("Total Sell Qty: " + locale.toString(totalSell));
    m_lastUpdatedLabel->setText("Last Updated: " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
}

