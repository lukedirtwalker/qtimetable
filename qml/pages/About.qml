import QtQuick 2.0
import Sailfish.Silica 1.0

Page{
    id: aboutPage
    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            anchors {
                left: parent.left
                right: parent.right
                margins: Theme.paddingLarge
            }

            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("About")
            }

            Label {
                id: versionInfo
                width: parent.width
                // TODO: version number
                text: qsTr("CURRENT VERSION: NYI")
                wrapMode: Text.WordWrap
            }

            Label {
                id: testInfo
                width: parent.width
                text: qsTr("THIS APPLICATION IS A TEST VERSION. THANKS FOR REPORTING BUGS ETC.")
                wrapMode: Text.WordWrap
            }

            Label {
                id: infoLabel
                width: parent.width
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
                    Qt.openUrlExternally("mailto:qtimetable@gmail.com?subject=QtimeTable")
                }
            }
        }
    }
}
