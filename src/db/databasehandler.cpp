#include "databasehandler.h"
#include <QDebug>

DatabaseHandler::DatabaseHandler() :
    SERVER_NAME{"localhost"}, DB_NAME{"/usr/share/harbour-qtimetable/data/stations.db"},
    USER_NAME{"sbbApp"}, PASSWORD{"1234"}, q_{nullptr} {}

DatabaseHandler::~DatabaseHandler()
{
    if(q_)
        delete q_;
    db_.close();
}

/*
    open a connection to a database
*/
bool DatabaseHandler::openConnection()
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(DB_NAME);
    db_.setUserName(USER_NAME);
    db_.setPassword(PASSWORD);
    db_.setConnectOptions("QSQLITE_OPEN_READONLY=1");
    if(db_.open())
    {
        qDebug() << "db opened";
        q_ = new QSqlQuery(db_);
        q_->setForwardOnly(true);
        return true;
    }
    return false;
}


//void DatabaseHandler::searchByLocation(double latitude, double longitude, ResultListModel *mdl)
//{
//    mdl->clear();
//    double oneKM = 0.008983;
//    QGeoCoordinate myCoord(latitude,longitude);
//    QString sqlQuery = "SELECT id,external_id,name,lat,long,favorite FROM stations WHERE (abs(lat - " + QString::number(latitude) + ") < " + QString::number(oneKM) + ") and ( abs(long - " + QString::number(longitude) + ") < " + QString::number(oneKM) + ")";
//    q->prepare(sqlQuery);

////    qDebug()<< sqlQuery;
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//    QGeoCoordinate *other = 0;
//    QList<StationItemGeoAware*> resultList;
//    while(q->next())
//    {
//        other = new QGeoCoordinate(q->value(3).toDouble(), q->value(4).toDouble());
//        int distance = (int) myCoord.distanceTo(*other);
//        resultList.append(new StationItemGeoAware(q->value(0).toInt(),q->value(1).toInt(),q->value(3).toDouble(),q->value(4).toDouble(),q->value(2).toString(),q->value(5).toBool(),distance));
//    }

//    qSort(resultList.begin(),resultList.end(),dereferencedLessThan<StationItemGeoAware>);
//    foreach(StationItemGeoAware* ptr, resultList)
//        mdl->appendRow(ptr);

//    delete other;
//}

//LocationItem *DatabaseHandler::selectById(const int dbId)
//{
//    QString sqlQuery = QString("SELECT id,external_id,name,favorite FROM stations WHERE id=%1").arg(dbId);
//    q->prepare(sqlQuery);
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//    if(!q->next())
//    {
//        qDebug() << "failure to get value";
//    }
//    else
//    {
//        return new LocationItem(q->value(0).toInt(),q->value(1).toInt(), q->value(2).toString(),"","",STATION,q->value(3).toBool());
//    }
//    return 0;
//}

//void DatabaseHandler::changeFavorite(int id, bool favorite)
//{
//    QString sqlQuery;
//    if(favorite)
//    {
//        sqlQuery = "UPDATE stations SET favorite = 1 WHERE id = ";
//    }
//    else
//    {
//        sqlQuery = "UPDATE stations SET favorite = 0 WHERE id = ";
//    }
//    sqlQuery.append(QString::number(id));
////    qDebug() << sqlQuery;
//    q->prepare(sqlQuery);
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//}

//void DatabaseHandler::saveFavoriteConnection(LocationItem *depStation, LocationItem *arrStation, LocationItem *viaStation)
//{
//    QString sqlQuery;
//    if(viaStation != NULL)
//        sqlQuery = QString("INSERT INTO favorite_connections VALUES (NULL,'%1','%2','%3','%4','%5','%6',0)").arg(depStation->getName()).arg(depStation->getExternalId()).arg(arrStation->getName()).arg(arrStation->getExternalId()).arg(viaStation->getName()).arg(viaStation->getExternalId());
//    else
//        sqlQuery = QString("INSERT INTO favorite_connections VALUES (NULL,'%1','%2','%3','%4','%5','%6',0)").arg(depStation->getName()).arg(depStation->getExternalId()).arg(arrStation->getName()).arg(arrStation->getExternalId()).arg("e").arg("");
////    qDebug() << sqlQuery;
//    q->prepare(sqlQuery);
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//}

//void DatabaseHandler::getFavoritesConnections(ResultListModel *mdl)
//{
//    QString sqlQuery;
//    sqlQuery = "SELECT * FROM favorite_connections";
//    q->prepare(sqlQuery);
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//    while(q->next())
//    {
//        mdl->appendRow(new FavoriteConnectionItem(q->value(0).toInt(),q->value(2).toString(),q->value(1).toString(),q->value(4).toString(),q->value(3).toString(),q->value(6).toString(),q->value(5).toString()));
//    }
//    qDebug() << "dbHandler modeled FavoriteConnections";
//}

//void DatabaseHandler::removeFavoriteConnection(int index)
//{
//    QString sqlQuery;
//    sqlQuery = QString("DELETE FROM favorite_connections WHERE id = %1").arg(index);
////    qDebug() << sqlQuery;
//    q->prepare(sqlQuery);
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//}

//bool DatabaseHandler::isFavoriteConnection(LocationItem *depStation, LocationItem *arrStation, LocationItem *viaStation) const
//{
//    QString sqlQuery;
//    if(viaStation != NULL)
//        sqlQuery = QString("SELECT * FROM favorite_connections WHERE depStationExtId ='%1' AND arrStationExtId = '%2' AND viaStationExtId = '%3'").arg(depStation->getExternalId()).arg(arrStation->getExternalId()).arg(viaStation->getExternalId());
//    else
//        sqlQuery = QString("SELECT * FROM favorite_connections WHERE depStationExtId ='%1' AND arrStationExtId = '%2' AND viaStationExtId = '%3'").arg(depStation->getExternalId()).arg(arrStation->getExternalId()).arg("");
//    q->prepare(sqlQuery);
//    if(!q->exec())
//    {
//        qDebug() << "failure in DB query";
//        qDebug() << q->lastError();
//    }
//    return q->next();
//}

QSqlDatabase *DatabaseHandler::getDb()
{
    return &db_;
}
