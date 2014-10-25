import QtQuick 2.0
import Sailfish.Silica 1.0

Page{
    id: aboutPage
    SilicaFlickable {
        anchors.fill: parent


        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: aboutPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("About")
            }

            Label {
                width: parent.width
                text: qsTr("Version: %1".arg(APP_VERSION))
            }

            TextArea{
                id:info1
                width: parent.width
                readOnly: true
                text: qsTr("THIS APPLICATION IS A TEST VERSION. PLEASE DO NOT REDISTRIBUTE. THANKS FOR REPORTING BUGS ETC.")
            }
            TextArea{
                id: infoLabel
                width: parent.width
                readOnly: true
                text: qsTr("This is an unofficial timetable client application which uses the information provided by SBB. \nFor bug reports and other questions / issues send an email to qtimetable@gmail.com or preferably use the link below")
            }
            TextArea{
                id: issueField
                width: parent.width
                readOnly: true
                // TODO: Fix link
                text: qsTr("Report issues here : <a href=\"https://bitbucket.org/qtimetable/qtimetablen9/issues?status=new&status=open\"> issue tracker </a>")
                // XXX: Workaround to have Links
//                Component.onCompleted: {
//                    issueField.textFormat = TextFormat.RichText
//                }
            }
        }
    }
}
