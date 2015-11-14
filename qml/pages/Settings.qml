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

Page{
    id: settingsPage
    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: settingsPage.width
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("QTimeTable %1").arg(APP_VERSION)
            }

            TextSwitch {
                checked: timeHandler.showWalkInDepTime
                text: qsTr("Account for walk times")
                description: qsTr("For some connections the first step is to walk to a station. If this setting is on the departure time in the connection page accounts for this walking time. If it is off it shows the departure time of the train.")
                onClicked: {
                    timeTableHandler.showWalkInDepTime = checked
                }
            }

            TextSwitch {
                checked: timeTableHandler.saveStations
                text: "Save stations on Exit"
                onClicked: {
                    timeTableHandler.saveStations = checked
                }
            }

            PageHeader {
                title: qsTr("About")
            }

            Label {
                id: infoLabel
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingLarge
                    right: parent.right
                    rightMargin: Theme.paddingLarge
                }

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
                    Qt.openUrlExternally("mailto:lukedirtwalkerdev@gmail.com?subject=[QTimeTable]")
                }
            }

            Button {
                id: donateButton
                width: parent.width * 0.5
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Donate")
                onClicked: {
                    Qt.openUrlExternally("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=DA4FXEE3WXVWW")
                }
            }
        }

        VerticalScrollDecorator { }
    }
}
