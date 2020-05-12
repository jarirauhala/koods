import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11


import "../components"

Popup {

    // if controller validates input and model populates table succesfully, ResultWindow is opened.
    // Otherwise ErrorWindow is opened and error message displayed
    function viewClickHandler() {
        var year = yearInput.text;
        var travel1 = travelInqs1.travelParser()
        var travel2 = travelInqs2.travelParser()
        var names = namesInput.text

        if(clickHandler.eriMatkojenVertailuClicked(year, travel1, travel2, names)) {
            var popupComponent = Qt.createComponent("qrc:/eriMatkojenVertailu/ResultWindow.qml")
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

        TextField {
            id: yearInput
            placeholderText: "Vuosi"
            Layout.alignment: Qt.AlignHCenter
            width: 150
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Rectangle {
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
                            text: qsTr("Matka 1:")
                            font.pixelSize: 20
                        }
                    }

                    TravelInquiries {
                        id: travelInqs1
                    }
                }
            }

            Rectangle {
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
                            id: travelTitle2
                            text: qsTr("Matka 2:")
                            font.pixelSize: 20
                        }
                    }

                    TravelInquiries {
                        id: travelInqs2
                    }
                }
            }
        }

        TextField {
            id: namesInput
            placeholderText: "Hiihtäjän nimi, esim. Hillevi Hiihtäjä, Timo Tamppaaja"
            Layout.alignment: Qt.AlignHCenter
            implicitWidth: 450
        }

        SearchButton {
            id: searchButton
            Layout.alignment: Qt.AlignHCenter
            onClicked: viewClickHandler()
        }
    }
}
