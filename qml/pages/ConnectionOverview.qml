import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"

Page {
    id: connectionsPage

    property alias model: searchSuggestionList.model

    SilicaListView {
        id: searchSuggestionList
        anchors.fill: parent
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.top: stationSearchWrap.bottom
//        anchors.topMargin: Theme.paddingLarge
//        anchors.bottom: parent.bottom

        delegate: ConnectionOverviewItem {}
    }

}
