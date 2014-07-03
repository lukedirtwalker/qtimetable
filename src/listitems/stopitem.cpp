#include "stopitem.h"
#include "../domin/station.h"
#include "../domin/address.h"

StopItem::StopItem(QDomNode domBasicStop, QDateTime date)
{
    this->mLocation = NULL;
    this->mUtilisationFirst = 0;
    this->mUtilisationSecond = 0;
    this->mHasDelay = false;
    this->mHasArrDelay = false;
    this->mHasDepDelay = false;
    this->mHasArrTime = false;
    this->mHasDepTime = false;
    this->mHasChangedPlatform = false;
    this->mHasChangedArrPlatform = false;
    this->mHasChangedDepPlatform = false;

    QDomNode curNode = domBasicStop.firstChild();

    while(!curNode.isNull())
    {
        QString tagName = curNode.toElement().tagName();
        if(this->mLocation == NULL && tagName == "Station")
        {
            this->mLocation = new Station(curNode);
        }
        else if(this->mLocation == NULL && tagName == "Address")
        {
            this->mLocation = new Address(curNode);
        }
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
                this->mArrTime = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                this->mHasArrTime = true;
                this->mTime = this->mArrTime;
            }
            this->mArrPlatform = curNode.toElement().elementsByTagName("Platform").at(0).toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
            while(this->mArrPlatform.endsWith( ' ' )) this->mArrPlatform.chop(1);

            this->mPlatform = this->mArrPlatform;
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
                {
                    t = QTime::fromString(d,"hh:mm");
                }
                this->mDepTime = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                this->mHasDepTime = true;
                this->mTime = this->mDepTime;
            }
            this->mDepPlatform = curNode.toElement().elementsByTagName("Platform").at(0).toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
            while(this->mDepPlatform.endsWith( ' ' )) this->mDepPlatform.chop(1);
            this->mPlatform = this->mDepPlatform;
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
                            this->mDepPlatform = p.toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
                            while(this->mDepPlatform.endsWith(' ')) this->mDepPlatform.chop(1);
                            this->mHasChangedDepPlatform = !this->mDepPlatform.isEmpty();

                            this->mPlatform = this->mDepPlatform;
                            this->mHasChangedPlatform = !this->mPlatform.isEmpty();
                        }
                        else if(tagName == "Time")
                        {
                            QDateTime dateCopy = QDateTime(date.date());
                            QString d = p.toElement().text().toLatin1();
                            QTime t = QTime::fromString(d.mid(3),"hh:mm:ss");
                            int days = d.left(2).toInt();
                            QDateTime dt = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                            this->mHasDepDelay = true;
                            this->mDepDelay = Duration(this->mDepTime.secsTo(dt));

                            this->mHasDelay = true;
                            this->mDelay = this->mDepDelay;
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
                            this->mArrPlatform = p.toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
                            while(this->mArrPlatform.endsWith(' ')) this->mArrPlatform.chop(1);
                            this->mHasChangedArrPlatform = !this->mArrPlatform.isEmpty();

                            this->mPlatform = this->mArrPlatform;
                            this->mHasChangedPlatform = !this->mPlatform.isEmpty();
                        }
                        else if(tagName == "Time")
                        {
                            QDateTime dateCopy = QDateTime(date.date());
                            QString d = p.toElement().text().toLatin1();
                            QTime t = QTime::fromString(d.mid(3),"hh:mm:ss");
                            int days = d.left(2).toInt();
                            QDateTime dt = dateCopy.addSecs(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());
                            this->mHasArrDelay = true;
                            this->mArrDelay = Duration(this->mArrTime.secsTo(dt));

                            this->mHasDelay = true;
                            this->mDelay = this->mArrDelay;
                        }
                        p = p.nextSibling();
                    }
                }
                else if(tagName == "Capacity1st")
                {
                    this->mUtilisationFirst = n.toElement().text().toInt();
                }
                else if(tagName == "Capacity2nd")
                {
                    this->mUtilisationSecond = n.toElement().text().toInt();
                }
                n = n.nextSibling();
            }
        }
        curNode = curNode.nextSibling();
    }
    if(this->mLocation == NULL)
    {
        this->mLocation = new Location();
//        TODO Debugger::getInstance()->print("WARNING: STOP HAS NEITHER ADDRESS NOR STATION");
    }
}

StopItem::~StopItem()
{
    delete this->mLocation;
}

QString StopItem::getId() const
{
    return QString();
}

QVariant StopItem::data(int role) const
{
    switch(role)
    {
        case StationRole: return this->getName();
        case PlatformRole: return this->getPlatform();
        case ArrivalTimeRole: return this->getArrTime();
        case DepartureTimeRole: return this->getDepTime();
        case UtilisationFirstRole: return this->getUtilisationFirst();
        case UtilisationSecondRole: return this->getUtilisationSecond();
        case HasArrivalTimeRole: return this->hasArrTime();
        case HasDepartureTimeRole: return this->hasDepTime();
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

QDateTime StopItem::getTime()
{
    return this->mTime;
}

QString StopItem::getPlatform() const
{
    return this->mPlatform;
}

int StopItem::getUtilisationFirst() const
{
    return this->mUtilisationFirst;
}

int StopItem::getUtilisationSecond() const
{
    return this->mUtilisationSecond;
}

double StopItem::getLatitude() const
{
    switch(this->mLocation->getType())
    {
        case ADDRESS:
        {
            Address *a = (Address*) this->mLocation;
            return a->getLatitude().toDouble()/1000000;
        }
        case STATION:
        {
            Station *s = (Station*) this->mLocation;
            return s->getLatitude().toDouble()/1000000;
        }
    }
    return 0;
}

double StopItem::getLongitude() const
{
    switch(this->mLocation->getType())
    {
        case ADDRESS:
        {
            Address *a = (Address*) this->mLocation;
            return a->getLongitude().toDouble()/1000000;
        }
        case STATION:
        {
            Station *s = (Station*) this->mLocation;
            return s->getLongitude().toDouble()/1000000;
        }
    }
    return 0;
}

QString StopItem::getDelay() const
{
    return this->mDelay.toString();
}

QString StopItem::getName() const
{
    return this->mLocation->getName();
}

QString StopItem::getExternalId()
{
    switch(this->mLocation->getType())
    {
        case STATION:
        {
            Station *s = (Station*) this->mLocation;
            return s->getExternalID();
        }
    }
    return QString();
}

bool StopItem::hasDelay()
{
    return this->mHasDelay;
}

bool StopItem::hasArrTime() const
{
    return this->mHasArrTime;
}

bool StopItem::hasDepTime() const
{
    return this->mHasDepTime;
}

QDateTime StopItem::getArrTime() const
{
    return this->mArrTime;
}

QDateTime StopItem::getDepTime() const
{
    return this->mDepTime;
}

QString StopItem::getArrPlatform() const
{
    return this->mArrPlatform;
}

QString StopItem::getDepPlatform() const
{
    return this->mDepPlatform;
}

QString StopItem::getArrDelay() const
{
    return this->mArrDelay.toString();
}

QString StopItem::getDepDelay() const
{
    return this->mDepDelay.toString();
}

bool StopItem::hasChangedPlatform()
{
    return this->mHasChangedPlatform;
}

void StopItem::setDateTime(QDateTime t)
{
    this->mTime = t;
}
