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
