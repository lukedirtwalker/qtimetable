/******************************************************************************
*Copyright (c) 2013-2015, Lukas Vogel, Stefan Willi
*All rights reserved.
*
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*    * Neither the name of the <organization> nor the
*      names of its contributors may be used to endorse or promote products
*      derived from this software without specific prior written permission.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
*DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
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
        anchors.margins: Theme.paddingLarge
        Label{
            id:fromLabel
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("From")
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.highlightColor
            visible: hasDep
        }

        Label{
            id:fromStation
            anchors.left: parent.left
            anchors.top: fromLabel.bottom
            width: parent.width * 0.75
            elide: Text.ElideRight
        }

        Label{
            id:dateLabel
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("Date")
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.highlightColor
        }

        Label{
            id:dateValue
            anchors.right: parent.right
            anchors.top: dateLabel.bottom
        }
    }

    Item{
        id:toTime
        anchors.top: fromDate.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: Theme.itemSizeSmall
        anchors.rightMargin: Theme.paddingLarge
        anchors.leftMargin: Theme.paddingLarge
        Label{
            id:toLabel
            anchors.left: parent.left
            anchors.top: parent.top
            text: qsTr("To")
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.highlightColor
            visible: hasArrival
        }

        Label{
            id:toStation
            anchors.left: parent.left
            anchors.top: toLabel.bottom
            width: parent.width * 0.75
            elide: Text.ElideRight
        }

        Label{
            id:timeLabel
            anchors.right: parent.right
            anchors.top: parent.top
            text: qsTr("Time")
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.highlightColor
        }

        Label{
            id:timeValue
            anchors.right: parent.right
            anchors.top: timeLabel.bottom
        }
    }
}
