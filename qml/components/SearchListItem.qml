import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: searchListItem
    width: parent.width
    height: Theme.itemSizeSmall

    property alias text: stationNameLabel.text

    Label {
        id: stationNameLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
    }
}
