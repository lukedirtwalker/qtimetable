import QtQuick 2.1
import Sailfish.Silica 1.0

Row {
    width: parent.width

    // TODO replace with backend state
    property bool depart: true;

    TextSwitch {
        id: dep
        width: parent.width / 2
        text: qsTr("Departure")
        checked: true
        automaticCheck: false
        onClicked: {
            if(!checked) {
                arr.checked = false;
                arr.highlighted = false;
                highlighted = true;
                // TODO backend
                checked = true;
            }
        }
    }

    TextSwitch {
        id: arr
        width: parent.width / 2
        text: qsTr("Arrival")

        checked: false
        automaticCheck: false
        onClicked: {
            if(!checked) {
                dep.checked = false;
                dep.highlighted = false;
                highlighted = true;
                // TODO backend
                checked = true;
            }
        }
    }
}
