#ifndef CONNECTIONLISTMODEL_H
#define CONNECTIONLISTMODEL_H

#include "resultlistmodel.h"
#include "../listitems/connectionitem.h"

class ConnectionListModel : public ResultListModel<ConnectionItem>
{
    Q_OBJECT
public:
    ConnectionListModel(QObject *parent=nullptr)
        : ResultListModel<ConnectionItem>(parent) {}

    Q_INVOKABLE inline QObject *getConnectionSteps(const int index);
    Q_INVOKABLE inline void clear();
};

inline QObject *ConnectionListModel::getConnectionSteps(const int index) {
    return at(index)->getConnectionSteps();
}

inline void ConnectionListModel::clear() { ResultListModel<ConnectionItem>::clear();}

#endif // CONNECTIONLISTMODEL_H
