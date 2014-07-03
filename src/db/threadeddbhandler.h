#ifndef THREADEDDBHANDLER_H
#define THREADEDDBHANDLER_H

#include <QtSql/QtSql>

class LocationItem;

template<class T>
static bool dereferencedLessThan(T * o1, T * o2) {
    return *o1 < *o2;
}

class ThreadedDbHandler : public QObject
{
    Q_OBJECT
public:
    // Don't use this with empty strings!
    ThreadedDbHandler(QSqlDatabase *db, const QString &comp);
    ~ThreadedDbHandler();

public slots:
    void run();

signals:
    void finished();
    void foundResults(const QList<LocationItem*> items);

private:
    QSqlQuery *q_;
    QString comp_;
    QList<LocationItem*> items_;

    //db queries
    int queryCityName(const QString &query,bool searchMiddle,int numResults);
    int queryStationName(const QString &query,bool searchMiddle,int numResults);
    //replacer function to reduce string in db format
    QString replacer(QString query);
};

#endif // THREADEDDBHANDLER_H
