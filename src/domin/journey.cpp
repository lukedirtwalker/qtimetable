/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include "journey.h"

#include "../util/qdomnodeiterator.h"

#include <QDebug>
#include <QStringList>

Journey::Journey(const QString &meansOfTransportation)
    : meansOfTransport_(meansOfTransportation)
{
    hasMOT_ = !meansOfTransport_.isEmpty();
}

Journey::Journey(const QDomNode &domJourney, QDateTime date, bool isWalk) : hasMOT_{false}
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

void Journey::createWalk(const QDomNode &domWalk, QDateTime date)
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

    auto domWalkChild = domWalk.firstChild();
    while(!domWalkChild.isNull())
    {
        QString t = domWalkChild.toElement().tagName();
        if("Duration" == t)
        {
            QString timeString = domWalkChild.toElement().elementsByTagName("Time")
                    .at(0).toElement().text().trimmed();
            // XXX: We assume that we only have to walk at most 59 mins...
            // also days are ignored
            timeString = timeString.split("d").at(1);
            QDateTime timeParsed = QDateTime::fromString(timeString, "hh:mm:ss");
            meansOfTransportDetail_.prepend(timeParsed.toString("m").append(" min "));
        }
        else if("JourneyAttributeList" == t)
        {
            meansOfTransport_ = domWalkChild.toElement()
                    .elementsByTagName("JourneyAttribute").at(0).toElement()
                    .elementsByTagName("Attribute").at(0).toElement()
                    .elementsByTagName("Text").at(0).toElement()
                    .text().trimmed();
            hasMOT_ = !meansOfTransport_.isEmpty();
        }
        domWalkChild = domWalkChild.nextSibling();
    }

}

void Journey::createJourney(const QDomNode &domJourney, QDateTime date)
{
    auto domJourneyChild = domJourney.firstChild();
    while(!domJourneyChild.isNull())
    {
        QString t = domJourneyChild.toElement().tagName();
        if(t == "JHandle")
        {
            jHandlecycle_ = domJourneyChild.toElement().attributeNode("cycle")
                    .value().trimmed().toLatin1();
            jHandlepuic_ = domJourneyChild.toElement().attributeNode("puic")
                    .value().trimmed().toLatin1();
            jHandletNr_ = domJourneyChild.toElement().attributeNode("tNr")
                    .value().trimmed().toLatin1();
        }
        else if(t == "JourneyAttributeList")
        {
            QDomNodeList domJourneyAttributes = domJourneyChild.toElement()
                    .elementsByTagName("JourneyAttribute");
            for(const auto& domJ : domJourneyAttributes)
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
                        for(const auto& node : variants)
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
                        for(const auto& node : variants)
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
            QDomNodeList domBasicStops = domJourneyChild.toElement()
                    .elementsByTagName("BasicStop");
            for(auto stop : domBasicStops)
                stopovers_.append(new StopItem(stop, date));
        }
        domJourneyChild = domJourneyChild.nextSibling();
    }
}
