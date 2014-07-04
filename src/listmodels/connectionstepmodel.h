#ifndef CONNECTIONSTEPMODEL_H
#define CONNECTIONSTEPMODEL_H

#include "resultlistmodel.h"
#include "../listitems/connectionstepitem.h"

class ConnectionStepModel : public ResultListModel<ConnectionStepItem>
{
    Q_OBJECT
public:
    ConnectionStepModel(QObject *parent=nullptr)
        : ResultListModel<ConnectionStepItem>(parent) {}
};

#endif // CONNECTIONSTEPMODEL_H
