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
import "../components"

Page {
    id: connectionStepPage

    property alias model: connectionSteps.model
    property string from: ""
    property string to: ""
    property string date: ""
    property string time: ""

    SilicaListView {
        id: connectionSteps
        anchors.fill: parent

        header: Column {
            id: column
            width: connectionStepPage.width
            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("Detail")
            }

            ConnectionOverviewHeader {
                id: overviewHeader
                fromStationText: connectionStepPage.from
                toStationText: connectionStepPage.to
                date: connectionStepPage.date
                time: connectionStepPage.time
            }

            Item {
                id: tableHeader

                width: parent.width
                height: Theme.itemSizeSmall

                Row {
                    id: headerRow
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    spacing: Theme.paddingMedium
                    Label{
                        id: depTimeLabel
                        width: parent.width * 0.18
                        text: qsTr("Time")
                        color: Theme.highlightColor
                    }

                    Label{
                        id: arrTimeLabel
                        width: parent.width * 0.18
                        text: qsTr("Pl.")
                        color: Theme.highlightColor
                    }
                    Label{
                        id: durTimeLabel
                        //                    width: parent.width * 0.5
                        text: qsTr("Stop / Remark")
                        color: Theme.highlightColor
                    }
                }
            }
        }

        VerticalScrollDecorator {}

        clip: true
        pressDelay: 0

        delegate: ConnectionStepItem {}
    }
}
