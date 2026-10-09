#pragma once

#include <QMainWindow>
#include <QMap>
#include <QString>
#include "orderbookwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class OrderBookManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void openOrderBookWindow(const QString &symbol);
    void onThrottleChanged(int ms);

private:
    void setupConnections();
    void populateSymbolMenu();

    Ui::MainWindow *ui = nullptr;
    OrderBookManager *m_manager = nullptr;
    QMap<QString, OrderBookWindow*> m_windows;
};

