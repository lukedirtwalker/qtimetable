import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: connectionStepPage

    property alias model: connectionSteps.model
    property string from: ""
    property string to: ""
    property string date: ""
    property string time: ""

    SilicaListView {
        id: connectionSteps
        anchors.fill: parent

        header: Column {
            id: column
            width: connectionStepPage.width
            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("Detail")
            }

            ConnectionOverviewHeader {
                id: overviewHeader
                fromStationText: connectionStepPage.from
                toStationText: connectionStepPage.to
                date: connectionStepPage.date
                time: connectionStepPage.time
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
                        color: Theme.highlightColor
                    }

                    Label{
                        id: arrTimeLabel
                        width: parent.width * 0.18
                        text: qsTr("Pl.")
                        color: Theme.highlightColor
                    }
                    Label{
                        id: durTimeLabel
                        //                    width: parent.width * 0.5
                        text: qsTr("Stop / Remark")
                        color: Theme.highlightColor
                    }
                }
            }
        }

        VerticalScrollDecorator {}

        clip: true
        pressDelay: 0

        delegate: ConnectionStepItem {}
    }
}
