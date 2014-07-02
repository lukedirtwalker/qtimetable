#include "timehandler.h"

TimeHandler::TimeHandler(QObject *parent) :
    QObject(parent)
{
    this->uiTime = QDateTime::currentDateTime();
}

void TimeHandler::updateTime()
{
    this->uiTime = QDateTime::currentDateTime();
}

QDate TimeHandler::getCurrentDate() const
{
    return this->uiTime.date();
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
}

void TimeHandler::setDate(const int year, const int month, const int day)
{
    uiTime.setDate(QDate(year,month,day));
}
