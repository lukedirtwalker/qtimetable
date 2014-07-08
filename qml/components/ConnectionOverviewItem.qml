import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: connOverviewItem

    width: parent.width
    height: Theme.itemSizeSmall

    Row {
        id: labelRow
        anchors.left: parent.left
        anchors.leftMargin: Theme.paddingLarge
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        spacing: Theme.paddingMedium


        Label{
            id: depTimeLabel
            width: parent.width * 0.18
            text: Qt.formatTime(dep,"hh:mm") // TODO change depending on locale
            color: connOverviewItem.highlighted ?
                       Theme.highlightColor : Theme.primaryColor
        }

        Label{
            id: arrTimeLabel
            width: parent.width * 0.18
            text: Qt.formatTime(arr,"hh:mm"); // TODO change depending on locale
            color: connOverviewItem.highlighted ?
                       Theme.highlightColor : Theme.primaryColor
        }
        Label{
            id: durTimeLabel
            width: parent.width * 0.18
            text: dur
            color: connOverviewItem.highlighted ?
                       Theme.highlightColor : Theme.primaryColor
        }
        Label{
            id: chgLabel
            width: parent.width * 0.18
            text: chg
            color: connOverviewItem.highlighted ?
                       Theme.highlightColor : Theme.primaryColor
        }

        Label{
            id: platTimeLabel
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
    }
}
