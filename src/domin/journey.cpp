#include "journey.h"

#include "../util/qdomnodeiterator.h"

Journey::Journey(QString meansOfTransportation)
    : meansOfTransport_(meansOfTransportation), hasMOT_{false} {}

Journey::Journey(QDomNode domJourney, QDateTime date) : hasMOT_{false}
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
                            .at(0).toElement().text().trimmed().toLatin1();
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

Journey::~Journey()
{
    if(stopovers_.size() > 0)
    {
        qDeleteAll(stopovers_);
        stopovers_.clear();
    }
}
