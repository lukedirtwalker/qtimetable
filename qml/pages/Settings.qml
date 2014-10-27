import QtQuick 2.0
import Sailfish.Silica 1.0

Page{
    id: settingsPage
    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: settingsPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Settings")
            }

            TextSwitch {
                checked: timeTableHandler.saveStations
                text: "Save stations on Exit"
                onClicked: {
                    timeTableHandler.saveStations = checked
                }
            }
        }

        PullDownMenu {
//            MenuItem{
//                text:qsTr("Help")
//                onClicked: pageStack.push(Qt.resolvedUrl("Help.qml"))
//            }

            MenuItem{
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
        }
    }
}
