import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"


Page {
    id: depArrPage
    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column{
            id: column

            width: depArrPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Departure/Arrival")
            }
        }




        PullDownMenu {
            MenuItem{
                id: timeTableMenu
                text: qsTr("Timetable")
                // TODO: Find better solution than {}
                onClicked: pageStack.replace(Qt.resolvedUrl("TimeTable.qml"), {}, PageStackAction.Immediate)
            }
            MenuItem{
                id: favMenu
                text: qsTr("Favorites")
                // TODO: Find better solution than {}
                onClicked: pageStack.replace(Qt.resolvedUrl("Favorites.qml"), {}, PageStackAction.Immediate)
            }
        }
        PushUpMenu {
            MenuItem{
                text:qsTr("Help")
                onClicked: pageStack.push(Qt.resolvedUrl("Help.qml"))
            }

            MenuItem{
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }

            MenuItem{
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("Settings.qml"))
            }
        }
    }


}
