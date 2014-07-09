import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: searchListItem
    width: parent.width
    height: Theme.itemSizeSmall

    Label {
        id: stationNameLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
        text: stationName
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
    }
}
