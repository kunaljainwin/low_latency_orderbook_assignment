#include "orderbookmodel.h"
#include <QBrush>

OrderBookModel::OrderBookModel(const QStringList &headers, QObject *parent, bool isBid)
    : QAbstractTableModel(parent),
    headers(headers),
    isBidModel(isBid)
{
}

int OrderBookModel::rowCount(const QModelIndex &) const
{
    return tableData.size();
}

int OrderBookModel::columnCount(const QModelIndex &) const
{
    return headers.size();
}

QVariant OrderBookModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= tableData.size() || index.column() >= headers.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return tableData[index.row()][index.column()];

    if (role == Qt::ForegroundRole) {
        // Color text: blue for bids, red for asks
        return QBrush(isBidModel ? Qt::blue : Qt::red);
    }
    if (role == Qt::TextAlignmentRole)
        return QVariant(int(Qt::AlignRight | Qt::AlignVCenter));  // Left align horizontally, center vertically


    return QVariant();
}

QVariant OrderBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];

    return QVariant();
}

void OrderBookModel::setData(const QList<QPair<double, MarketDepth>> &dataList)
{
    // If no new data, keep the previous tableData
    if (dataList.isEmpty())
        return;

    beginResetModel();
    tableData.clear();

    for (const auto &entry : dataList) {
        QList<QVariant> row;
        row << entry.second.orderCount()
            << entry.first              // price
            << entry.second.volume();   // qty
        tableData.append(row);
    }

    endResetModel();
}
