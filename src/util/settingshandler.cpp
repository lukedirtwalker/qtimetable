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

#include "settingshandler.h"

#include "../listitems/locationitem.h"

static const QString saveStations_ {"saveStations"};
static const QString depStation_ {"depStation"};
static const QString arrStation_ {"arrStation"};
static const QString viaStation_ {"viaStation"};

QSharedPointer<LocationItem> SettingsHandler::depStation()
{
    return stationItem(depStation_);
}

QSharedPointer<LocationItem> SettingsHandler::arrStation()
{
    return stationItem(arrStation_);
}

QSharedPointer<LocationItem> SettingsHandler::viaStation()
{
    return stationItem(viaStation_);
}

void SettingsHandler::setDepStation(QSharedPointer<LocationItem> depSave)
{
    setStationItem(depStation_, depSave);
}

void SettingsHandler::setArrStation(QSharedPointer<LocationItem> arrSave)
{
    setStationItem(arrStation_, arrSave);
}

void SettingsHandler::setViaStation(QSharedPointer<LocationItem> viaSave)
{
    setStationItem(viaStation_, viaSave);
}

bool SettingsHandler::saveStations() const
{
   return settings_.value(saveStations_, true).toBool();
}

void SettingsHandler::setSaveStations(const bool save)
{
    settings_.setValue(saveStations_, save);
}

QSharedPointer<LocationItem> SettingsHandler::stationItem(const QString &key)
{
    return LocationItem::createFromSettings(settings_, key);
}

void SettingsHandler::setStationItem(const QString &groupKey,
                                     QSharedPointer<LocationItem> station)
{
    if (station)
        station->saveToSettings(settings_, groupKey);
    else
        settings_.remove(groupKey);
}
