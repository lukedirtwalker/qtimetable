#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql/QtSql>



//#include "util/sorterhelper.h"

class LocationItem;

class DatabaseHandler
{
public:
    static DatabaseHandler &getInstance() {
        static DatabaseHandler inst;
        return inst;
    }

    ~DatabaseHandler();
    bool openConnection(const QString &dbFile);
 //   void searchByLocation(double latitude,double longitude, ResultListModel *mdl);
    LocationItem *selectById(const int dbId);

    //favorite stations
    void changeFavorite(int id, bool favorite);

//    void saveFavoriteConnection(LocationItem *depStation, LocationItem *arrStation, LocationItem *viaStation);
//    void getFavoritesConnections(ResultListModel *mdl);
//    void removeFavoriteConnection(int index);
//    bool isFavoriteConnection(LocationItem *depStation, LocationItem *arrStation, LocationItem *viaStation) const;

    QSqlDatabase *getDb();

private:
    DatabaseHandler() : q_{} {}
    DatabaseHandler(DatabaseHandler const&);
    void operator=(DatabaseHandler const&);

    QSqlDatabase db_;
    QSqlQuery *q_;
};

#endif // DATABASEHANDLER_H
