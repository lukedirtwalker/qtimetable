template <class ItemType>
ResultListModel<ItemType>::ResultListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    prototype_ = new ItemType();
}

template <class ItemType>
int ResultListModel<ItemType>::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return dataList_.size();
}

template <class ItemType>
QVariant ResultListModel<ItemType>::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= dataList_.size())
        return QVariant();
    return dataList_.at(index.row())->data(role);
}

template <class ItemType>
QHash<int, QByteArray> ResultListModel<ItemType>::roleNames() const
{
    return prototype_->roleNames();
}

template <class ItemType>
ResultListModel<ItemType>::~ResultListModel()
{
    delete prototype_;
    clear();
}

template <class ItemType>
void ResultListModel<ItemType>::appendRow(ItemType *item)
{
    appendRows(QList<ItemType*>() << item);
}

template <class ItemType>
void ResultListModel<ItemType>::appendRows(const QList<ItemType *> &items)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount()+items.size()-1);
    dataList_.append(items);
    endInsertRows();
}

template <class ItemType>
void ResultListModel<ItemType>::insertRow(int row, ItemType *item)
{
    beginInsertRows(QModelIndex(),row,row);
    dataList_.insert(row,item);
    endInsertRows();
}

template <class ItemType>
ItemType *ResultListModel<ItemType>::find(const QString &id) const
{
    foreach(ItemType * item, dataList_)
    {
        if(item->getId() == id) return item;
    }
    return 0;
}

template <class ItemType>
QModelIndex ResultListModel<ItemType>::indexFromItem(const ItemType *item) const
{
    Q_ASSERT(item);
    for(int row=0; row<dataList_.size();++row)
    {
        if(dataList_.at(row) == item) return index(row);
    }

    return QModelIndex();
}

template <class ItemType>
void ResultListModel<ItemType>::clear()
{
    beginRemoveRows(QModelIndex(),0, dataList_.size()-1);
    qDeleteAll(dataList_);
    dataList_.clear();
    endRemoveRows();
}

template <class ItemType>
bool ResultListModel<ItemType>::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= dataList_.size()) return false;
    beginRemoveRows(QModelIndex(), row, row);
    delete dataList_.takeAt(row);
    endRemoveRows();
    return true;
}

template <class ItemType>
bool ResultListModel<ItemType>::removeRows(int row, int count, const QModelIndex &parent)
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

template <class ItemType>
bool ResultListModel<ItemType>::isEmpty()
{
    return dataList_.isEmpty();
}

template <class ItemType>
ItemType *ResultListModel<ItemType>::takeRow(int row){
    beginRemoveRows(QModelIndex(),row,row);
    ItemType* item = dataList_.takeAt(row);
    endRemoveRows();
    return item;
}

template <class ItemType>
ItemType *ResultListModel<ItemType>::at(int index)
{
    return dataList_.at(index);
}

template <class ItemType>
void ResultListModel<ItemType>::replaceData(const QList<ItemType *> &newData)
{
    clear();
    appendRows(newData);
}
