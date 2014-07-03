#include "journey.h"

Journey::Journey()
{
    this->mHasMOT = false;
}

Journey::Journey(QString meansOfTransportation)
{
    this->mMeansOfTransport = meansOfTransportation;
    this->mHasMOT = false;
}

Journey::Journey(QDomNode domJourney, QDateTime date)
{
    this->mHasMOT = false;

    domJourney = domJourney.firstChild();
    while(!domJourney.isNull())
    {
        QString t = domJourney.toElement().tagName();
        if(t == "JProg")
        {

        }
        else if(t == "JHandle")
        {
            this->mJHandlecycle = domJourney.toElement().attributeNode("cycle").value().toLatin1();
            while(this->mJHandlecycle.endsWith(' ')) this->mJHandlecycle.chop(1);

            this->mJHandlepuic = domJourney.toElement().attributeNode("puic").value().toLatin1();
            while(this->mJHandlepuic.endsWith(' ')) this->mJHandlepuic.chop(1);

            this->mJHandletNr = domJourney.toElement().attributeNode("tNr").value().toLatin1();
            while(this->mJHandletNr.endsWith(' ')) this->mJHandletNr.chop(1);
        }
        else if(t == "JourneyAttributeList")
        {
            QDomNodeList domJourneyAttributes = domJourney.toElement().elementsByTagName("JourneyAttribute");
            int count = domJourneyAttributes.count();
            for(int i=0;i<count;i++)
            {
                QDomElement domJourneyAttribute = domJourneyAttributes.at(i).toElement().elementsByTagName("Attribute").at(0).toElement();
                QString type = domJourneyAttribute.attributeNode("type").value();

                if(type == "NAME")
                {
                    this->mMeansOfTransport = domJourneyAttribute.elementsByTagName("Text").at(0).toElement().text().toLatin1();
                    while(this->mMeansOfTransport.endsWith( ' ' )) this->mMeansOfTransport.chop(1);
                    this->mHasMOT = !this->mMeansOfTransport.isEmpty();
                }
                else if(type == "DIRECTION")
                {
                    this->mDirection = domJourneyAttribute.elementsByTagName("Text").at(0).toElement().text().toLatin1();
                    while(this->mDirection.endsWith(' ')) this->mDirection.chop(1);
                }
            }
        }
        else if(t == "PassList")
        {
            QDomNodeList domBasicStops = domJourney.toElement().elementsByTagName("BasicStop");
            int count = domBasicStops.count();
            for(int i=0;i<count;i++)
            {
                StopItem *it = new StopItem(domBasicStops.at(i), date);
                this->mStopovers.append(it);
            }
        }
        domJourney = domJourney.nextSibling();
    }
}

Journey::~Journey()
{
    if(this->mStopovers.size() > 0)
    {
        qDeleteAll(this->mStopovers);
        this->mStopovers.clear();
    }
}

QList<StopItem *> Journey::getStopovers()
{
    return this->mStopovers;
}

bool Journey::hasMeansOfTransportation()
{
    return this->mHasMOT;
}

QString Journey::getMeansOfTransport() const
{
    return this->mMeansOfTransport;
}

QString Journey::getDirection() const
{
    return this->mDirection;
}

QString Journey::getJHandletNr()
{
    return this->mJHandletNr;
}

QString Journey::getJHandlecycle()
{
    return this->mJHandlecycle;
}

QString Journey::getJHandlepuic()
{
    return this->mJHandlepuic;
}
