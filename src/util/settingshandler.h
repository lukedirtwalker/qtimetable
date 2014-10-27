#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QtCore/QSharedPointer>

class QSettings;

class LocationItem;

class SettingsHandler
{
public:
    SettingsHandler();

    QSharedPointer<LocationItem> depStation();
    QSharedPointer<LocationItem> arrStation();
    QSharedPointer<LocationItem> viaStation();

    void setDepStation(QSharedPointer<LocationItem> depSave);
    void setArrStation(QSharedPointer<LocationItem> arrSave);
    void setViaStation(QSharedPointer<LocationItem> viaSave);

    bool saveStations() const;
    void setSaveStations(const bool save);

private:
    QSettings *settings_;

    QSharedPointer<LocationItem> stationItem(const QString &key);
    void setStationItem(const QString &groupKey, QSharedPointer<LocationItem> station);
};

#endif // SETTINGSHANDLER_H
