import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11


import "../components"

Popup {

    // if controller validates input and model populates table succesfully, ResultWindow is opened.
    // Otherwise ErrorWindow is opened and error message displayed
    function viewClickHandler() {
        var year = yearInput.text;
        var travel = travelInqs.travelParser()
        //var travel = travelParser();

        if(clickHandler.parhaatJoukkueetClicked(year, travel)) {
            var popupComponent = Qt.createComponent("qrc:/parhaatJoukkueet/ResultWindow.qml")
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

    id: questionwindowPJ
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
        anchors.top: questionwindowPJ.top
        anchors.left: questionwindowPJ.left
        onClicked: questionwindowPJ.close()
    }

    ColumnLayout {
        anchors.top: backButton.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 10


        TextField {
            id: yearInput
            placeholderText: "vuosi"
            Layout.alignment: Qt.AlignHCenter
        }

        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            color: "mediumturquoise"
            radius: 5
            border.color: "white"
            width: 200
            height: 200

            ColumnLayout {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                spacing: 30

                Text {
                    Text {
                        id: travelTitle1
                        text: qsTr("Matka")
                        font.pixelSize: 20
                    }
                }

                TravelInquiries {
                    id: travelInqs
                }
            }
        }

        SearchButton {
            id: searchButton
            Layout.alignment: Qt.AlignHCenter
            onClicked: viewClickHandler()
        }
    }
}
