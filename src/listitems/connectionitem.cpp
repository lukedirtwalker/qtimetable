#include "connectionitem.h"

#include <QDomNode>

ConnectionItem::ConnectionItem(QDomNode domConnection) : ListItem()
{
    mConnectionSteps = new ConnectionStepModel(this); // needs parent to keep ownership

    this->mDate = QDateTime::fromString(domConnection.toElement().elementsByTagName("Date").at(0).toElement().text().toLatin1(),"yyyyMMdd");
    this->mId = domConnection.toElement().attributeNode("id").value().toLatin1();
    mId = mId.trimmed();

    this->mNrChanges = domConnection.toElement().elementsByTagName("Transfers").at(0).toElement().text().toInt();

    QDomNodeList domStateInformations = domConnection.toElement().elementsByTagName("RtStateList");
    this->mHasCSInformation = domStateInformations.count();
    if(this->mHasCSInformation)
    {
        QDomNode domStateInformation = domStateInformations.at(0);
        QDomNodeList domSingleStateInformationList = domStateInformation.toElement().elementsByTagName("RtState");
        int n = domSingleStateInformationList.count();
        for(int i=0;i<n;i++)
        {
            QString val = domSingleStateInformationList.at(i).toElement().attributeNode("value").value();
            if(val == "HAS_DELAYINFO")
            {
                this->mConnectionStateInformations.append(DELAY_INFO);
            }
            else if(val == "WARNING")
            {
                this->mConnectionStateInformations.append(WARNING_INFO);
            }
            else if(val == "WARNING_CONNECTION_NOT_RIDABLE")
            {
                this->mConnectionStateInformations.append(WARNOTRIDABLE_INFO);
            }
            else if(val == "HAS_ALTERNATIVE")
            {
                this->mConnectionStateInformations.append(HAS_ALTERNATIVE);
            }
            else if(val == "IS_ALTERNATIVE")
            {
                this->mConnectionStateInformations.append(IS_ALTERNATIVE);
            }
            else
            {
//               TODO Debugger::getInstance()->print(QString(this->mId + ": Unhandled State Information: "+val));
            }
        }
    }

    QDomNode domDuration = domConnection.toElement().elementsByTagName("Duration").at(0);
    QString d = domDuration.toElement().elementsByTagName("Time").at(0).toElement().text().toLatin1();
    QTime t = QTime::fromString(d.mid(3),"hh:mm:ss");
    int days = d.left(2).toInt();
    this->mDuration = Duration(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());

    this->mServiceDays = "";
    QDomNode domServiceDays = domConnection.toElement().elementsByTagName("ServiceDays").at(0);
    if(domServiceDays.toElement().elementsByTagName("RegularServiceText").count())
    {
        this->mHasIrregularServiceDays = false;
        this->mServiceDays = domServiceDays.toElement().elementsByTagName("RegularServiceText").at(0).toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
    }
    else if(domServiceDays.toElement().elementsByTagName("IrregularServiceText").count())
    {
        this->mHasIrregularServiceDays = true;
        this->mServiceDays = domServiceDays.toElement().elementsByTagName("IrregularServiceText").at(0).toElement().elementsByTagName("Text").at(0).toElement().text().toLatin1();
    }
    while(this->mServiceDays.endsWith( ' ' )) this->mServiceDays.chop(1);

    QDomNode domProducts = domConnection.toElement().elementsByTagName("Products").at(0);
    QDomNodeList domProductList = domProducts.toElement().elementsByTagName("Product");
    int count = domProductList.count();
    for(int i=0;i<count;i++)
    {
        QString travel = domProductList.at(i).toElement().attributeNode("cat").value().toLatin1();
        while(travel.endsWith( ' ' )) travel.chop(1);
        this->mConnectionVehicles.append(travel);
    }

    QDomNodeList domConnectionSteps = domConnection.toElement().elementsByTagName("ConSection");
    count = domConnectionSteps.count();
    for(int i=0;i<count;i++)
    {
        QDomNode domCStep = domConnectionSteps.at(i);
        ConnectionStepItem *s = new ConnectionStepItem(domCStep,this->mDate);
        this->mConnectionSteps->appendRow(s);
    }

    this->createOverview();
}

ConnectionItem::~ConnectionItem()
{
    mConnectionSteps->clear();
    delete mConnectionSteps;
//    qDeleteAll(this->mConnectionSteps);
}

QVariant ConnectionItem::data(int role) const
{
    switch(role)
    {
    case DepRole: return this->getDepartureTime();
    case ArrRole: return this->getArrivalTime();
    case DurRole: return this->getDuration();
    case ChgRole: return this->getNumberOfChanges();
    case PlatRole: return this->getPlatform();
    case UtilisationFirstRole: return this->getUtilisationFirst();
    case UtilisationSecRole: return this->getUtilisationSecond();
    case ConnectionStateInfoRole: return this->getConnectionStateInfo();
    case HasChangedDeparturePlatformRole: return this->hasChangedDeparturePlatform();
    default: return QVariant();
    }
}

QHash<int, QByteArray> ConnectionItem::roleNames() const
{
    QHash<int,QByteArray> names;
    names[DepRole] = "dep";
    names[ArrRole] = "arr";
    names[DurRole] = "dur";
    names[ChgRole] = "chg";
    names[PlatRole] = "plat";
    names[UtilisationFirstRole] = "utFirst";
    names[UtilisationSecRole] = "utSecond";
    names[ConnectionStateInfoRole] = "getConnectionStateInfo";
    names[HasChangedDeparturePlatformRole] = "HasChangedDepPlatform";
    return names;
}

void ConnectionItem::createOverview()
{
    int maxFirst = 0;
    int maxSecond = 0;
    int count = mConnectionSteps->rowCount();
    for(int i = 0; i < count; ++i)
    {
         ConnectionStepItem *cur = mConnectionSteps->at(i);
        maxFirst = qMax(maxFirst,cur->getUtilisationFirst());
        maxSecond = qMax(maxSecond,cur->getUtilisationSecond());
    }
    this->mUtilisationFirst = maxFirst;
    this->mUtilisationSecond = maxSecond;

    bool start = true;
    ConnectionStepItem *cur = mConnectionSteps->at(0);
    for(int i = 0; i < count; ++i)
    {
        cur = mConnectionSteps->at(i);
        if (cur->hasMeansOfTransportation())
            break;
        if(!start)
            this->mNrChanges--;
        else
            start = false;
    }
    ConnectionStepItem *tmp = cur;
    this->mPlatform = tmp->getDepPlatform();
    this->mHasChangedDeparturePlatform = tmp->hasChangedDeparturePlatform();
    this->mDepartureTime = tmp->getDepTime();
    this->mArrivalTime = this->mConnectionSteps->at(count - 1)->getArrTime();
}

QString ConnectionItem::getId() const
{
    return QString();
}

ConnectionStepModel *ConnectionItem::getConnectionSteps()
{
    return this->mConnectionSteps;
}

QString ConnectionItem::getPlatform() const
{
    return this->mPlatform;
}
int ConnectionItem::getNumberOfChanges() const
{
    return this->mNrChanges;
}

int ConnectionItem::getUtilisationSecond() const
{
    return this->mUtilisationSecond;
}

bool ConnectionItem::hasChangedDeparturePlatform() const
{
    return this->mHasChangedDeparturePlatform;
}

int ConnectionItem::getUtilisationFirst() const
{
    return this->mUtilisationFirst;
}

int ConnectionItem::getConnectionStateInfo() const
{
    return this->mConnectionStateInfo;
}

bool ConnectionItem::hasConnectionStateInformation()
{
    return this->mHasCSInformation;
}

void ConnectionItem::setConnectionStateInfo(int info)
{
    this->mConnectionStateInfo = info;
}

QDateTime ConnectionItem::getDepartureTime() const
{
    return this->mDepartureTime;
}

QDateTime ConnectionItem::getArrivalTime() const
{
    return this->mArrivalTime;
}

QString ConnectionItem::getDuration() const
{
    return this->mDuration.toString();
}
