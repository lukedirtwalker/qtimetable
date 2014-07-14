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

            spacing: Theme.paddingMedium

            Label{
                id:depTimeLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: HasDepDelay ? Qt.formatTime(DepTime,"hh:mm") + "+" + DepDelay : Qt.formatTime(DepTime,"hh:mm")
                //                color: theme.inverted ? (HasDepDelay ? "red" : "white") : (HasDepDelay ? "red" : "black")
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
            }

            Label{
                id: depPlatformLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: DepPlatform
                //                color: theme.inverted ? (HasChangedDepPlatform ? "red" : "white") : (HasChangedDepPlatform ? "red" : "black")
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
            }

            Label{
                id: depStopLabel
                width: parent.width * 0.55
                anchors.verticalCenter: parent.verticalCenter
                text: DepStation
                elide: Text.ElideRight
                maximumLineCount: 2
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
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

            Label{
                id: meansOfTransportLabel
                anchors.verticalCenter: parent.verticalCenter
                text: MeansOfTransport
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
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

            spacing: Theme.paddingMedium

            Label{
                id: arrTimeLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: HasArrDelay ? Qt.formatTime(ArrTime,"hh:mm") + "+" + ArrDelay : Qt.formatTime(ArrTime,"hh:mm")
                //                color: theme.inverted ? (HasArrDelay ? "red" : "white") : (HasArrDelay ? "red" : "black")
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
            }

            Label{
                id: arrPlatformLabel
                width: parent.width * 0.18
                anchors.verticalCenter: parent.verticalCenter
                text: ArrPlatform
                //                color: theme.inverted ? (HasChangedArrPlatform ? "red" : "white") : (HasChangedArrPlatform ? "red" : "black")
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
            }
            Label{
                id: arrStopLabel
                width: parent.width * 0.55
                anchors.verticalCenter: parent.verticalCenter
                text: ArrStation
                elide: Text.ElideRight
                maximumLineCount: 2
                color: connStepItem.highlighted ?
                           Theme.highlightColor : Theme.primaryColor
            }
        }
    }
}
