/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include <QDebug>

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
void ResultListModel<ItemType>::appendRow(QSharedPointer<ItemType> item)
{
    appendRows(QList<QSharedPointer<ItemType> >() << item);
}

template <class ItemType>
void ResultListModel<ItemType>::appendRows(const QList<QSharedPointer<ItemType> > &items)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount()+items.size()-1);
    dataList_.append(items);
    endInsertRows();
}

template <class ItemType>
void ResultListModel<ItemType>::insertRow(int row, QSharedPointer<ItemType> item)
{
    beginInsertRows(QModelIndex(),row,row);
    dataList_.insert(row,item);
    endInsertRows();
}

template <class ItemType>
QSharedPointer<ItemType> ResultListModel<ItemType>::find(const QString &id) const
{
    for(auto item : dataList_)
        if(item->getId() == id) return item;
    return 0;
}

template <class ItemType>
QModelIndex ResultListModel<ItemType>::indexFromItem(const QSharedPointer<ItemType> item) const
{
    Q_ASSERT(item);
    for(int row=0; row<dataList_.size();++row)
        if(dataList_.at(row) == item) return index(row);

    return QModelIndex();
}

template <class ItemType>
void ResultListModel<ItemType>::clear()
{
    beginRemoveRows(QModelIndex(),0, dataList_.size()-1);
    dataList_.clear();
    endRemoveRows();
}

template <class ItemType>
bool ResultListModel<ItemType>::removeRow(int row, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row < 0 || row >= dataList_.size()) return false;
    beginRemoveRows(QModelIndex(), row, row);
    dataList_.takeAt(row).clear();
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
        dataList_.takeAt(row).clear();
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
QSharedPointer<ItemType> ResultListModel<ItemType>::takeRow(int row){
    beginRemoveRows(QModelIndex(),row,row);
    auto item = dataList_.takeAt(row);
    endRemoveRows();
    return item;
}

template <class ItemType>
QSharedPointer<ItemType> ResultListModel<ItemType>::at(int index)
{
    return dataList_.at(index);
}

template <class ItemType>
void ResultListModel<ItemType>::replaceData(const QList<QSharedPointer<ItemType> > &newData)
{
    clear();
    appendRows(newData);
}

template <class ItemType>
bool ResultListModel<ItemType>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() >= 0 && index.row() < dataList_.size()) {
        if(dataList_.at(index.row())->setData(value, role)) {
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    return false;
}
