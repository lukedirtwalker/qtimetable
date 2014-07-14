#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include <QObject>
#include <QDateTime>

class TimeHandler : public QObject
{
    Q_OBJECT
public:
    TimeHandler(QObject *parent = nullptr);
    Q_INVOKABLE void updateTime();
    QDate getCurrentDate() const;
    QTime getCurrentTime() const;
    QDateTime getCurrentDateTime() const;
    Q_INVOKABLE void setTime(const int hours, const int minutes);
    Q_INVOKABLE void setDate(const int year, const int month, const int day);

    Q_PROPERTY(QDate date READ getCurrentDate() NOTIFY dateChanged)
    Q_PROPERTY(QTime time READ getCurrentTime() NOTIFY timeChanged)


signals:
    void dateChanged();
    void timeChanged();

private:
    QDateTime uiTime;
};

#endif // TIMEHANDLER_H
