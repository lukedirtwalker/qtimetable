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

#ifndef THREADEDDBHANDLER_H
#define THREADEDDBHANDLER_H

#include <QtSql/QtSql>

class LocationItem;

template<class T>
static bool dereferencedLessThan(QSharedPointer<T> o1, QSharedPointer<T> o2) {
    return *o1 < *o2;
}

class ThreadedDbHandler : public QObject
{
    Q_OBJECT
public:
    // Don't use this with empty strings!
    ThreadedDbHandler(const QString &comp);
    ~ThreadedDbHandler();

public slots:
    void run();

signals:
    void finished();
    void foundResults(const QList<QSharedPointer<LocationItem> > items);

private:
    QSqlQuery *q_;
    QString comp_;
    QList<QSharedPointer<LocationItem> > items_;

    //db queries
    int queryCityName(const QString &query,bool searchMiddle,int numResults);
    int queryStationName(const QString &query,bool searchMiddle,int numResults);
    //replacer function to reduce string in db format
    QString replacer(QString query);
};

#endif // THREADEDDBHANDLER_H
