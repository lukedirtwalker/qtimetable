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

#include "threadeddbhandler.h"

#include "databasehandler.h"

#include "../listitems/locationitem.h"
//#include "ui/searchitem.h"

ThreadedDbHandler::~ThreadedDbHandler()
{
    delete q_;
}

ThreadedDbHandler::ThreadedDbHandler(const QString &comp)
    : QObject(), comp_(comp)
{
    q_ = new QSqlQuery(*DatabaseHandler::getInstance().getDb());
}

void ThreadedDbHandler::run()
{
    QString comparer = replacer(comp_);
    int len = comparer.length();
    int i=20;
    if(i>0)
        i-=queryCityName(comparer,false,i);
    if(i>0 && len > 1)
        i-=queryCityName(comparer,true,i);
    if(i>0)
        i-=queryStationName(comparer,false,i);
    if(i>0 && len > 1)
        i-=queryStationName(comparer,true,i);

    qStableSort(items_.begin(),items_.end(),dereferencedLessThan<LocationItem>);

    // TODO items_.prepend(new SearchItem(comp_));

    emit foundResults(items_);

    emit finished();
}

int ThreadedDbHandler::queryCityName(const QString &query, bool searchMiddle, int numResults)
{
    int i=0;
    QString sqlQuery = "SELECT id,external_id,name,favorite FROM stations WHERE";
    QRegExp rx("(\\ |\\,)");
    QStringList parts = query.split(rx,QString::SkipEmptyParts);
    //        qDebug() << "parts Len" << parts.length();
    if(parts.length()>1){
        if(searchMiddle)
            return 0;
        for(int k=0;k<parts.length();k++)
        {
            sqlQuery.append(" (reduced_city_name LIKE '"+parts.at(k)+"%'");
            sqlQuery.append(" or reduced_city_name LIKE '% "+parts.at(k)+"%'");
            sqlQuery.append(" or reduced_station_name LIKE '"+parts.at(k)+"%'");
            sqlQuery.append(" or reduced_station_name LIKE '% "+parts.at(k)+"%')");
            if(k != parts.length()-1)
                sqlQuery.append(" and ");
        }
    }
    else
    {
        if(searchMiddle)
            sqlQuery = "SELECT id,external_id,name,favorite FROM stations WHERE reduced_city_name LIKE '% "+query+"%'";
        else
            sqlQuery = "SELECT id,external_id,name,favorite FROM stations WHERE reduced_city_name LIKE '"+query+"%'";

    }
    sqlQuery.append(" order by favorite desc limit 15");
    //        qDebug() << sqlQuery;
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
    for(i=0; i< numResults; i++)
    {
        if(q_->next())
        {
            items_.append(QSharedPointer<LocationItem>
                          (new LocationItem(q_->value(0).toInt(),
                                            q_->value(1).toInt(),
                                            q_->value(2).toString(),"","",
                                            q_->value(3).toBool())));
        }
        else
            break;
    }
    return i;
}

int ThreadedDbHandler::queryStationName(const QString &query, bool searchMiddle, int numResults)
{
    int i=0;
    QString sqlQuery;
    QRegExp rx("(\\ |\\,)");
    QStringList parts = query.split(rx,QString::SkipEmptyParts);
    //        qDebug() << "parts Len" << parts.length();
    if(parts.length()>1){
        return 0;
    }
    else
    {
        if(searchMiddle)
            sqlQuery = "SELECT id,external_id,name,favorite FROM stations WHERE reduced_station_name LIKE '% "+query+"%'";
        else
            sqlQuery = "SELECT id,external_id,name,favorite FROM stations WHERE reduced_station_name LIKE '"+query+"%'";
    }
    sqlQuery.append(" order by favorite desc limit 15");
    //  qDebug() << sqlQuery;
    q_->prepare(sqlQuery);
    if(!q_->exec())
    {
        qDebug() << "failure in DB query";
        qDebug() << q_->lastError();
    }
    for(i=0; i< numResults; i++)
    {
        if(q_->next())
        {
            items_.append(QSharedPointer<LocationItem>
                          (new LocationItem(q_->value(0).toInt(),
                                            q_->value(1).toInt(),
                                            q_->value(2).toString(),"","",
                                            q_->value(3).toBool())));
        }
        else
            break;
    }
    return i;
}

QString ThreadedDbHandler::replacer(QString query)
{
    QString ret = query;
    ret = ret.toLower();
    ret.replace(QString::fromUtf8("\u00E4"),QString("a"));
    ret.replace(QString::fromUtf8("\u00E2"),QString("a"));
    ret.replace(QString::fromUtf8("\u00E0"),QString("a"));
    ret.replace(QString::fromUtf8("\u00fc"),QString("u"));
    ret.replace(QString::fromUtf8("\u00F9"),QString("u"));
    ret.replace(QString::fromUtf8("\u00FB"),QString("u"));
    ret.replace(QString::fromUtf8("\u00F6"),QString("o"));
    ret.replace(QString::fromUtf8("\u00F4"),QString("o"));
    ret.replace(QString::fromUtf8("\u00E9"),QString("e"));
    ret.replace(QString::fromUtf8("\u00E8"),QString("e"));
    ret.replace(QString::fromUtf8("\u00EA"),QString("e"));
    ret.replace(QString::fromUtf8("\u00EB"),QString("e"));
    ret.replace(QString::fromUtf8("\u00EF"),QString("i"));
    ret.replace(QString::fromUtf8("\u00EE"),QString("i"));
    ret.replace(QString::fromUtf8("\u00FF"),QString("y"));
    ret.replace(QString::fromUtf8("\u00E7"),QString("c"));
    ret.replace('-',QString(" "));
    ret.replace('/',QString(" "));
    ret.replace('.',QString(" "));
    ret.replace('(',QString(" "));
    ret.replace(')',QString(" "));
    return ret;
}
