#include "resultlistmodel.h"

ResultListModel::ResultListModel(ListItem *prototype, QObject *parent) :
    QAbstractListModel(parent), prototype_(prototype) {}

int ResultListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return dataList_.size();
}

QVariant ResultListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= dataList_.size())
        return QVariant();
    return dataList_.at(index.row())->data(role);
}

QHash<int, QByteArray> ResultListModel::roleNames() const
{
    return prototype_->roleNames();
}

ResultListModel::~ResultListModel()
{
    delete prototype_;
    clear();
}

void ResultListModel::appendRow(ListItem *item)
{
    appendRows(QList<ListItem*>() << item);
}

void ResultListModel::appendRows(const QList<ListItem *> &items)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount()+items.size()-1);
    foreach(ListItem *item, items)
    {
        dataList_.append(item);
    }
    endInsertRows();
}

void ResultListModel::insertRow(int row, ListItem *item)
{
    beginInsertRows(QModelIndex(),row,row);
    dataList_.insert(row,item);
    endInsertRows();
}

ListItem * ResultListModel::find(const QString &id) const
{
    foreach(ListItem * item, dataList_)
    {
        if(item->getId() == id) return item;
    }
    return 0;
}

QModelIndex ResultListModel::indexFromItem(const ListItem *item) const
{
    Q_ASSERT(item);
    for(int row=0; row<dataList_.size();++row)
    {
        if(dataList_.at(row) == item) return index(row);
    }

    return QModelIndex();
}

void ResultListModel::clear()
{
    beginRemoveRows(QModelIndex(),0, dataList_.size()-1);
    qDeleteAll(dataList_);
    dataList_.clear();
    endRemoveRows();
}

bool ResultListModel::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= dataList_.size()) return false;
    beginRemoveRows(QModelIndex(), row, row);
    delete dataList_.takeAt(row);
    endRemoveRows();
    return true;
}

bool ResultListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || (row+count) >= dataList_.size()) return false;
    beginRemoveRows(QModelIndex(),row,row+count-1);
    for(int i=0; i<count; ++i){
        delete dataList_.takeAt(row);
    }
    endRemoveRows();
    return true;

}

bool ResultListModel::isEmpty()
{
    return dataList_.isEmpty();
}

ListItem* ResultListModel::takeRow(int row){
    beginRemoveRows(QModelIndex(),row,row);
    ListItem* item = dataList_.takeAt(row);
    endRemoveRows();
    return item;
}

ListItem *ResultListModel::at(int index)
{
    return dataList_.at(index);
}
