#ifndef JOURNEY_H
#define JOURNEY_H
#include "../listitems/stopitem.h"

#include <QDomNode>
#include <QVector>

class Journey
{
public:
    Journey() : hasMOT_{false} {}
    Journey(QString meansOfTransportation);
    Journey(QDomNode domJourney, QDateTime date);
    ~Journey();

    inline QString getMeansOfTransport() const;
    inline QString getDirection() const;

    inline QList<StopItem*> getStopovers();
    inline bool hasMeansOfTransportation();
    inline QString getJHandletNr();
    inline QString getJHandlepuic();
    inline QString getJHandlecycle();


private:
    QList<StopItem*> stopovers_;
    QString direction_;
    QString meansOfTransport_;
    QString jHandletNr_;
    QString jHandlepuic_;
    QString jHandlecycle_;
    bool hasMOT_;
};

inline QList<StopItem *> Journey::getStopovers() { return stopovers_;}

inline bool Journey::hasMeansOfTransportation() { return hasMOT_;}

inline QString Journey::getMeansOfTransport() const { return meansOfTransport_;}

inline QString Journey::getDirection() const { return direction_;}

inline QString Journey::getJHandletNr() { return jHandletNr_;}

inline QString Journey::getJHandlecycle() { return jHandlecycle_;}

inline QString Journey::getJHandlepuic() { return jHandlepuic_;}

#endif // CONNECTIONEDGE_H
