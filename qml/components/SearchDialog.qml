import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    id: searchDialog

    property string searchText
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
        timeTableHandler.setStation(selectIndex, type)
    }

    DialogHeader {
        id: header
        acceptText: typeString
    }

    SearchField { // should be outside such that we keep focus
        id: stationSearch
        width: parent.width
        anchors.top: header.bottom
        text: searchText
        placeholderText: qsTr("Enter %1 station".arg(typeString.toLowerCase()))
        onTextChanged: {
            timeTableHandler.startQuery(text, type)
        }
    }

    SilicaListView {
        id: searchSuggestionList
        width: parent.width
        anchors.top: stationSearch.bottom
        anchors.bottom: parent.bottom
        clip: true
        pressDelay: 0

        VerticalScrollDecorator {}

        delegate: SearchListItem {
            text: stationSearch.text.length > 0 ? Theme.highlightText(model.stationName, stationSearch.text, Theme.highlightColor) : model.stationName
            onClicked: {
                selectIndex = index;
                pageStack.navigateForward()
            }
        }
    }
}
