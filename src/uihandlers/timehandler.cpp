#include "timehandler.h"

TimeHandler::TimeHandler(QObject *parent) :
    QObject(parent)
{
    uiTime = QDateTime::currentDateTime();
    emit dateChanged();
    emit timeChanged();
}

void TimeHandler::updateTime()
{
    uiTime = QDateTime::currentDateTime();
    emit dateChanged();
    emit timeChanged();
}

QDate TimeHandler::getCurrentDate() const
{
    return uiTime.date();
}

QTime TimeHandler::getCurrentTime() const
{
    return uiTime.time();
}

QDateTime TimeHandler::getCurrentDateTime() const
{
    return uiTime;
}

void TimeHandler::setTime(const int hours, const int minutes)
{
    uiTime.setTime(QTime(hours,minutes));
    emit timeChanged();
}

void TimeHandler::setDate(const int year, const int month, const int day)
{
    uiTime.setDate(QDate(year,month,day));
    emit dateChanged();
}
