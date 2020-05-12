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
        color: "#26e6e3"
        radius: 3
        border.color: "#444"
    }

    BackButton {
        anchors.top: popup2.Top
        anchors.left: popup2.Left
        onClicked: popup2.close()
    }

    contentItem: TableViewAll {
        id: disp
    }
}
