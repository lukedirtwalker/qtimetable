#include "domdate.h"

DomDate::DomDate(QDateTime date, bool isArrival) : Serializable("ReqT")
{
    domStaticElementAttributes_["a"] = isArrival ? "1" : "0";
    QString dateString = QString("%1%2%3").arg(
                QString("%1").arg(date.date().year(),4,10,QChar('0').toUpper()),
                QString("%1").arg(date.date().month(),2,10,QChar('0').toUpper()),
                QString("%1").arg(date.date().day(),2,10,QChar('0').toUpper()));
    domStaticElementAttributes_["date"] =  dateString;
    domStaticElementAttributes_["time"] = date.time().toString("hh:mm");
}
