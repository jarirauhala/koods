import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

import "../components"


Popup {

    // if controller validates input and model populates table succesfully, ResultWindow is opened.
    // Otherwise ErrorWindow is opened and error message displayed
    function viewClickHandler() {
        var year = yearInput.text;

        if(clickHandler.vuosittaisetTilastotClicked(year)) {
            var popupComponent = Qt.createComponent("qrc:/vuosittaisetTilastot/ResultWindow.qml")
            var popupWindow = popupComponent.createObject(parent);
            popupWindow.open()
        }
        else {
            // open errorWindow
            var popupComponentErr = Qt.createComponent("qrc:/ErrorWindow.qml");
            var errWindow = popupComponentErr.createObject(parent);
            errWindow.open()
        }
    }

    id: questionwindow1
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
        color: "mediumturquoise"
        radius: 3
        border.color: "#444"
    }

    BackButton {
        id: backButton
        anchors.top: questionwindow1.top
        anchors.left: questionwindow1.left
        onClicked: questionwindow1.close()
    }

    ColumnLayout {
        anchors.top: backButton.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        TextField {
            id: yearInput
            placeholderText: "Vuosi"
            Layout.alignment: Qt.AlignHCenter
        }

        SearchButton {
            id: searchButton
            Layout.alignment: Qt.AlignHCenter
            onClicked: viewClickHandler()
        }
    }
}
