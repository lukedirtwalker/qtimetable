#ifndef THREADEDDBHANDLER_H
#define THREADEDDBHANDLER_H

#include <QtSql/QtSql>

#include "../listmodels/resultlistmodel.h"
//#include "ui/searchitem.h"
#include "../listitems/locationitem.h"

template<class T>
static bool dereferencedLessThan(T * o1, T * o2) {
    return *o1 < *o2;
}

class ThreadedDbHandler : public QObject
{
    Q_OBJECT
public:
    ThreadedDbHandler(QSqlDatabase *db, const QString &comp);
    ~ThreadedDbHandler();
    void interrupt();

//public slots:
    void run(const QString &comp, ResultListModel *model);

signals:
    void finished(const ResultListType items);

private:
    QSqlQuery *q_;
    QString comp_;
    QList<LocationItem*> items_;
//    ResultListType endItems_;
    bool interrupted_;

    //db queries
    int queryCityName(const QString &query,bool searchMiddle,int numResults);
    int queryStationName(const QString &query,bool searchMiddle,int numResults);
    //replacer function to reduce string in db format
    QString replacer(QString query);
};

#endif // THREADEDDBHANDLER_H
