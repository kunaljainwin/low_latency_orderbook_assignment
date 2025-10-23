#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "orderbookmanager.h"
#include "orderbookwindow.h"
#include <QAction>
#include <QMenu>
#include <QDebug>

static OrderBookManager *gManager = nullptr;

// Define static member
QMap<QString, OrderBookWindow*> MainWindow::windows;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize OrderBookManager
    gManager = new OrderBookManager(this);
    gManager->loadFromCsv("../../Dummy_TBT.csv");
    gManager->setUpdateInterval(50); // 50 ms throttle for demo

    // Example symbols (could be loaded dynamically from CSV)
    QStringList symbols = {};
    symbols = gManager->getSymbols();
    for (const QString &sym : symbols) {
        QAction *action = new QAction(sym, this);
        ui->menuOrderBool->addAction(action);

        // Use a lambda to safely pass symbol
        connect(action, &QAction::triggered, this, [this, sym]() {
            openOrderBookWindow(sym);
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    for(auto &it:windows){
        delete it;
    }
    // Safely delete all open order book windows
    qDeleteAll(windows);
    windows.clear();
}

void MainWindow::openOrderBookWindow(const QString &symbol)
{
    // Create window if it does not exist
    if (!windows.contains(symbol)) {
        auto w = new OrderBookWindow(nullptr);
        w->setSymbol(symbol);
        windows[symbol] = w;
        // Connect manager updates to this window
        connect(gManager, &OrderBookManager::orderBookUpdated,
                w, [w, symbol](const QString &s,
                            const QList<QPair<double,MarketDepth>> &bids,
                            const QList<QPair<double,MarketDepth>> &asks) {
                    if (s == symbol) {
                        w->updateOrderBook(bids, asks);
                    }
                });
    }

    // Show window safely
    if (windows[symbol]) {
        windows[symbol]->show();
        windows[symbol]->raise();
        windows[symbol]->activateWindow();
    }
}

void MainWindow::throttleChanged(int ms)
{
    if (gManager)
        gManager->setUpdateInterval(ms); // update the OrderBookManager throttle
}
