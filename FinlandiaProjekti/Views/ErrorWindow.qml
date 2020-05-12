import QtQuick 2.0
import QtQuick.Controls 2.2
import "./components"


Popup {
    id: errorPopup
    x: 0
    y: 0
    width: parent.parent.parent.width - 4
    height: parent.parent.parent.height - 64
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    background: Rectangle {
        implicitWidth: 500
        implicitHeight: 200
        color: "mediumorchid"
        radius: 3
        border.color: "#444"
    }

    BackButton {
        id: backButton
        anchors.top: errorPopup.Top
        anchors.left: errorPopup.Left
        onClicked: errorPopup.close()
    }

    Text {
        anchors.left: backButton.right
        anchors.top: backButton.bottom
        id: errorMessage
        text: "Virhe!" + "\n" + clickHandler.errorMessage
        font.pixelSize: parent.width / 20
        color: "white"
    }
}
