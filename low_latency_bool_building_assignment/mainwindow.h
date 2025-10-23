#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "orderbookwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openOrderBookWindow(const QString &symbol);
    void throttleChanged(int ms);

private:
    Ui::MainWindow *ui;
    static QMap<QString, OrderBookWindow*> windows; // symbol -> window map
};

#endif // MAINWINDOW_H
