#include "stopitem.h"

#include <QDebug>

#include "../domin/station.h"
#include "../domin/address.h"

StopItem::StopItem(QDomNode domBasicStop, QDateTime date)
    : hasDelay_{false}, hasArrTime_{false}, hasDepTime_{false},
      hasDepDelay_{false}, hasArrDelay_{false}, hasChangedPlatform_{false},
      hasChangedArrPlatform_{false}, hasChangedDepPlatform_{false},
      location_{nullptr}, utilisationFirst_{0}, utilisationSecond_{0}
{
    QDomNode curNode = domBasicStop.firstChild();

    while(!curNode.isNull())
    {
        QString tagName = curNode.toElement().tagName();
        if(!location_ && tagName == "Station")
            location_ = new Station(curNode);
        else if(!location_ && tagName == "Address")
            location_ = new Address(curNode);
        else if(tagName == "Arr")
        {
            QDateTime dateCopy = QDateTime(date.date());
            QString d = curNode.toElement().elementsByTagName("Time").at(0).toElement().text().toLatin1();
            if(!d.isEmpty())
            {
                int days = 0;
                QTime t;
                if(d.contains("d"))
                {
                    t = QTime::fromString(d.mid(3),"hh:mm:ss");
                    days = d.left(2).toInt();
                }
                else
                {
                    t = QTime::fromString(d,"hh:mm");
                }
                arrTime_ = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                hasArrTime_ = true;
                time_ = arrTime_;
            }
            arrPlatform_ = curNode.toElement().elementsByTagName("Platform").at(0).toElement().elementsByTagName("Text").at(0).toElement().text().trimmed().toLatin1();

            platform_ = arrPlatform_;
        }
        else if(tagName == "Dep")
        {
            QDateTime dateCopy = QDateTime(date.date());
            QString d = curNode.toElement().elementsByTagName("Time").at(0).toElement().text().toLatin1();
            if(!d.isEmpty())
            {
                int days = 0;
                QTime t;
                if(d.contains("d"))
                {
                    t = QTime::fromString(d.mid(3),"hh:mm:ss");
                    days = d.left(2).toInt();
                }
                else
                    t = QTime::fromString(d,"hh:mm");
                depTime_ = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                hasDepTime_ = true;
                time_ = depTime_;
            }
            depPlatform_ = curNode.toElement().elementsByTagName("Platform").at(0).toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
            while(depPlatform_.endsWith( ' ' )) depPlatform_.chop(1);
            platform_ = depPlatform_;
        }
        else if(tagName == "StopPrognosis")
        {
            QDomNode n = curNode.firstChild();
            while(!n.isNull())
            {
                QString tagName = n.toElement().tagName();
                if(tagName == "Dep")
                {
                    QDomNode p = n.firstChild();
                    while(!p.isNull())
                    {
                        QString tagName = p.toElement().tagName();
                        if(tagName == "Platform")
                        {
                            depPlatform_ = p.toElement().elementsByTagName("Text").at(0).toElement().text().trimmed().toLatin1();
                            hasChangedDepPlatform_ = !depPlatform_.isEmpty();

                            platform_ = depPlatform_;
                            hasChangedPlatform_ = !platform_.isEmpty();
                        }
                        else if(tagName == "Time")
                        {
                            QDateTime dateCopy = QDateTime(date.date());
                            QString d = p.toElement().text().toLatin1();
                            QTime t = QTime::fromString(d.mid(3),"hh:mm:ss");
                            int days = d.left(2).toInt();
                            QDateTime dt = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                            hasDepDelay_ = true;
                            delay_ = Duration(depTime_.secsTo(dt));
                            hasDelay_ = true;
                        }
                        p = p.nextSibling();
                    }
                }
                else if(tagName == "Arr")
                {
                    QDomNode p = n.firstChild();
                    while(!p.isNull())
                    {
                        QString tagName = p.toElement().tagName();
                        if(tagName == "Platform")
                        {
                            arrPlatform_ = p.toElement().elementsByTagName("Text").at(0).toElement().text().trimmed().toLatin1();
                            hasChangedArrPlatform_ = !arrPlatform_.isEmpty();

                            platform_ = arrPlatform_;
                            hasChangedPlatform_ = !platform_.isEmpty();
                        }
                        else if(tagName == "Time")
                        {
                            QDateTime dateCopy = QDateTime(date.date());
                            QString d = p.toElement().text().toLatin1();
                            QTime t = QTime::fromString(d.mid(3),"hh:mm:ss");
                            int days = d.left(2).toInt();
                            QDateTime dt = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                            hasArrDelay_ = true;
                            delay_ = Duration(arrTime_.secsTo(dt));
                            hasDelay_ = true;
                        }
                        p = p.nextSibling();
                    }
                }
                else if(tagName == "Capacity1st")
                    utilisationFirst_ = n.toElement().text().toInt();
                else if(tagName == "Capacity2nd")
                    utilisationSecond_ = n.toElement().text().toInt();
                n = n.nextSibling();
            }
        }
        curNode = curNode.nextSibling();
    }
    if(!location_)
    {
        location_ = new Location();
        qDebug() << "WARNING: STOP HAS NEITHER ADDRESS NOR STATION";
    }
}

StopItem::~StopItem()
{
    delete location_;
}

QString StopItem::getId() const
{
    return QString();
}

QVariant StopItem::data(int role) const
{
    switch(role)
    {
        case StationRole: return location_->getName();
        case PlatformRole: return platform_;
        case ArrivalTimeRole: return arrTime_;
        case DepartureTimeRole: return depTime_;
        case UtilisationFirstRole: return utilisationFirst_;
        case UtilisationSecondRole: return utilisationSecond_;
        case HasArrivalTimeRole: return hasArrTime_;
        case HasDepartureTimeRole: return hasDepTime_;
        default: return QVariant();
    }
}

QHash<int, QByteArray> StopItem::roleNames() const
{
    QHash<int,QByteArray> names;
    names[StationRole] = "StationName";
    names[ArrivalTimeRole] = "ArrivalTime";
    names[PlatformRole] = "Platform";
    names[DepartureTimeRole] = "DepartureTime";
    names[UtilisationFirstRole] = "UtilisationFirst";
    names[UtilisationSecondRole] = "UtilisationSecond";
    names[HasArrivalTimeRole] = "HasArrivalTime";
    names[HasDepartureTimeRole] = "HasDepartureTime";
    return names;
}

QString StopItem::getPlatform() const
{
    return platform_;
}

int StopItem::getUtilisationFirst() const
{
    return utilisationFirst_;
}

int StopItem::getUtilisationSecond() const
{
    return utilisationSecond_;
}

double StopItem::getLatitude() const
{
    auto type = location_->getType();
    if(ADDRESS == type)
            return static_cast<Address*>(location_)->getLatitude().toDouble()/1000000;
    else if(STATION == type)
            return static_cast<Station*>(location_)->getLatitude().toDouble()/1000000;
    return 0;
}

double StopItem::getLongitude() const
{
    auto type = location_->getType();
    if(ADDRESS == type)
            return static_cast<Address*>(location_)->getLongitude().toDouble()/1000000;
    else if(STATION == type)
            return static_cast<Station*>(location_)->getLongitude().toDouble()/1000000;
    return 0;
}

QString StopItem::getDelay() const
{
    return delay_.toString();
}

QString StopItem::getName() const
{
    return location_->getName();
}

QString StopItem::getExternalId() const
{
    if(STATION == location_->getType())
        return static_cast<Station*>(location_)->getExternalID();
    return QString();
}

bool StopItem::hasDelay()
{
    return hasDelay_;
}

bool StopItem::hasChangedPlatform()
{
    return hasChangedPlatform_;
}

void StopItem::setDateTime(QDateTime t)
{
    time_ = t;
}
