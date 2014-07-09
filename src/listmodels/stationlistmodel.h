#ifndef STATIONLISTMODEL_H
#define STATIONLISTMODEL_H

#include "resultlistmodel.h"
#include "../listitems/locationitem.h"

typedef QList<QSharedPointer<LocationItem> > StationListType;

class StationListModel : public ResultListModel<LocationItem>
{
    Q_OBJECT
public:
    StationListModel(QObject *parent=nullptr)
        : ResultListModel<LocationItem>(parent) {}
    Q_INVOKABLE inline void clear();
};

inline void StationListModel::clear() { ResultListModel<LocationItem>::clear();}

#endif // STATIONLISTMODEL_H
