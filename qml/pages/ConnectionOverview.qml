import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: connectionsPage

    property alias model: searchSuggestionList.model
    property alias from: overviewHeader.fromStationText
    property alias to: overviewHeader.toStationText
    property alias date: overviewHeader.date
    property alias time: overviewHeader.time

    Component.onDestruction : {
        searchSuggestionList.model.clear()
    }

    Column {
        id: column
        width: connectionsPage.width
        spacing: Theme.paddingSmall

        PageHeader {
            title: qsTr("Overview")
        }

        ConnectionOverviewHeader {
            id: overviewHeader
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
                    width: parent.width / 4
                    text: qsTr("Dep")
                }

                Label{
                    id: arrTimeLabel
                    width: parent.width / 4
                    text: qsTr("Arr")
                }
                Label{
                    id: durTimeLabel
                    width: parent.width / 4
                    text: qsTr("Dur")
                }
                Label{
                    id: chgLabel
                    width: parent.width / 4
                    text: qsTr("Chg")
                }
            }

            Separator {
                height: 2
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                    bottom: parent.bottom
                }
                color: Theme.primaryColor
            }
        }
    }
    SilicaListView {
        id: searchSuggestionList
        anchors {
            left: parent.left
            right: parent.right
            top: column.bottom
            bottom: parent.bottom
        }

        delegate: ConnectionOverviewItem {
            id: overviewItem
            onClicked: {
                pageStack.push(Qt.resolvedUrl("ConnectionStep.qml"),
                               {"model" : searchSuggestionList.model.getConnectionSteps(index),
                                   "from" : overviewHeader.fromStationText,
                                   "to" : overviewHeader.toStationText,
                                   "time" : Qt.formatDateTime(dep, "hh:mm"),
                                   "date" : Qt.formatDateTime(dep, "dd.MM")})
            }
        }
    }
}
