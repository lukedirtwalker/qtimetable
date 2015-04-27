import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: connStepItem

    width: parent.width
    height: content.height

    Column {
        id: content
        width: parent.width

        Row {
            id: depItem
            height: Theme.itemSizeExtraSmall
            anchors {
                left:  parent.left
                leftMargin: Theme.paddingLarge
                right: parent.right
            }

            property color labelColor: Theme.highlightColor
            spacing: Theme.paddingMedium

            Label{
                id:depTimeLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: HasDepDelay ? Qt.formatTime(DepTime,"hh:mm") + "+" + DepDelay : Qt.formatTime(DepTime,"hh:mm")
                //                color: theme.inverted ? (HasDepDelay ? "red" : "white") : (HasDepDelay ? "red" : "black")
                color: depItem.labelColor
            }

            Label{
                id: depPlatformLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: DepPlatform
                //                color: theme.inverted ? (HasChangedDepPlatform ? "red" : "white") : (HasChangedDepPlatform ? "red" : "black")
                color: depItem.labelColor
            }

            Label{
                id: depStopLabel
                width: parent.width * 0.55
                anchors.verticalCenter: parent.verticalCenter
                text: DepStation
                elide: Text.ElideRight
                maximumLineCount: 2
                color: depItem.labelColor
            }
        }

        Row {
            id: infoItem
            height: Theme.itemSizeSmall
            anchors {
                left:  parent.left
                leftMargin: Theme.paddingLarge
                right: parent.right
            }

            property color labelColor: highlighted ? Theme.highlightColor : Theme.primaryColor

            spacing: Theme.paddingMedium

            Label{
                id: meansOfTransportLabel
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width * 0.36 + Theme.paddingMedium
                text: MeansOfTransport
                color: infoItem.labelColor
            }

            Column {
                width: parent.width * 0.55

                anchors.verticalCenter: parent.verticalCenter

                Label {
                    width: parent.width
                    text: MOTDetail
                    elide: Text.ElideRight
                    color: infoItem.labelColor
                }

                Label {
                    width: parent.width
                    text: Direction.length > 0 ? qsTr("Dir. ") + Direction : ""
                    elide: Text.ElideRight
                    color: infoItem.labelColor
                }
            }


            //        Item{
            //            id: infoTimeLabel1
            //            anchors.left: infoItem.right
            //            anchors.rightMargin: 14
            //            anchors.verticalCenter: parent.verticalCenter
            //            width: Ui.UT_IMAGE_WIDTH
            //            Loader{
            //                anchors.fill: parent
            //                sourceComponent: loadLabelFirst(UtilisationFirst)
            //            }
            //        }

            //        Item{
            //            id: loaderWrap
            //            anchors.left: infoTimeLabel1.right
            //            anchors.leftMargin: 14
            //            width: Ui.UT_IMAGE_WIDTH
            //            anchors.verticalCenter: parent.verticalCenter
            //            Loader{
            //                id:firstLoader
            //                anchors.fill: parent
            //                sourceComponent: loadComp(UtilisationFirst)
            //            }
            //        }

            //        Item{
            //            id:infoTimeLabel2
            //            anchors.left: loaderWrap.right
            //            anchors.rightMargin: 14
            //            anchors.verticalCenter: parent.verticalCenter
            //            width: Ui.UT_IMAGE_WIDTH
            //            Loader{
            //                anchors.fill: parent
            //                sourceComponent: loadLabelSecond(UtilisationSecond)
            //            }
            //        }

            //        Item{
            //            id: loaderWrap2
            //            anchors.left: infoTimeLabel2.right
            //            anchors.leftMargin: 14
            //            width: Ui.UT_IMAGE_WIDTH
            //            anchors.verticalCenter: parent.verticalCenter
            //            Loader{
            //                id:secondLoader
            //                anchors.fill: parent
            //                sourceComponent: loadComp(UtilisationSecond)
            //            }
            //        }
        }

        Row {
            id: arrItem
            height: Theme.itemSizeExtraSmall
            anchors {
                left:  parent.left
                leftMargin: Theme.paddingLarge
                right: parent.right
            }

            property color labelColor: Theme.highlightColor

            spacing: Theme.paddingMedium

            Label{
                id: arrTimeLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: HasArrDelay ? Qt.formatTime(ArrTime,"hh:mm") + "+" + ArrDelay : Qt.formatTime(ArrTime,"hh:mm")
                //                color: theme.inverted ? (HasArrDelay ? "red" : "white") : (HasArrDelay ? "red" : "black")
                color: arrItem.labelColor
            }

            Label{
                id: arrPlatformLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: ArrPlatform
                //                color: theme.inverted ? (HasChangedArrPlatform ? "red" : "white") : (HasChangedArrPlatform ? "red" : "black")
                color: arrItem.labelColor
            }
            Label{
                id: arrStopLabel
                width: parent.width * 0.55
                anchors.verticalCenter: parent.verticalCenter
                text: ArrStation
                elide: Text.ElideRight
                maximumLineCount: 2
                color: arrItem.labelColor
            }
        }
    }
}
