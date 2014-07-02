#ifndef TIMEHANDLER_H
#define TIMEHANDLER_H

#include <QObject>
#include <QDateTime>

class TimeHandler : public QObject
{
    Q_OBJECT
public:
    TimeHandler(QObject *parent = 0);
    Q_INVOKABLE void updateTime();
    Q_INVOKABLE QDate getCurrentDate() const;
    Q_INVOKABLE QTime getCurrentTime() const;
    Q_INVOKABLE QDateTime getCurrentDateTime() const;
    Q_INVOKABLE void setTime(const int hours, const int minutes);
    Q_INVOKABLE void setDate(const int year, const int month, const int day);

private:
    QDateTime uiTime;
};

#endif // TIMEHANDLER_H
