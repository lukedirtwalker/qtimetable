#include "sbbquerycontainer.h"
//#include <QSystemDeviceInfo>
//#include <QtSystemInfo/QSystemInfo>

//using namespace QtMobility;

SBBQueryContainer::SBBQueryContainer()
{
    // TODO device info
//    QSystemInfo info;
//    QSystemDeviceInfo dInfo;
    domStaticElementName_ = "ReqC";
    domStaticElementAttributes_.insert("lang","EN");
//    domStaticElementAttributes_.insert("prod",QString(dInfo.manufacturer() + " " + dInfo.model()));
    domStaticElementAttributes_.insert("prod", "Jolla Jolla");
//    domStaticElementAttributes_.insert("ver",info.version(QSystemInfo::Firmware));
    domStaticElementAttributes_.insert("ver", "1.0.7.6");
    domStaticElementAttributes_.insert("accessId","sbuR5gsaDCEzWpCzSuEnxJOmDbb5vEM1vf0tWwjY3s6eab2uj8dAiLvjisGKDnN");
}

QDomElement SBBQueryContainer::toXML(QDomDocument &query)
{
    QString instr = "version=\"ISO-8859-1\" encoding=\"1.0\"";
    query.appendChild(query.createProcessingInstruction("xml", instr));
    return Serializable::toXML(query);
}
