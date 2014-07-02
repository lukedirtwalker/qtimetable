import QtQuick 2.0
import Sailfish.Silica 1.0

Page{
    id: helpPage
    SilicaFlickable {
        anchors.fill: parent


        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: helpPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("Help")
            }
            TextArea{
                id:help
                width: parent.width
                readOnly: true
                // TODO: Add help ;)
                text: qsTr("Help --- comming soon ;)")
            }
        }
    }
}
