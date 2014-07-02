import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"


Page {
    id: timeTablePage

    onStatusChanged: {
        if(timeTablePage.status === PageStatus.Active) {
            dateButton.value = Qt.formatDate(timeHandler.getCurrentDate(),
                                             "ddd dd.MM.yyyy")
            timeButton.value = Qt.formatTime(timeHandler.getCurrentTime(),
                                             "hh:mm")
        }
    }

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column{
            id: column

            width: timeTablePage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Timetable")
            }

            TimeTableInput {
                labelText: qsTr("From")
                stationText: qsTr("Location")
                type: 0 // dep
                listModel: depStationModel
            }
            TimeTableInput {
                labelText: qsTr("To")
                stationText: qsTr("Location")
                type: 1 // arr
                listModel: arrStationModel
            }
            TimeTableInput {
                labelText: qsTr("Via")
                stationText: qsTr("Location")
                type: 2 // via
                listModel: viaStationModel
            }

            DepArrSwitch {
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingLarge
            }
            Row {
                id: timeRow
                width: parent.width
                height: 100
                ValueButton {
                    id: dateButton
                    label: ""
                    width: parent.width / 2
                    value: Qt.formatDate(timeHandler.getCurrentDate(),
                                         "ddd dd.MM.yyyy")

                    onClicked: {
                        var dialog = pageStack.push(
                                    "Sailfish.Silica.DatePickerDialog", {
                                        date: timeHandler.getCurrentDate()})
                        dialog.accepted.connect(function() {
                            timeHandler.setDate(dialog.year, dialog.month,
                                                dialog.day)
                            dateButton.value = Qt.formatDate(dialog.date,
                                                             "ddd dd.MM.yyyy")
                        })
                    }
                }

                ValueButton {
                    id: timeButton
                    label: ""
                    width: parent.width / 2
                    value: Qt.formatTime(timeHandler.getCurrentTime(), "hh:mm")

                    onClicked:{
                        var dialog = pageStack.push(
                                    "Sailfish.Silica.TimePickerDialog", {
                                        hour: timeHandler.getCurrentTime().getHours(),
                                        minute: timeHandler.getCurrentTime().getMinutes()})

                        dialog.accepted.connect(function() {
                            timeHandler.setTime(dialog.hour, dialog.minute)
                            timeButton.value = Qt.formatTime(dialog.time, "hh:mm")
                        })
                    }
                }
            }

            Button {
                id: searchButton
                text: qsTr("Search")
                onClicked: {
                    timeTableHandler.lookupConnection()
                }
            }

        }

        PullDownMenu {
            MenuItem{
                id: depArrMenu
                text: qsTr("Departure/Arrival")
                // TODO: Find better solution than {}
                onClicked: pageStack.replace(Qt.resolvedUrl("DepArr.qml"), {}, PageStackAction.Immediate)
            }
            MenuItem{
                id: favMenu
                text: qsTr("Favorites")
                // TODO: Find better solution than {}
                onClicked: pageStack.replace(Qt.resolvedUrl("Favorites.qml"), {}, PageStackAction.Immediate)
            }
        }
        PushUpMenu {
            MenuItem{
                text:qsTr("Help")
                onClicked: pageStack.push(Qt.resolvedUrl("Help.qml"))
            }

            MenuItem{
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }

            MenuItem{
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
            }
        }
    }


}
