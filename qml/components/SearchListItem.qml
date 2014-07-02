import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: searchListItem
    width: parent.width
    height: Theme.itemSizeSmall

    property alias text: stationNameLabel.text
    signal selected


    Label {
        id: stationNameLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
    }

    MouseArea {
        id: stationMouseArea
        anchors.fill: parent
        onClicked: {
            stationNameLabel.color = Theme.highlightColor
            searchListItem.selected()
        }
    }
}
