import QtQuick 2.0
import QtQuick.Controls 2.2
import "../tableViews"
import "../components"

Popup {
    id: popupRestults
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

    contentItem: TableViewBest {
        id: disp
    }

    BackButton {
        anchors.top: popupRestults.Top
        anchors.left: popupRestults.Left
        onClicked: popupRestults.close()
    }
}
