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

Dialog {
    id: searchDialog

    property string searchText
    property int type
    property string typeString
    property alias model: searchSuggestionList.model

    property int selectIndex : 0;

    Component.onDestruction: {
        searchDialog.model.clear()
    }

    onOpened: {
        stationSearch.forceActiveFocus()
    }

    onAccepted: {
        timeTableHandler.setStation(selectIndex, type)
    }

    DialogHeader {
        id: header
        acceptText: typeString
    }

    SearchField { // should be outside such that we keep focus
        id: stationSearch
        width: parent.width
        anchors.top: header.bottom
        text: searchText
        placeholderText: qsTr("Enter %1 station".arg(typeString.toLowerCase()))
        onTextChanged: {
            timeTableHandler.startQuery(text, type)
        }
    }

    SilicaListView {
        id: searchSuggestionList
        width: parent.width
        anchors.top: stationSearch.bottom
        anchors.bottom: parent.bottom
        clip: true
        pressDelay: 0

        VerticalScrollDecorator {}

        delegate: SearchListItem {
            text: stationSearch.text.length > 0 ? Theme.highlightText(model.stationName, stationSearch.text, Theme.highlightColor) : model.stationName
            onClicked: {
                selectIndex = index;
                pageStack.navigateForward()
            }
        }
    }
}
