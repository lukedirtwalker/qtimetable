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
                    spacing: Theme.paddingLarge

                    TimeTableInput {
                        id: fromStation
                        labelText: qsTr("From")
                        stationText: qsTr("Location")
                        text: timeTableHandler.depStation
                        type: 0 // dep
                        typeString: qsTr("Departure")
                        listModel: depStationModel
                        handler: timeTableHandler
                        onStationSelected: adaptAttachPage()
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
                        onStationSelected: adaptAttachPage()
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
                }

                IconButton {
                    id: oppDirection
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -parent.height / 4 + height / 2
                    width: Theme.iconSizeMedium
                    height: width;
                    icon.source: "image://theme/icon-m-shuffle"
                    onClicked: {
                        if(timeTableHandler.switchStations()) {
                            oppDirection.state == "rotated" ? oppDirection.state = "" : oppDirection.state = "rotated"
                        }
                    }
                    icon.transform: Rotation{
                        id: rotation
                        axis{x: 1; y: 0; z: 0}
                        origin.x: oppDirection.width/2
                        origin.y: oppDirection.height/2
                    }

                    states: State {
                        name: "rotated"
                        PropertyChanges { target: rotation;  angle: 180}
                    }

                    transitions: Transition {
                        NumberAnimation { target: rotation; properties: "angle"; duration: 250; easing.type: Easing.InOutQuad }
                    }
                }
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

            PageHeader {
                title: qsTr("Favorites")
                visible: favoritesRepeater.count
            }

            Grid {
                id: view
                width: parent.width
                clip: true
                columns: 2
                visible: favoritesRepeater.count

                Repeater {
                    id: favoritesRepeater
                    model: favoritesModel
                    delegate: FavoriteConnectionItem {
                        depStation: DepStation
                        arrStation: ArrStation
                        viaStation: ViaStation
                        hasVia: HasViaStation
                        onClicked: {
                            timeTableHandler.setConnectionToFavoriteConnection(index)
                            adaptAttachPage()
                            pageStack.navigateForward()
                        }
                    }
                }
            }

            VerticalScrollDecorator { }
        }

        PullDownMenu {
            MenuItem{
                text: qsTr("Settings & About")
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

    Component.onCompleted: {
        timeTableHandler.modelFavoriteConnections()
    }

    onStatusChanged: {
        if (status === PageStatus.Active) {
                adaptAttachPage();
        }
    }

    function adaptAttachPage() {
        if(fromStation.text === "") {
            pageStack.pushAttached(Qt.resolvedUrl("../components/SearchDialog.qml"),
                           {"searchText": fromStation.text,
                               "type": fromStation.type,
                               "typeString": fromStation.typeString,
                               "model" : fromStation.listModel,
                               "acceptDestination" : timeTablePage,
                               "acceptDestinationAction" : PageStackAction.Pop})
            return 0
        }
        if(toStation.text === "") {
            pageStack.pushAttached(Qt.resolvedUrl("../components/SearchDialog.qml"),
                           {"searchText": toStation.text,
                               "type": toStation.type,
                               "typeString": toStation.typeString,
                               "model" : toStation.listModel,
                               "acceptDestination" : timeTablePage,
                               "acceptDestinationAction" : PageStackAction.Pop})
            return 0
        }

        pageStack.pushAttached(Qt.resolvedUrl("ConnectionOverview.qml"),
                       {"model" : connectionModel,
                           "from": fromStation.text,
                           "to": toStation.text,
                           "date": Qt.formatDate(timeHandler.date, "dd.MM"),
                           "time": timeButton.value})
        return 1
    }
}
