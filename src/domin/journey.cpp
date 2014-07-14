#include "journey.h"

#include "../util/qdomnodeiterator.h"

#include <QDebug>
#include <QStringList>

Journey::Journey(QString meansOfTransportation)
    : meansOfTransport_(meansOfTransportation)
{
    hasMOT_ = !meansOfTransport_.isEmpty();
}

Journey::Journey(QDomNode domJourney, QDateTime date, bool isWalk) : hasMOT_{false}
{
    if(isWalk)
        createWalk(domJourney, date);
    else
        createJourney(domJourney, date);
}

Journey::~Journey()
{
    if(stopovers_.size() > 0)
    {
        qDeleteAll(stopovers_);
        stopovers_.clear();
    }
}

void Journey::createWalk(QDomNode domWalk, QDateTime date)
{
    Q_UNUSED(date)
//    <Walk length="181">
//        <Duration>
//            <Time>00d00:07:00</Time>
//        </Duration>
//        <JourneyAttributeList>
//            <JourneyAttribute>
//                <Attribute code="Y " priority="5">
//                    <AttributeVariant type="NORMAL">
//                        <Text>Walk</Text>
//                    </AttributeVariant>
//                </Attribute>
//            </JourneyAttribute>
//        </JourneyAttributeList>
//    </Walk>
    // TODO There are som translation strings in here (meters, min)
    meansOfTransportDetail_ = domWalk.attributes().namedItem("length").nodeValue().append(" meters");

    domWalk = domWalk.firstChild();
    while(!domWalk.isNull())
    {
        QString t = domWalk.toElement().tagName();
        if("Duration" == t)
        {
            QString timeString = domWalk.toElement().elementsByTagName("Time")
                    .at(0).toElement().text().trimmed();
            // XXX: We assume that we only have to walk at most 59 mins...
            // also days are ignored
            timeString = timeString.split("d").at(1);
            QDateTime timeParsed = QDateTime::fromString(timeString, "hh:mm:ss");
            meansOfTransportDetail_.prepend(timeParsed.toString("m").append(" min "));
        }
        else if("JourneyAttributeList" == t)
        {
            meansOfTransport_ = domWalk.toElement()
                    .elementsByTagName("JourneyAttribute").at(0).toElement()
                    .elementsByTagName("Attribute").at(0).toElement()
                    .elementsByTagName("Text").at(0).toElement()
                    .text().trimmed();
            hasMOT_ = !meansOfTransport_.isEmpty();
        }
        domWalk = domWalk.nextSibling();
    }

}

void Journey::createJourney(QDomNode domJourney, QDateTime date)
{
    domJourney = domJourney.firstChild();
    while(!domJourney.isNull())
    {
        QString t = domJourney.toElement().tagName();
        if(t == "JHandle")
        {
            jHandlecycle_ = domJourney.toElement().attributeNode("cycle")
                    .value().trimmed().toLatin1();
            jHandlepuic_ = domJourney.toElement().attributeNode("puic")
                    .value().trimmed().toLatin1();
            jHandletNr_ = domJourney.toElement().attributeNode("tNr")
                    .value().trimmed().toLatin1();
        }
        else if(t == "JourneyAttributeList")
        {
            QDomNodeList domJourneyAttributes = domJourney.toElement()
                    .elementsByTagName("JourneyAttribute");
            for(auto domJ : domJourneyAttributes)
            {
                QDomElement domJourneyAttribute = domJ.toElement().
                        elementsByTagName("Attribute").at(0).toElement();
                QString type = domJourneyAttribute.attributeNode("type").value();

                if(type == "NAME")
                {
                    meansOfTransport_ = domJourneyAttribute
                            .elementsByTagName("Text").at(0).toElement()
                            .text().trimmed().toLatin1();
                    hasMOT_ = !meansOfTransport_.isEmpty();
                }
                else if(type == "DIRECTION")
                {
                    direction_ = domJourneyAttribute.elementsByTagName("Text")
                            .at(0).toElement().text().trimmed();
                }
                else if("NAMEFORMATTED" == type)
                {
                    bool ok = false;
                    int code = domJourneyAttribute.attributeNode("code").value().toInt(&ok);
                    if(!ok) continue;
                    if(1 == code)
                    {
                        QDomNodeList variants = domJourneyAttribute.elementsByTagName("AttributeVariant");
                        for(auto node : variants)
                        {
                            if(node.attributes().namedItem("type").nodeValue() == "NORMAL")
                            {
                                meansOfTransport_ = node.toElement().elementsByTagName("Text").at(0).toElement().text().trimmed();
                            }
                        }
                        hasMOT_ = !meansOfTransport_.isEmpty();
                    }
                    else if(2 == code)
                    {
                        QDomNodeList variants = domJourneyAttribute.elementsByTagName("AttributeVariant");
                        for(auto node : variants)
                        {
                            if(node.attributes().namedItem("type").nodeValue() == "NORMAL")
                            {
                                meansOfTransportDetail_ = node.toElement().elementsByTagName("Text").at(0).toElement().text().trimmed();
                            }
                        }
                    }
                }
            }
        }
        else if(t == "PassList")
        {
            QDomNodeList domBasicStops = domJourney.toElement()
                    .elementsByTagName("BasicStop");
            for(auto stop : domBasicStops)
                stopovers_.append(new StopItem(stop, date));
        }
        domJourney = domJourney.nextSibling();
    }
}
