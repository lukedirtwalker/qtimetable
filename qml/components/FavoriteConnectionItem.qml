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

ListItem {
    id: favConnectionItem
    property bool hasVia: false
    property alias depStation: depStation.text
    property alias arrStation: arrStation.text
    property string viaStation: ""

    width: parent.width / 2
    contentHeight: content.height

    menu: ContextMenu {
        MenuItem {
            text: qsTr("Remove from favorites")
            onClicked: {
                remorseAction("Remove from favorites", function() {timeTableHandler.removeFavoriteConnection(DbId);})
            }
        }
    }

    Column {
        id: content
        spacing: Theme.paddingSmall
        anchors {
            left: parent.left
            leftMargin: Theme.paddingLarge
            right: parent.right
            rightMargin: Theme.paddingLarge
        }

        Item {
            id: spacerTop
            width: parent.width
            height: Theme.paddingSmall
        }

        Label {
            id: depStation
            width: parent.width
            truncationMode: TruncationMode.Fade
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
        }

        Label {
            id: viaStation
            width: parent.width
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
            text: favConnectionItem.hasVia ? favConnectionItem.viaStation : qsTr("To")
            color: Theme.secondaryHighlightColor
        }

        Label {
            id: arrStation
            width: parent.width
            truncationMode: TruncationMode.Fade
            color: highlighted ? Theme.highlightColor : Theme.primaryColor
        }

        Item {
            id: spacerBottom
            width: parent.width
            height: Theme.paddingSmall
        }
    }

    Image {
        id: gradientImage

        anchors {
            bottom: parent.bottom
            right: parent.right
        }

        width: Math.min(parent.width, sourceSize.width)
        height: Math.min(parent.height, sourceSize.height)

        opacity: 0.15
        source: "image://theme/graphic-gradient-corner?" + Theme.highlightBackgroundColor
    }
}
