#include "connectionitem.h"

#include <QDomNode>
#include <QDebug>

#include "../util/qdomnodeiterator.h"

ConnectionItem::ConnectionItem(QDomNode domConnection, QObject *parent)
    : ListItem(parent)
{
    connectionSteps_ = new ConnectionStepModel(this); // needs parent to keep ownership

    date_ = QDateTime::fromString(domConnection.toElement().elementsByTagName(QStringLiteral("Date")).at(0).toElement().text().toLatin1(),"yyyyMMdd");
    id_ = domConnection.toElement().attributeNode(QStringLiteral("id")).value().trimmed().toLatin1();

    nrChanges_ = domConnection.toElement().elementsByTagName(QStringLiteral("Transfers")).at(0).toElement().text().toInt();

    QDomNodeList domStateInformations = domConnection.toElement().elementsByTagName(QStringLiteral("RtStateList"));
    hasCSInformation_ = domStateInformations.count();
    if(hasCSInformation_)
    {
        QDomNode domStateInformation = domStateInformations.at(0);
        QDomNodeList domSingleStateInformationList = domStateInformation.toElement().elementsByTagName(QStringLiteral("RtState"));
        int n = domSingleStateInformationList.count();
        for(int i=0;i<n;i++)
        {
            QString val = domSingleStateInformationList.at(i).toElement().attributeNode(QStringLiteral("value")).value();
            if(val == "HAS_DELAYINFO")
                connectionStateInformations_.append(DELAY_INFO);
            else if(val == "WARNING")
                connectionStateInformations_.append(WARNING_INFO);
            else if(val == "WARNING_CONNECTION_NOT_RIDABLE")
                connectionStateInformations_.append(WARNOTRIDABLE_INFO);
            else if(val == "HAS_ALTERNATIVE")
                connectionStateInformations_.append(HAS_ALTERNATIVE);
            else if(val == "IS_ALTERNATIVE")
                connectionStateInformations_.append(IS_ALTERNATIVE);
            else
                qDebug() << id_ << ": Unhandled State Information:" << val;
        }
    }

    QDomNode domDuration = domConnection.toElement().elementsByTagName(QStringLiteral("Duration")).at(0);
    QString d = domDuration.toElement().elementsByTagName(QStringLiteral("Time")).at(0).toElement().text().toLatin1();
    QTime t = QTime::fromString(d.mid(3),"hh:mm:ss");
    int days = d.left(2).toInt();
    duration_ = Duration(days*24*60*60+t.hour()*60*60+t.minute()*60+t.second());

    serviceDays_ = "";
    QDomNode domServiceDays = domConnection.toElement().elementsByTagName(QStringLiteral("ServiceDays")).at(0);
    auto regServiceText = domServiceDays.toElement().elementsByTagName(QStringLiteral("RegularServiceText"));
    if(regServiceText.count())
    {
        hasIrregularServiceDays_ = false;
        serviceDays_ = regServiceText.at(0).toElement().elementsByTagName(QStringLiteral("Text")).at(0).toElement().text().trimmed().toLatin1();
    }

    else
    {
        auto irregServiceText = domServiceDays.toElement().elementsByTagName(QStringLiteral("IrregularServiceText"));
        if(irregServiceText.count())
        {
            hasIrregularServiceDays_ = true;
            serviceDays_ = irregServiceText.at(0).toElement().elementsByTagName(QStringLiteral("Text")).at(0).toElement().text().trimmed().toLatin1();
        }
    }

    QDomNode domProducts = domConnection.toElement().elementsByTagName(QStringLiteral("Products")).at(0);
    QDomNodeList domProductList = domProducts.toElement().elementsByTagName(QStringLiteral("Product"));

    for(auto product : domProductList)
        connectionVehicles_.append(product.toElement().attributeNode(QStringLiteral("cat")).value().trimmed().toLatin1());

    QDomNodeList domConnectionSteps = domConnection.toElement().elementsByTagName(QStringLiteral("ConSection"));
    for(auto conStep : domConnectionSteps)
        connectionSteps_->appendRow(QSharedPointer<ConnectionStepItem>(new ConnectionStepItem(conStep,date_)));

    createOverview();
}

QVariant ConnectionItem::data(int role) const
{
    switch(role)
    {
    case DepRole: return departureTime_;
    case ArrRole: return arrivalTime_;
    case DurRole: return duration_.toString();
    case ChgRole: return nrChanges_;
    case PlatRole: return platform_;
    case UtilisationFirstRole: return utilisationFirst_;
    case UtilisationSecRole: return utilisationSecond_;
    case ConnectionStateInfoRole: return connectionStateInfo_;
    case HasChangedDeparturePlatformRole: return hasChangedDeparturePlatform_;
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

bool ConnectionItem::setData(const QVariant &value, int role)
{
    Q_UNUSED(value)
    Q_UNUSED(role)
    return false;
}

void ConnectionItem::createOverview()
{
    int maxFirst = 0;
    int maxSecond = 0;
    int count = connectionSteps_->rowCount();
    for(int i = 0; i < count; ++i)
    {
        auto cur = connectionSteps_->at(i);
        maxFirst = qMax(maxFirst,cur->getUtilisationFirst());
        maxSecond = qMax(maxSecond,cur->getUtilisationSecond());
    }
    utilisationFirst_ = maxFirst;
    utilisationSecond_ = maxSecond;

    bool start = true;
    auto cur = connectionSteps_->at(0);
    for(int i = 0; i < count; ++i)
    {
        cur = connectionSteps_->at(i);
        if (cur->hasMeansOfTransportation())
            break;
        if(!start)
            nrChanges_--;
        else
            start = false;
    }
    auto tmp = cur;
    platform_ = tmp->getDepPlatform();
    hasChangedDeparturePlatform_ = tmp->hasChangedDeparturePlatform();
    departureTime_ = tmp->getDepTime();
    arrivalTime_ = connectionSteps_->at(count - 1)->getArrTime();
}
