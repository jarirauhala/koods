import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import "./components"

Item {
    x: 1
    y: 1
    width: parent.width
    height: parent.height
    focus: true
    Text {
        anchors.top: parent.top
        anchors.left: parent.left
        id: header1
        text: qsTr("Finlandia-haku")
        color: "cadetblue"
        font.pixelSize:50
        x:10
    }

    Rectangle {
        id: secretAnchor
        anchors.top: header1.bottom
        anchors.left: header1.left
    }

    RowLayout {
        id: row1
        anchors.top: header1.bottom
        anchors.topMargin: 30
        anchors.left: header1.left
        anchors.leftMargin: (parent.parent.width - 400) /3
        spacing: (parent.parent.width - 400) /3

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            spacing: (parent.parent.parent.height - 400) / 7
            Text {
                Layout.alignment: Qt.AlignHCenter
                id: header2
                text: "Hae taulukoita:"
                font.pixelSize: 30
            }

            OperationButton1 {
                Layout.alignment: Qt.AlignHCenter
                id: eriMatkojenVertailuButton
                text: "Eri matkojen vertailu"
                onClicked: {
                    var popupComponent = Qt.createComponent("qrc:/eriMatkojenVertailu/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }
            OperationButton1 {
                Layout.alignment: Qt.AlignHCenter
                id: haeAikojenMukaanButton
                text: "Hae aikojen mukaan"

                onClicked: {
                    var popupComponent = Qt.createComponent("qrc:/haeAikojenMukaan/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton1 {
                Layout.alignment: Qt.AlignHCenter
                id: parhaatJoukkueetButton
                text: "Parhaat joukkueet"

                onClicked: {
                    var popupComponent = Qt.createComponent("qrc:/parhaatJoukkueet/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton1 {
                Layout.alignment: Qt.AlignHCenter
                id: samanMatkanVertailuButton
                text: "Saman matkan vertailu"

                onClicked: {
                    var popupComponent = Qt.createComponent("qrc:/samanMatkanVertailu/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton1 {
                Layout.alignment: Qt.AlignHCenter
                id: tuloksetAakkosittainButton
                text: "Tulokset aakkosittain"

                onClicked: {
                    var popupComponent = Qt.createComponent("tuloksetAakkosittain/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton1 {
                Layout.alignment: Qt.AlignHCenter
                id: vuosittaisetTilastotButton
                text: "Vuosittaiset tilastot"

                onClicked: {
                    var popupComponent = Qt.createComponent("vuosittaisetTilastot/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            spacing: (parent.parent.parent.height - 400) / 7
            Text {
                id: header3
                text: "Hae kuvaajia:"
                font.pixelSize: 30
            }

            // Tänne napit kuvaajien toiminnallisuuksille

            OperationButton2 {
                Layout.alignment: Qt.AlignHCenter
                id: urheilijanKehitysButton
                text: "Urheilijan kehitys"

                onClicked: {
                    var popupComponent = Qt.createComponent("urheilijanKehitys/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton2 {
                Layout.alignment: Qt.AlignHCenter
                id: jakaumaMaittainButton
                text: "Jakauma maittain"

                onClicked: {
                    var popupComponent = Qt.createComponent("jakaumaMaittain/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton2 {
                Layout.alignment: Qt.AlignHCenter
                id: keskinopeusSijoituksenMukaanButton
                text: "Keskinopeus sijoituksen mukaan"

                onClicked: {
                    var popupComponent = Qt.createComponent("keskinopeusSijoituksenMukaan/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }

            OperationButton2 {
                Layout.alignment: Qt.AlignHCenter
                id: parhaanSijoitusButton
                text: "Parhaan sijoitus"

                onClicked: {
                    var popupComponent = Qt.createComponent("parhanSijoitus/QuestionWindow.qml")
                    var popupWindow = popupComponent.createObject(secretAnchor);
                    popupWindow.open()
                }
            }
        }
    }
}
