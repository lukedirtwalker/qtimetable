import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"


Page {
    id: timeTablePage

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

            Row {
                anchors {
                    left: parent.left
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }

                Column {
                    width: parent.width - oppDirection.width

                    TimeTableInput {
                        id: fromStation
                        labelText: qsTr("From")
                        stationText: qsTr("Location")
                        text: timeTableHandler.depStation
                        type: 0 // dep
                        typeString: qsTr("Departure")
                        listModel: depStationModel
                        handler: timeTableHandler
                    }

                    TimeTableInput {
                        id: toStation
                        labelText: qsTr("To")
                        stationText: qsTr("Location")
                        text: timeTableHandler.arrStation
                        type: 1 // arr
                        typeString: qsTr("Arrival")
                        listModel: arrStationModel
                        handler: timeTableHandler
                    }
                }

                IconButton {
                    id: oppDirection
                    anchors.verticalCenter: parent.verticalCenter
                    width: Theme.iconSizeMedium
                    height: width;
                    icon.source: "image://theme/icon-m-mobile-network"
                    onClicked: {
                        if(timeTableHandler.switchStations()) {
                            oppDirection.state == "rotated" ? oppDirection.state = "" : oppDirection.state = "rotated"
                        }
                    }

                    states: State {
                        name: "rotated"
                        PropertyChanges { target: oppDirection; rotation: 180 }
                    }

                    transitions: Transition {
                        RotationAnimation { duration: 500; direction: RotationAnimation.Clockwise }
                    }
                }
            }
            TimeTableInput {
                id: viaStation
                labelText: qsTr("Via")
                stationText: qsTr("Location")
                text: timeTableHandler.viaStation
                type: 2 // via
                typeString: qsTr("Via")
                listModel: viaStationModel
                handler: timeTableHandler
            }

            DepArrSwitch {
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingLarge
                onArrivalChanged: {
                    timeTableHandler.setArrival(arrival)
                }
            }
            Row {
                id: timeRow
                anchors {
                    left: parent.left
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }

                ValueButton {
                    id: dateButton
                    width: parent.width * 0.5
                    anchors.verticalCenter: parent.verticalCenter
                    value: Qt.formatDate(timeHandler.date,
                                         "ddd dd.MM.yyyy")

                    onClicked: {
                        var dialog = pageStack.push(
                                    "Sailfish.Silica.DatePickerDialog", {
                                        date: timeHandler.date})
                        dialog.accepted.connect(function() {
                            timeHandler.setDate(dialog.year, dialog.month,
                                                dialog.day)
                        })
                    }
                }

                ValueButton {
                    id: timeButton
                    width: parent.width * 0.5 - refresherButton.width
                    anchors.verticalCenter: parent.verticalCenter
                    value: Qt.formatTime(timeHandler.time, "hh:mm")

                    onClicked:{
                        var dialog = pageStack.push(
                                    "Sailfish.Silica.TimePickerDialog", {
                                        hour: timeHandler.time.getHours(),
                                        minute: timeHandler.time.getMinutes()})

                        dialog.accepted.connect(function() {
                            timeHandler.setTime(dialog.hour, dialog.minute)
                        })
                    }
                }

                IconButton {
                    id: refresherButton
                    width: Theme.iconSizeMedium
                    height: width;
                    anchors.verticalCenter: parent.verticalCenter
                    icon.source: "image://theme/icon-m-refresh"
                    onClicked: {
                        timeHandler.updateTime()
                    }
                }
            }

            Button {
                id: searchButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Search")
                onClicked: {
                    tryLookup()
                }
            }
        }

        PullDownMenu {
            MenuItem{
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
            }
            //            MenuItem{
            //                id: depArrMenu
            //                text: qsTr("Departure/Arrival")
            //                // TODO: Find better solution than {}
            //                onClicked: pageStack.replace(Qt.resolvedUrl("DepArr.qml"), {}, PageStackAction.Immediate)
            //            }
            //            MenuItem{
            //                id: favMenu
            //                text: qsTr("Favorites")
            //                // TODO: Find better solution than {}
            //                onClicked: pageStack.replace(Qt.resolvedUrl("Favorites.qml"), {}, PageStackAction.Immediate)
            //            }
        }
    }

    function tryLookup() {
        if(fromStation.text === "") {
            pageStack.push(Qt.resolvedUrl("../components/SearchDialog.qml"),
                           {"searchText": fromStation.text,
                               "type": fromStation.type,
                               "typeString": fromStation.typeString,
                               "model" : fromStation.listModel})
            return
        }
        if(toStation.text === "") {
            pageStack.push(Qt.resolvedUrl("../components/SearchDialog.qml"),
                           {"searchText": toStation.text,
                               "type": toStation.type,
                               "typeString": toStation.typeString,
                               "model" : toStation.listModel})
            return
        }

        timeTableHandler.lookupConnection()
        pageStack.push(Qt.resolvedUrl("ConnectionOverview.qml"),
                       {"model" : connectionModel,
                           "from": fromStation.text,
                           "to": toStation.text,
                           "date": Qt.formatDate(timeHandler.date, "dd.MM"),
                           "time": timeButton.value})
    }
}
