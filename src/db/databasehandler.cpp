/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "databasehandler.h"
#include <QDebug>

#include "../listitems/locationitem.h"
#include "../listitems/favoriteconnectionitem.h"

#include "../listmodels/favoriteconnectionmodel.h"

DatabaseHandler &DatabaseHandler::getInstance() {
    static DatabaseHandler inst;
    return inst;
}

DatabaseHandler::~DatabaseHandler()
{
    if(q_)
        delete q_;
    db_.close();
}

/*
    open a connection to a database
*/
bool DatabaseHandler::openConnection(const QString &dbFile)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(dbFile);
    db_.setUserName("sbbApp");
    db_.setPassword("1234");
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

QSharedPointer<LocationItem> DatabaseHandler::selectById(const int dbId)
{
    QString sqlQuery = QString("SELECT id,external_id,name,favorite FROM stations WHERE id=%1").arg(dbId);
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
        return QSharedPointer<LocationItem>();
    }
    if(!q_->next())
    {
        qDebug() << "failure to get value";
    }
    else
    {
        return QSharedPointer<LocationItem>::create(q_->value(0).toInt(), q_->value(1).toInt(),
                                                    q_->value(2).toString(), "", "",
                                                    q_->value(3).toBool());
    }
    return QSharedPointer<LocationItem>();
}

void DatabaseHandler::changeFavorite(int id, bool favorite)
{
    QString sqlQuery;
    if(favorite)
        sqlQuery = "UPDATE stations SET favorite = 1 WHERE id = ";
    else
        sqlQuery = "UPDATE stations SET favorite = 0 WHERE id = ";
    sqlQuery.append(QString::number(id));
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
}

QVariant DatabaseHandler::saveFavoriteConnection(QSharedPointer<LocationItem> depStation, QSharedPointer<LocationItem> arrStation, QSharedPointer<LocationItem> viaStation)
{
    QString sqlQuery;
    if(viaStation != NULL)
        sqlQuery = QString("INSERT INTO favorite_connections VALUES (NULL,'%1','%2','%3','%4','%5','%6',0)").arg(depStation->stationName()).arg(depStation->getExternalId()).arg(arrStation->stationName()).arg(arrStation->getExternalId()).arg(viaStation->stationName()).arg(viaStation->getExternalId());
    else
        sqlQuery = QString("INSERT INTO favorite_connections VALUES (NULL,'%1','%2','%3','%4','%5','%6',0)").arg(depStation->stationName()).arg(depStation->getExternalId()).arg(arrStation->stationName()).arg(arrStation->getExternalId()).arg("e").arg("");
//    qDebug() << sqlQuery;
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
    return q_->lastInsertId();
}

void DatabaseHandler::populateFavoritesConnections(FavoriteConnectionModel *mdl)
{
    QString sqlQuery;
    sqlQuery = "SELECT * FROM favorite_connections";
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
    while(q_->next())
    {
        mdl->appendRow(QSharedPointer<FavoriteConnectionItem>::create(q_->value(0).toInt(),q_->value(2).toString(),q_->value(1).toString(),q_->value(4).toString(),q_->value(3).toString(),q_->value(6).toString(),q_->value(5).toString()));
    }
    qDebug() << "dbHandler modeled FavoriteConnections";
}

void DatabaseHandler::removeFavoriteConnection(int index)
{
    QString sqlQuery;
    sqlQuery = QString("DELETE FROM favorite_connections WHERE id = %1").arg(index);
//    qDebug() << sqlQuery;
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
}

bool DatabaseHandler::isFavoriteConnection(QSharedPointer<LocationItem> depStation, QSharedPointer<LocationItem> arrStation, QSharedPointer<LocationItem> viaStation) const
{
    QString sqlQuery;
    if(viaStation != NULL)
        sqlQuery = QString("SELECT * FROM favorite_connections WHERE depStationExtId ='%1' AND arrStationExtId = '%2' AND viaStationExtId = '%3'").arg(depStation->getExternalId()).arg(arrStation->getExternalId()).arg(viaStation->getExternalId());
    else
        sqlQuery = QString("SELECT * FROM favorite_connections WHERE depStationExtId ='%1' AND arrStationExtId = '%2' AND viaStationExtId = '%3'").arg(depStation->getExternalId()).arg(arrStation->getExternalId()).arg("");
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
    return q_->next();
}

QSqlDatabase *DatabaseHandler::getDb()
{
    return &db_;
}
