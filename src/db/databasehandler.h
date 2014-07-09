#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql/QtSql>



//#include "util/sorterhelper.h"


class DatabaseHandler
{
public:
    DatabaseHandler(QString dbFile);
    ~DatabaseHandler();
    bool openConnection();
 //   void searchByLocation(double latitude,double longitude, ResultListModel *mdl);
//    LocationItem *selectById(const int dbId);

    //favorite stations
//    void changeFavorite(int id, bool favorite);

//    void saveFavoriteConnection(LocationItem *depStation, LocationItem *arrStation, LocationItem *viaStation);
//    void getFavoritesConnections(ResultListModel *mdl);
//    void removeFavoriteConnection(int index);
//    bool isFavoriteConnection(LocationItem *depStation, LocationItem *arrStation, LocationItem *viaStation) const;

    QSqlDatabase *getDb();

private:
    QString DB_NAME;
    QString USER_NAME;
    QString PASSWORD;
    QSqlDatabase db_;
    QSqlQuery *q_;
};

#endif // DATABASEHANDLER_H
