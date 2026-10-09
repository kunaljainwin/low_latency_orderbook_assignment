#include "orderbookmodel.h"
#include <QBrush>
#include <QColor>

namespace {
constexpr int COL_ORDER_COUNT = 0;
constexpr int COL_PRICE = 1;
constexpr int COL_VOLUME = 2;
}

OrderBookModel::OrderBookModel(const QStringList &headers, QObject *parent, bool isBid)
    : QAbstractTableModel(parent),
      m_headers(headers),
      m_isBidModel(isBid)
{
}

int OrderBookModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_rows.size();
}

int OrderBookModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_headers.size();
}

QVariant OrderBookModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_rows.size() || index.column() >= m_headers.size()) {
        return QVariant();
    }

    const auto &entry = m_rows.at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case COL_ORDER_COUNT:
            return entry.second.orderCount();
        case COL_PRICE:
            return QString::number(entry.first, 'f', 2);
        case COL_VOLUME:
            return entry.second.volume();
        default:
            return QVariant();
        }
    }

    if (role == Qt::ForegroundRole) {
        return QBrush(m_isBidModel ? QColor(0, 114, 206) : QColor(220, 38, 38));
    }

    if (role == Qt::TextAlignmentRole) {
        return QVariant(int(Qt::AlignRight | Qt::AlignVCenter));
    }

    return QVariant();
}

QVariant OrderBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section < m_headers.size()) {
        return m_headers.at(section);
    }
    return QVariant();
}

void OrderBookModel::setData(const QList<QPair<double, MarketDepth>> &dataList)
{
    beginResetModel();
    m_rows = dataList;
    endResetModel();
}

void OrderBookModel::clear()
{
    beginResetModel();
    m_rows.clear();
    endResetModel();
}

