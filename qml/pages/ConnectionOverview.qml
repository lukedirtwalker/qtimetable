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
                text: qsTr("Earlier")
                onClicked: timeTableHandler.searchEarlier()
            }
        }

        PushUpMenu {
            MenuItem {
                text: qsTr("Later")
                onClicked:  timeTableHandler.searchLater()
            }
        }
    }
}
