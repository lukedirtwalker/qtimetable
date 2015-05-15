import QtQuick 2.0
import Sailfish.Silica 1.0

Column{
    id: listItem
    width: parent.width
    height: Theme.itemSizeLarge

    property alias text: station.text
    property alias labelText: label.text
    property alias stationText: station.placeholderText
    property int type
    property string typeString
    property variant listModel
    property variant handler

    signal stationSelected()

    Label{
        id: label
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
        color: Theme.highlightColor
    }

    DeletableTextField {
        id: station
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
        anchors.right: parent.right
        font.pixelSize: Theme.fontSizeMedium
        onClicked: { openSearch() }

        onDeleted: {
            handler.clearStation(type)
            openSearch()
        }
    }

    function openSearch() {
        var dialog = pageStack.push("SearchDialog.qml",
                       {"searchText": station.text,
                           "type": listItem.type,
                           "typeString": listItem.typeString,
                           "model" : listModel,
                           "acceptDestination" : timeTablePage,
                           "acceptDestinationAction" : PageStackAction.Pop})
        dialog.accepted.connect(stationSelected)
    }
}
