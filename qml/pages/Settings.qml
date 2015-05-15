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
                title: qsTr("QTimeTable %1").arg(APP_VERSION)
            }

            TextSwitch {
                checked: timeTableHandler.saveStations
                text: "Save stations on Exit"
                onClicked: {
                    timeTableHandler.saveStations = checked
                }
            }

            PageHeader {
                title: qsTr("About")
            }

            Label {
                id: infoLabel
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }

                text: qsTr("This is an unofficial timetable client application which uses the information provided by SBB. \nFor bug reports and other questions / issues use the issue tracker:")
                wrapMode: Text.WordWrap
            }

            Button {
                id: issueButton
                width: parent.width * 0.5
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Issue tracker")
                onClicked: {
                    Qt.openUrlExternally("https://bitbucket.org/qtimetable/qtimetable2/issues?status=open")
                }
            }

            Button {
                id: mailButton
                width: parent.width * 0.5
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("e-Mail developer")
                onClicked: {
                    Qt.openUrlExternally("mailto:lukedirtwalkerdev@gmail.com?subject=[QTimeTable]")
                }
            }

            Button {
                id: donateButton
                width: parent.width * 0.5
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Donate")
                onClicked: {
                    Qt.openUrlExternally("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=DA4FXEE3WXVWW")
                }
            }
        }

        VerticalScrollDecorator { }
    }
}
