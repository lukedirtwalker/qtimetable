import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    SilicaListView {
        property alias searchField: search

        anchors.fill: parent

        header: SearchField {
            id: search
            width: parent.width
            placeholderText: "Search"

            onTextChanged: {
                listModel.update()
            }
        }

        // prevent newly added list delegates from stealing focus away from the search field
        currentIndex: -1

        model: ListModel {
            id: listModel
            property var continents: ["Africa", "Antarctica", "Asia", "Europe", "North America", "Oceania", "South America"]

            function update() {
                clear()
                for (var i=0; i<continents.length; i++) {
                    if (searchField.text == "" || continents[i].indexOf(searchField.text) >= 0) {
                        append({"name": continents[i]})
                    }
                }
            }

            Component.onCompleted: update()
        }

        delegate: ListItem {
            Label {
                anchors {
                    left: parent.left
                    leftMargin: searchField.textLeftMargin
                    verticalCenter: parent.verticalCenter
                }
                text: name
            }
        }
    }
}
