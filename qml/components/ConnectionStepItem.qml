import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: connStepItem

    width: parent.width
    height: Theme.itemSizeLarge


    Row {
            id: depItem
            height: Theme.itemSizeSmall

            anchors {
                left:  parent.left
                leftMargin: Theme.paddingLarge
                right:  parent.right
                top: parent.top
            }

            spacing: Theme.paddingMedium

            Label{
                id:depTimeLabel
                width: parent.width / 4
                text: HasDepDelay ? Qt.formatTime(DepTime,"hh:mm") + "+" + DepDelay : Qt.formatTime(DepTime,"hh:mm")
//                color: theme.inverted ? (HasDepDelay ? "red" : "white") : (HasDepDelay ? "red" : "black")
            }

            Label{
                id: depPlatformLabel
                width: parent.width / 4
                text: DepPlatform
//                color: theme.inverted ? (HasChangedDepPlatform ? "red" : "white") : (HasChangedDepPlatform ? "red" : "black")
            }

            Label{
                id: depStopLabel
                width: parent.width / 2
                text: DepStation
                elide: Text.ElideRight
                maximumLineCount: 2
            }
        }

//        Item{
//            id: infoItem
//            anchors.left: parent.left
//            anchors.leftMargin: Theme.paddingLarge
//            anchors.top: depItem.bottom
//            anchors.topMargin: Theme.paddingLarge
//            height: Theme.itemSizeSmall / 2
//            width: Ui.INFO_MOT_OCCUP_WIDTH
//            Label{
//                id: meansOfTransportLabel
//                anchors.left: parent.left
//                anchors.verticalCenter: parent.verticalCenter
//                text: MeansOfTransport
//            }


//            Item{
//                id: infoTimeLabel1
//                anchors.left: infoItem.right
//                anchors.rightMargin: 14
//                anchors.verticalCenter: parent.verticalCenter
//                width: Ui.UT_IMAGE_WIDTH
//                Loader{
//                    anchors.fill: parent
//                    sourceComponent: loadLabelFirst(UtilisationFirst)
//                }
//            }

//            Item{
//                id: loaderWrap
//                anchors.left: infoTimeLabel1.right
//                anchors.leftMargin: 14
//                width: Ui.UT_IMAGE_WIDTH
//                anchors.verticalCenter: parent.verticalCenter
//                Loader{
//                    id:firstLoader
//                    anchors.fill: parent
//                    sourceComponent: loadComp(UtilisationFirst)
//                }
//            }

//            Item{
//                id:infoTimeLabel2
//                anchors.left: loaderWrap.right
//                anchors.rightMargin: 14
//                anchors.verticalCenter: parent.verticalCenter
//                width: Ui.UT_IMAGE_WIDTH
//                Loader{
//                    anchors.fill: parent
//                    sourceComponent: loadLabelSecond(UtilisationSecond)
//                }
//            }

//            Item{
//                id: loaderWrap2
//                anchors.left: infoTimeLabel2.right
//                anchors.leftMargin: 14
//                width: Ui.UT_IMAGE_WIDTH
//                anchors.verticalCenter: parent.verticalCenter
//                Loader{
//                    id:secondLoader
//                    anchors.fill: parent
//                    sourceComponent: loadComp(UtilisationSecond)
//                }
//            }

//        }

        Row {
            id: arrItem
            height: Theme.itemSizeSmall

            anchors {
                left:  parent.left
                leftMargin: Theme.paddingLarge
                right:  parent.right
                top: depItem.bottom
            }

            spacing: Theme.paddingMedium

            Label{
                id: arrTimeLabel
                width: parent.width / 4
                text: HasArrDelay ? Qt.formatTime(ArrTime,"hh:mm") + "+" + ArrDelay : Qt.formatTime(ArrTime,"hh:mm")
//                color: theme.inverted ? (HasArrDelay ? "red" : "white") : (HasArrDelay ? "red" : "black")
            }

            Label{
                id: arrPlatformLabel
                width: parent.width / 4
                text: ArrPlatform
//                color: theme.inverted ? (HasChangedArrPlatform ? "red" : "white") : (HasChangedArrPlatform ? "red" : "black")
            }
            Label{
                id: arrStopLabel
                width: parent.width / 2
                text: ArrStation
                elide: Text.ElideRight
                maximumLineCount: 2
            }
        }


}
