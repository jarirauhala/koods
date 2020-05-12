import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

import "../components"

Popup {

    // if controller validates input and model populates table succesfully, ResultWindow is opened.
    // Otherwise ErrorWindow is opened and error message displayed
    function viewClickHandler() {
        var year1 = yearSlider.first.value;
        var year2 = yearSlider.second.value;

        if(clickHandler.jakaumaMaittainClicked(year1, year2)) {
            var popupComponent = Qt.createComponent("qrc:/jakaumaMaittain/ResultWindow.qml")
            var popupWindow = popupComponent.createObject(parent);
            popupWindow.open()
        }
        else {
            // open error errorWindow
            var popupComponentErr = Qt.createComponent("qrc:/ErrorWindow.qml");
            var errWindow = popupComponentErr.createObject(parent);
            errWindow.open()
        }
    }

    id: questionwindow1
    x: 1
    y: 1
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
        anchors.top: parent.top
        anchors.left: parent.left
        onClicked: questionwindow1.close()
    }

    ColumnLayout {
        anchors.top: backButton.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10

        RangeSlider {
            Layout.alignment: Qt.AlignHCenter
            implicitWidth: 450
            height: 100
            id: yearSlider
            from: 1975
            to: 2022
            first.value: 1995
            second.value: 2002
            stepSize: 1
            snapMode: "SnapAlways"
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 55
            Text {
                id: sliderDisplay1
                text: "Vuodesta\n" + yearSlider.first.value
                font.pixelSize: 20
            }

            Text {
                id: sliderDisplay2
                text: "Vuoteen\n" + yearSlider.second.value
                font.pixelSize: 20
            }
        }

        SearchButton {
            Layout.alignment: Qt.AlignHCenter
            id: searchButton
            onClicked: viewClickHandler()
        }
    }
}
