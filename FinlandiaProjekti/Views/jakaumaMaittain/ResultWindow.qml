import QtQuick 2.0
import QtQuick.Controls 2.2
import "../graphViews"
import "../components"

Popup {
    id: popupResults
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

    contentItem: GraphViewDistribution {
        id: disp
    }

    BackButton {
        anchors.top: popupResults.Top
        anchors.left: popupResults.Left
        onClicked: popupResults.close()
    }
}
