import QtQuick 2.0
import Sailfish.Silica 1.0


Item {
    id: deletableTextField

    property alias text: textField.text
    property alias placeholderText: textField.placeholderText
    property alias font: textField.font

    signal clicked
    signal deleted

    width: parent.width
    height: Math.max(Theme.itemSizeMedium, textField._editor.height +
                     Theme.paddingMedium + Theme.paddingSmall)


    TextField {
        id: textField
        anchors.left: parent.left
        width: parent.width - (Theme.itemSizeSmall + Theme.paddingLarge) // icon
        // We never want focus
        focus: false
        focusOnClick: false

        onClicked: {
            deletableTextField.clicked()
        }
    }

    IconButton {
        id: clearButton
        anchors {
            right: parent.right
            rightMargin: Theme.paddingLarge
        }
        width: icon.width
        height: parent.height - (Theme.paddingLarge + Theme.paddingMedium)

        icon.source: "image://theme/icon-m-clear"

        enabled: textField.enabled

        opacity: textField.text.length > 0 ? 1 : 0

        onClicked: {
            deletableTextField.deleted()
        }
    }
}
