#ifndef RESULTLISTMODEL_H
#define RESULTLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>

#include "../listitems/listitem.h"
#include "resultlisttype.h"

class ResultListModel : public QAbstractListModel
{
    Q_OBJECT

    //TODO we can template this class?

public:
    explicit ResultListModel(ListItem* prototype, QObject* parent=0);
    ~ResultListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;
    void appendRow(ListItem* item);
    void appendRows(const QList<ListItem*> &items);
    void insertRow(int row, ListItem* item);
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool isEmpty();
    ListItem* takeRow(int row);
    ListItem* find(const QString &id) const;
    ListItem* at(int index);
    QModelIndex indexFromItem( const ListItem* item) const;
    Q_INVOKABLE void clear();

private:
    ListItem* prototype_;
    ResultListType dataList_;

};

#endif // RESULTLISTMODEL_H
