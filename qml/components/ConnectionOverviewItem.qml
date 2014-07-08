import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: connOverviewItem

    width: parent.width
    height: Theme.itemSizeSmall

    Label{
        id: depTimeLabel
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.18
        text: Qt.formatTime(dep,"hh:mm") // TODO change depending on locale
        color: connOverviewItem.highlighted ?
                   Theme.highlightColor : Theme.primaryColor
    }

    Label{
        id: arrTimeLabel
        anchors.left: depTimeLabel.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.18
        text: Qt.formatTime(arr,"hh:mm"); // TODO change depending on locale
        color: connOverviewItem.highlighted ?
                   Theme.highlightColor : Theme.primaryColor
    }
    Label{
        id: durTimeLabel
        anchors.left: arrTimeLabel.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.18
        text: dur
        color: connOverviewItem.highlighted ?
                   Theme.highlightColor : Theme.primaryColor
    }
    Label{
        id: chgLabel
        anchors.left: durTimeLabel.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.18
        text: chg
        color: connOverviewItem.highlighted ?
                   Theme.highlightColor : Theme.primaryColor
    }

    Label{
        id: platTimeLabel
        anchors.left: chgLabel.right
        anchors.leftMargin: Theme.paddingMedium
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.18
        text: plat
//        color: theme.inverted ? (HasChangedDepPlatform ? "red" : "white") : (HasChangedDepPlatform ? "red" : "black")
        color: connOverviewItem.highlighted ?
                   Theme.highlightColor : Theme.primaryColor
    }

    //        Item{
    //            id:delayWarningWrap
    //            anchors.left: chgLabel.right
    //            anchors.verticalCenter: parent.verticalCenter
    //            width: 32
    //            Loader{
    //                anchors.fill: parent
    //                sourceComponent: loadDelayWarner(getConnectionStateInfo);
    //            }
    //        }

    //        Label{
    //            id: platTimeLabel
    //            anchors.left: delayWarningWrap.right
    //            anchors.leftMargin: UiConstants.DefaultMargin
    //            anchors.verticalCenter: parent.verticalCenter
    //            width: Ui.PLATFORM_LABEL_WIDTH_RESULT
    //            text: plat
    //            color: theme.inverted ? (HasChangedDepPlatform ? "red" : "white") : (HasChangedDepPlatform ? "red" : "black")
    //        }
}
