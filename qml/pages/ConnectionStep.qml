import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: connectionStepPage

    property alias model: connectionSteps.model
    property alias from: overviewHeader.fromStationText
    property alias to: overviewHeader.toStationText
    property alias date: overviewHeader.date
    property alias time: overviewHeader.time

    Column {
        id: column
        width: connectionStepPage.width
        spacing: Theme.paddingSmall

        PageHeader {
            title: qsTr("Detail")
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
                    width: parent.width * 0.18
                    text: qsTr("Time")
                }

                Label{
                    id: arrTimeLabel
                    width: parent.width * 0.18
                    text: qsTr("Pl.")
                }
                Label{
                    id: durTimeLabel
//                    width: parent.width * 0.5
                    text: qsTr("Stop / Remark")
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
        id: connectionSteps
        anchors {
            left: parent.left
            right: parent.right
            top: column.bottom
            bottom: parent.bottom
        }

        VerticalScrollDecorator {}

        clip: true
        pressDelay: 0

        delegate: ConnectionStepItem {}
    }
}
