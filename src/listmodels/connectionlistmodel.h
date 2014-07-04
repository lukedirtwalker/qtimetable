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
};

inline QObject *ConnectionListModel::getConnectionSteps(const int index) {
    return at(index)->getConnectionSteps();
}

#endif // CONNECTIONLISTMODEL_H
