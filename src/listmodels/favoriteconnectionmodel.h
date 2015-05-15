#ifndef FAVORITECONNECTIONMODEL_H
#define FAVORITECONNECTIONMODEL_H

#include "resultlistmodel.h"
#include "../listitems/favoriteconnectionitem.h"

class FavoriteConnectionModel : public ResultListModel<FavoriteConnectionItem>
{
    Q_OBJECT
public:
    FavoriteConnectionModel(QObject *parent = nullptr)
        : ResultListModel<FavoriteConnectionItem>(parent) {}
};

#endif // FAVORITECONNECTIONMODEL_H
