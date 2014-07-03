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
};

#endif // CONNECTIONLISTMODEL_H
