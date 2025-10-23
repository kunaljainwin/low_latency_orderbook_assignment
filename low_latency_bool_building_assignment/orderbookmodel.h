#pragma once
#include <QAbstractTableModel>
#include "marketdepth.h"

class OrderBookModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit OrderBookModel(const QStringList &headers, QObject *parent = nullptr, bool isBid = true);

    void setData(const QList<QPair<double, MarketDepth>> &data);
    int rowCount(const QModelIndex &parent = {}) const override;
    int columnCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QList<QPair<double, MarketDepth>> rows;
    QStringList headers;
    QList<QList<QVariant>> tableData;
    bool isBidModel;
};
