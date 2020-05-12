import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import "../components"

Popup {

    // if controller validates input and model populates table succesfully, ResultWindow is opened.
    // Otherwise ErrorWindow is opened and error message displayed

    function viewClickHandler() {
        let year1 = yearSlider.first.value;
        let year2 = yearSlider.second.value;
        let travel = travelInqs.travelParser();
        let rankMax = rankSpinBox.value;

        if(clickHandler.keskinopeusSijoituksenMukaanClicked(year1, year2, travel, rankMax)) {
            var popupComponent = Qt.createComponent("qrc:/keskinopeusSijoituksenMukaan/ResultWindow.qml")
            var popupWindow = popupComponent.createObject(parent);
            popupWindow.open();
        }
        else
        {
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

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Text {
                id: sliderDisplay1
                text: "Vuodesta\n" + yearSlider.first.value
                font.pixelSize: 20
            }

            RangeSlider {
                Layout.alignment: Qt.AlignHCenter
                implicitWidth: parent.parent.parent.width / 2
                height: 100
                id: yearSlider
                from: 1975
                to: 2022
                first.value: 1995
                second.value: 2002
                stepSize: 1
                snapMode: "SnapAlways"
            }

            Text {
                id: sliderDisplay2
                text: "Vuoteen\n" + yearSlider.second.value
                font.pixelSize: 20
            }
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
                spacing: 20

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

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 5
            Text {
                Layout.alignment: Qt.AlignHCenter

                text: qsTr("Top sijoitukset")
                font.pixelSize: 15
            }

            SpinBox {
                id: rankSpinBox
                value: 5
                editable: true
                to: 10000
            }

        }

        SearchButton {
            id: searchButton
            Layout.alignment: Qt.AlignHCenter
            onClicked: viewClickHandler()
        }
    }
}
