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

#ifndef STOPITEM_H
#define STOPITEM_H

#include "../domin/location.h"
#include "../util/duration.h"
#include "listitem.h"

#include <QDomNode>
#include <QDateTime>

class StopItem : public ListItem
{
    Q_OBJECT
public:
    StopItem(QObject *parent = nullptr) : ListItem(parent) {}
    StopItem(QDomNode domBasicStop,QDateTime date, QObject * parent = nullptr);
    ~StopItem();

    virtual QString getId() const;
    virtual QVariant data(int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    bool setData(const QVariant &value, int role);

    double getLatitude() const;
    double getLongitude() const;
    QString getExternalId() const;

    inline QString getPlatform() const;
    inline int getUtilisationFirst() const;
    inline int getUtilisationSecond() const;
    inline QString getDelay() const;
    inline QString getName() const;
    inline QDateTime getTime() const;
    inline bool hasDelay() const;
    inline bool hasChangedPlatform() const;

    inline void setDateTime(QDateTime t);

    enum Roles{StationRole=Qt::UserRole+1,
               PlatformRole,
               ArrivalTimeRole,
               DepartureTimeRole,
               UtilisationFirstRole,
               UtilisationSecondRole,
               HasArrivalTimeRole,
               HasDepartureTimeRole
              };


private:
    bool hasDelay_;
    bool hasArrTime_;
    bool hasDepTime_;
    bool hasDepDelay_;
    bool hasArrDelay_;
    bool hasChangedPlatform_;
    bool hasChangedArrPlatform_;
    bool hasChangedDepPlatform_;
    QString platform_;
    QString arrPlatform_;
    QString depPlatform_;
    Location *location_;
    int utilisationFirst_;
    int utilisationSecond_;
    QDateTime time_;
    QDateTime arrTime_;
    QDateTime depTime_;
    Duration delay_;
};

inline QDateTime StopItem::getTime() const { return time_;}

inline QString StopItem::getPlatform() const { return platform_;}

inline int StopItem::getUtilisationFirst() const { return utilisationFirst_;}

inline int StopItem::getUtilisationSecond() const { return utilisationSecond_;}

inline QString StopItem::getDelay() const { return delay_.toString();}

inline QString StopItem::getName() const { return location_->getName();}

inline bool StopItem::hasDelay() const { return hasDelay_;}

inline bool StopItem::hasChangedPlatform() const { return hasChangedPlatform_;}

inline void StopItem::setDateTime(QDateTime t) { time_ = t;}

#endif // STOP_H
