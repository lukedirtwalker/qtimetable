import QtQuick 2.1
import Sailfish.Silica 1.0

Row {
    id: depArrSwitch

    width: parent.width

    property bool arrival: false;

    TextSwitch {
        id: dep
        width: parent.width / 2
        text: qsTr("Departure")
        checked: !arrival
        automaticCheck: false
        onClicked: {
            if(!checked) {
                depArrSwitch.arrival = false;
            }
        }
    }

    TextSwitch {
        id: arr
        width: parent.width / 2
        text: qsTr("Arrival")

        checked: arrival
        automaticCheck: false
        onClicked: {
            if(!checked) {
                depArrSwitch.arrival = true;
            }
        }
    }
}
