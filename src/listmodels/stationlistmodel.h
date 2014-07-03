#ifndef STATIONLISTMODEL_H
#define STATIONLISTMODEL_H

#include "resultlistmodel.h"
#include "../listitems/locationitem.h"

typedef QList<LocationItem*> StationListType;

class StationListModel : public ResultListModel<LocationItem>
{
    Q_OBJECT
public:
    StationListModel(QObject *parent=nullptr)
        : ResultListModel<LocationItem>(parent) {}
};

#endif // STATIONLISTMODEL_H
