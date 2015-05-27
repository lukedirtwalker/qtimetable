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
    id: connectionsPage

    property alias model: searchSuggestionList.model
    property string from: ""
    property string to: ""
    property string date: ""
    property string time: ""

    Component.onCompleted: timeTableHandler.lookupConnection()

    Component.onDestruction : {
        searchSuggestionList.model.clear()
    }

    SilicaListView {
        id: searchSuggestionList
        anchors.fill: parent

        header: Column {
            id: column
            width: connectionsPage.width
            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("Connections")
            }

            ConnectionOverviewHeader {
                id: overviewHeader
                fromStationText: connectionsPage.from
                toStationText: connectionsPage.to
                date: connectionsPage.date
                time: connectionsPage.time
            }

            Item {
                id: tableHeader

                width: parent.width
                height: Theme.itemSizeSmall

                Row {
                    id: headerRow
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    spacing: Theme.paddingMedium
                    Label{
                        id: depTimeLabel
                        width: parent.width * 0.18
                        text: qsTr("Dep")
                        color: Theme.highlightColor
                    }

                    Label{
                        id: arrTimeLabel
                        width: parent.width * 0.18
                        text: qsTr("Arr")
                        color: Theme.highlightColor
                    }
                    Label{
                        id: durTimeLabel
                        width: parent.width * 0.18
                        text: qsTr("Dur")
                        color: Theme.highlightColor
                    }
                    Label{
                        id: chgLabel
                        width: parent.width * 0.18
                        text: qsTr("Chg")
                        color: Theme.highlightColor
                    }
                    Label {
                        id: platLabel
                        width: parent.width * 0.18
                        text: qsTr("Plat.")
                        color: Theme.highlightColor
                    }
                }
            }
        }


        delegate: ConnectionOverviewItem {
            id: overviewItem
            onClicked: {
                pageStack.push(Qt.resolvedUrl("ConnectionStep.qml"),
                               {"model" : searchSuggestionList.model.getConnectionSteps(index),
                                   "from" : connectionsPage.from,
                                   "to" : connectionsPage.to,
                                   "time" : Qt.formatDateTime(dep, "hh:mm"),
                                   "date" : Qt.formatDateTime(dep, "dd.MM")})
            }
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Add to favorites")
                onClicked: timeTableHandler.addFavoriteConnection()
                enabled: !timeTableHandler.isFavoriteConnection()
                visible: enabled
            }

            MenuItem {
                text: qsTr("Earlier")
                onClicked: timeTableHandler.searchEarlier()
            }
            visible: !timeTableHandler.busy
        }

        PushUpMenu {
            MenuItem {
                text: qsTr("Later")
                onClicked: timeTableHandler.searchLater()
            }
            visible: !timeTableHandler.busy
        }
    }
    BusyIndicator {
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: timeTableHandler.busy
    }
}
