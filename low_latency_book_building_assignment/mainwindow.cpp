#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "orderbookmanager.h"
#include <QAction>
#include <QDebug>

namespace {
constexpr int DEFAULT_THROTTLE_MS = 50;
constexpr int MIN_THROTTLE_MS = 0;
constexpr int MAX_THROTTLE_MS = 1000;
constexpr int THROTTLE_STEP_MS = 5;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_manager(new OrderBookManager(this))
{
    ui->setupUi(this);

    m_manager->loadFromCsv("Dummy_TBT.csv");

    setupConnections();
    populateSymbolMenu();

    // Start with default throttle
    m_manager->setUpdateInterval(DEFAULT_THROTTLE_MS);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_windows);
    m_windows.clear();
}

void MainWindow::setupConnections()
{
    ui->throttleSpinBox->setRange(MIN_THROTTLE_MS, MAX_THROTTLE_MS);
    ui->throttleSpinBox->setSingleStep(THROTTLE_STEP_MS);
    ui->throttleSpinBox->setValue(DEFAULT_THROTTLE_MS);
    ui->throttleSpinBox->setSuffix(" ms");
    ui->throttleSpinBox->setKeyboardTracking(true);

    connect(ui->throttleSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onThrottleChanged);
}

void MainWindow::populateSymbolMenu()
{
    const QStringList symbols = m_manager->getSymbols();
    for (const QString &symbol : symbols) {
        QAction *action = new QAction(symbol, this);
        ui->menuOrderBook->addAction(action);

        connect(action, &QAction::triggered, this, [this, symbol]() {
            openOrderBookWindow(symbol);
        });
    }
}

void MainWindow::openOrderBookWindow(const QString &symbol)
{
    if (symbol.isEmpty()) {
        return;
    }

    OrderBookWindow *window = m_windows.value(symbol, nullptr);
    if (!window) {
        window = new OrderBookWindow(nullptr);
        window->setSymbol(symbol);
        m_windows.insert(symbol, window);

        connect(m_manager, &OrderBookManager::orderBookUpdated,
                window, [window, symbol](const QString &sym,
                                         const QList<QPair<double, MarketDepth>> &bids,
                                         const QList<QPair<double, MarketDepth>> &asks) {
                    if (sym == symbol) {
                        window->updateOrderBook(bids, asks);
                    }
                });
    }

    window->show();
    window->raise();
    window->activateWindow();
}

void MainWindow::onThrottleChanged(int ms)
{
    if (m_manager) {
        m_manager->setUpdateInterval(ms);
        qInfo() << "MainWindow: Throttle interval updated to" << ms << "ms";
    }
}

