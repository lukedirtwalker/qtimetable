#ifndef RESULTLISTMODEL_H
#define RESULTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>

template <class ItemType>  class ResultListModel : public QAbstractListModel
{

public:
    explicit ResultListModel(QObject *parent=nullptr);
    ~ResultListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void appendRow(ItemType* item);
    void appendRows(const QList<ItemType*> &items);
    void insertRow(int row, ItemType *item);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool isEmpty();
    ItemType* takeRow(int row);
    ItemType* find(const QString &id) const;
    ItemType* at(int index);
    QModelIndex indexFromItem(const ItemType *item) const;
    void clear();

private:
    ItemType* prototype_;
    QList<ItemType*> dataList_;

};

// template class has to have definition
#include "resultlistmodel.cpp"

#endif // RESULTLISTMODEL_H
