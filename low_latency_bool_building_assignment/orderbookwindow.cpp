#include "orderbookwindow.h"
#include <QTableWidgetItem>

OrderBookWindow::OrderBookWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderBookWindow)
{
    ui->setupUi(this);

    //configure table headers
    ui->tableBids->setColumnCount(3);
    ui->tableBids->setHorizontalHeaderLabels(QStringList() << "Total Orders" << "Buy Price" << "Buy Qty");
    ui->tableBids->verticalHeader()->setVisible(false);

    ui->tableAsks->setColumnCount(3);
    ui->tableAsks->setHorizontalHeaderLabels(QStringList() << "Total Orders" << "Sell Price" << "Sell Qty");
    ui->tableBids->verticalHeader()->setVisible(false);
}

OrderBookWindow::~OrderBookWindow()
{
    delete ui;
}

void OrderBookWindow::setSymbol(const QString &s)
{
    symbol = s;
    setWindowTitle("Order Book: " + symbol);
    qDebug() << "Setting symbol:" << s;

}

void OrderBookWindow::updateOrderBook(const QList<QPair<double,MarketDepth>> &bids,
                                      const QList<QPair<double,MarketDepth>> &asks)
{
    // Only update if this window is for the symbol
    if (symbol.isEmpty()) return;

    // Update Bids table
    ui->tableBids->setRowCount(bids.size());
    for (int i = 0; i < bids.size(); ++i) {
        ui->tableBids->setItem(i, 0, new QTableWidgetItem(QString::number(bids[i].second.orderCount())));
        ui->tableBids->setItem(i, 1, new QTableWidgetItem(QString::number(bids[i].first, 'f', 2)));
        ui->tableBids->setItem(i, 2, new QTableWidgetItem(QString::number(bids[i].second.volume())));
    }

    // Update Asks table
    ui->tableAsks->setRowCount(asks.size());
    for (int i = 0; i < asks.size(); ++i) {
        ui->tableAsks->setItem(i, 0, new QTableWidgetItem(QString::number(asks[i].second.orderCount())));
        ui->tableAsks->setItem(i, 1, new QTableWidgetItem(QString::number(asks[i].first, 'f', 2)));
        ui->tableAsks->setItem(i, 2, new QTableWidgetItem(QString::number(asks[i].second.volume())));
    }
}
