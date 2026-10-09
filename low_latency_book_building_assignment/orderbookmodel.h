#pragma once

#include <QAbstractTableModel>
#include <QStringList>
#include "marketdepth.h"

class OrderBookModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit OrderBookModel(const QStringList &headers, QObject *parent = nullptr, bool isBid = true);

    void setData(const QList<QPair<double, MarketDepth>> &data);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QStringList m_headers;
    QList<QPair<double, MarketDepth>> m_rows;
    bool m_isBidModel;
};

