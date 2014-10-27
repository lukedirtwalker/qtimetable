#include "settingshandler.h"

#include <QtCore/QSettings>

#include "../listitems/locationitem.h"
#include "../db/databasehandler.h"

static const QString saveStations_ {"saveStations"};
static const QString depStation_ {"depStation"};
static const QString arrStation_ {"arrStation"};
static const QString viaStation_ {"viaStation"};

static const QString dbId_ {"dbId"};

SettingsHandler::SettingsHandler()
    : settings_{new QSettings()}
{}

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
   return settings_->value(saveStations_, true).toBool();
}

void SettingsHandler::setSaveStations(const bool save)
{
    settings_->setValue(saveStations_, save);
}

QSharedPointer<LocationItem> SettingsHandler::stationItem(const QString &key)
{
    settings_->beginGroup(key);
    int id = settings_->value(dbId_, -1).toInt();
    settings_->endGroup();
    if (id > -1)
        return QSharedPointer<LocationItem>(DatabaseHandler::getInstance().selectById(id));
    return QSharedPointer<LocationItem>();
}

void SettingsHandler::setStationItem(const QString &groupKey,
                                     QSharedPointer<LocationItem> station)
{
    settings_->beginGroup(groupKey);
    if (station)
        settings_->setValue(dbId_, station->dbId());
    else
        settings_->setValue(dbId_, -1);
    settings_->endGroup();
}
