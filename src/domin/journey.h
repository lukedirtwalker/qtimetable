#ifndef JOURNEY_H
#define JOURNEY_H
#include "../listitems/stopitem.h"

#include <QDomNode>
#include <QVector>

class Journey
{
public:
    Journey();
    Journey(QString meansOfTransportation);
    Journey(QDomNode domJourney, QDateTime date);
    ~Journey();

    QString getMeansOfTransport() const;
    QString getDirection() const;

    QList<StopItem*> getStopovers();
    bool hasMeansOfTransportation();
    QString getJHandletNr();
    QString getJHandlepuic();
    QString getJHandlecycle();


private:
    QList<StopItem*> mStopovers;
    QString mDirection;
    QString mMeansOfTransport;
    QString mJHandletNr;
    QString mJHandlepuic;
    QString mJHandlecycle;
    bool mHasMOT;
};

#endif // CONNECTIONEDGE_H
