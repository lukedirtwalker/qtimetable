import QtQuick 2.0
import Sailfish.Silica 1.0

Item{
    property alias fromStationText: fromStation.text
    property alias date: dateValue.text
    property alias toStationText: toStation.text
    property alias time: timeValue.text

    property bool hasArrival: true
    property bool hasDep: true

    anchors.left: parent.left
    anchors.right: parent.right
    height: fromDate.height + toTime.height + Theme.paddingMedium

    Item {
        id: fromDate
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: Theme.itemSizeSmall
        anchors.margins: Theme.paddingMedium
        Label{
            id:fromLabel
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("From")
            font.pixelSize: Theme.fontSizeSmall
            visible: hasDep
        }

        Label{
            id:fromStation
            anchors.left: parent.left
            anchors.top: fromLabel.bottom
            font.pixelSize: Theme.fontSizeLarge
            width: 100 // TODO
            elide: Text.ElideRight
        }

        Label{
            id:dateLabel
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("Date")
            font.pixelSize: Theme.fontSizeSmall
        }

        Label{
            id:dateValue
            anchors.right: parent.right
            anchors.top: dateLabel.bottom
            font.pixelSize: Theme.fontSizeLarge
        }
    }

    Item{
        id:toTime
        anchors.top: fromDate.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: Theme.itemSizeSmall
        anchors.rightMargin: Theme.paddingMedium
        anchors.leftMargin: Theme.paddingMedium
        Label{
            id:toLabel
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("To")
            font.pixelSize: Theme.fontSizeSmall
            visible: hasArrival
        }

        Label{
            id:toStation
            anchors.left: parent.left
            anchors.top: toLabel.bottom
            font.pixelSize: Theme.fontSizeLarge
            width: 100 // TODO
            elide: Text.ElideRight
        }

        Label{
            id:timeLabel
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("Time")
            font.pixelSize: Theme.fontSizeSmall
        }

        Label{
            id:timeValue
            anchors.right: parent.right
            anchors.top: timeLabel.bottom
            font.pixelSize: Theme.fontSizeLarge
        }
    }
}

