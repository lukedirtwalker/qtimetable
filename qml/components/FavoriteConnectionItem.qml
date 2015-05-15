import QtQuick 2.0
import Sailfish.Silica 1.0

ListItem {
    id: favConnectionItem
    property bool hasVia: false
    property alias depStation: depStation.text
    property alias arrStation: arrStation.text
    property string viaStation: ""

    width: parent.width / 2
    contentHeight: content.height

    menu: ContextMenu {
        MenuItem {
            text: qsTr("Remove from favorites")
            onClicked: {
                remorseAction("Remove from favorites", function() {timeTableHandler.removeFavoriteConnection(DbId);})
            }
        }
    }

    Column {
        id: content
        spacing: Theme.paddingSmall
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }

        Item {
            id: spacerTop
            width: parent.width
            height: Theme.paddingSmall
        }

        Label {
            id: depStation
            width: parent.width
            truncationMode: TruncationMode.Fade
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
        }

        Label {
            id: viaStation
            width: parent.width
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
            text: favConnectionItem.hasVia ? favConnectionItem.viaStation : qsTr("To")
            color: Theme.secondaryHighlightColor
        }

        Label {
            id: arrStation
            width: parent.width
            truncationMode: TruncationMode.Fade
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
        }

        Item {
            id: spacerBottom
            width: parent.width
            height: Theme.paddingSmall
        }
    }

    Image {
        id: gradientImage

        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        width: Math.min(parent.width, sourceSize.width)
        height: Math.min(parent.height, sourceSize.height)

        opacity: 0.15
        source: "image://theme/graphic-gradient-corner?" + Theme.highlightBackgroundColor
    }
}
