import QtQuick 2.0
import QtQuick.Controls 2.2
import "../tableViews"
import "../components"



Popup {
    id: popup2
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
        color: "#26e6e3"
        radius: 3
        border.color: "#444"
    }

    BackButton {
        id: backButton
        anchors.top: popup2.Top
        anchors.left: popup2.Left
        onClicked: popup2.close()
    }

    TableViewSplit {
        anchors.top: backButton.bottom
        anchors.topMargin: 10
        width: parent.width-20
        id: disp
    }
}
