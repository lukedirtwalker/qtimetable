#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql/QtSql>



//#include "util/sorterhelper.h"

class LocationItem;
class FavoriteConnectionModel;

class DatabaseHandler
{
public:
    static DatabaseHandler &getInstance();

    ~DatabaseHandler();
    bool openConnection(const QString &dbFile);
 //   void searchByLocation(double latitude,double longitude, ResultListModel *mdl);
    LocationItem *selectById(const int dbId);

    //favorite stations
    void changeFavorite(int id, bool favorite);

    QVariant saveFavoriteConnection(QSharedPointer<LocationItem> depStation, QSharedPointer<LocationItem> arrStation, QSharedPointer<LocationItem> viaStation);
    void populateFavoritesConnections(FavoriteConnectionModel *mdl);
    void removeFavoriteConnection(int index);
    bool isFavoriteConnection(QSharedPointer<LocationItem> depStation, QSharedPointer<LocationItem> arrStation, QSharedPointer<LocationItem> viaStation) const;

    QSqlDatabase *getDb();

private:
    DatabaseHandler() : q_{} {}
    DatabaseHandler(DatabaseHandler const&);
    void operator=(DatabaseHandler const&);

    QSqlDatabase db_;
    QSqlQuery *q_;
};

#endif // DATABASEHANDLER_H
