import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: searchDialog

    property string searchText
    property string selectedText
    property int type
    property string typeString
    property alias model: searchSuggestionList.model

    property int selectIndex : 0;

    Component.onDestruction: {
        searchDialog.model.clear()
    }

    onOpened: {
        stationSearch.forceActiveFocus()
    }

    onAccepted: {
        selectedText = timeTableHandler.setStation(selectIndex, type)
    }

    DialogHeader {
        acceptText: typeString
    }

    // TODO maybe use accept destination?

    Item {
        id: stationSearchWrap
        width: parent.width
        height: Theme.itemSizeMedium
        anchors.top: parent.top
        anchors.topMargin: Theme.itemSizeSmall

        SearchField { // should be outside such that we keep focus
            id: stationSearch
            anchors.fill: parent
            text: searchText
            placeholderText: qsTr("Enter %1 station".arg(typeString.toLowerCase()))
            onTextChanged: {
                timeTableHandler.startQuery(text, type)
            }
        }
    }

    SilicaListView {
        id: searchSuggestionList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: stationSearchWrap.bottom
        anchors.topMargin: Theme.paddingLarge
        anchors.bottom: parent.bottom

        delegate: SearchListItem {
            onClicked: {
                selectIndex = index;
                searchDialog.accept()
            }
        }
    }
}
