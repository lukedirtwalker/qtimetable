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
        color: searchListItem.highlighted ?
                   Theme.highlightColor : Theme.primaryColor
    }

    IconButton {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        icon.source: favorite ? "image://theme/icon-m-favorite-selected" :
                                "image://theme/icon-m-favorite"
        onClicked: {
            favorite = !favorite;
        }
        highlighted: down || searchListItem.highlighted
    }
}
