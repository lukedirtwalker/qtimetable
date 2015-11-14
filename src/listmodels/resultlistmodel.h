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

#ifndef RESULTLISTMODEL_H
#define RESULTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include <QSharedPointer>

template <class ItemType>  class ResultListModel : public QAbstractListModel
{

public:
    explicit ResultListModel(QObject *parent=nullptr);
    ~ResultListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void appendRow(QSharedPointer<ItemType>  item);
    void appendRows(const QList<QSharedPointer<ItemType> > &items);
    void insertRow(int row, QSharedPointer<ItemType> item);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void replaceData(const QList<QSharedPointer<ItemType> > &newData);
    bool isEmpty();
    QSharedPointer<ItemType> takeRow(int row);
    QSharedPointer<ItemType> find(const QString &id) const;
    QSharedPointer<ItemType> at(int index);
    QModelIndex indexFromItem(const QSharedPointer<ItemType> item) const;
    void clear();

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    using iterator = typename QList<QSharedPointer<ItemType>>::Iterator;
    using const_iterator = typename QList<QSharedPointer<ItemType>>::ConstIterator;

    iterator begin() { return dataList_.begin(); }
    const_iterator begin() const { return dataList_.begin(); }
    const_iterator cbegin() const { return dataList_.cbegin(); }
    iterator end() { return dataList_.end(); }
    const_iterator end() const { return dataList_.end(); }
    const_iterator cend() const { return dataList_.cend(); }

private:
    ItemType* prototype_;
    QList<QSharedPointer<ItemType> > dataList_;

};

// template class has to have definition
#include "resultlistmodel.cpp"

#endif // RESULTLISTMODEL_H
