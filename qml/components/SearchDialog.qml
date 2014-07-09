import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: searchDialog

    property string searchText
    property string selectedText
    property int type
    property alias model: searchSuggestionList.model

    Component.onDestruction: {
        searchDialog.model.clear()
    }

    // TODO it would be nicer to just select the first entry?
    canAccept: false

    onOpened: {
        stationSearch.forceActiveFocus()
    }

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
            placeholderText: qsTr("Enter station")
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
                timeTableHandler.setStation(index, type)
                selectedText = stationName
                searchDialog.canAccept = true
                searchDialog.accept()
            }
        }
    }
}
