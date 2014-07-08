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

private:
    ItemType* prototype_;
    QList<QSharedPointer<ItemType> > dataList_;

};

// template class has to have definition
#include "resultlistmodel.cpp"

#endif // RESULTLISTMODEL_H
