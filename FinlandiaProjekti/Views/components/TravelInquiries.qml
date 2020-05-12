import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

// used to parse travel as QString from user input
ColumnLayout {
    id: travelInqElements

    function travelParser() {
        var travel = "";
        if(styleSlider.value === 1) {
            travel += "V";
        }
        else {
            travel += "P";
        }

        travel += travels.textFromValue(travels.value);
        if (juniorBox.checked) {
            travel += "jun";
        }

        return travel;
    }

    RowLayout {
        Text {
            id: styleIndicator1
            text: qsTr("Tyyli:\nPerinteinen")
            font.pixelSize: 15
        }

        Slider {
            id: styleSlider
            implicitWidth: 80
            from: 0
            value: 0
            to: 1
            stepSize: 1
            snapMode: "SnapAlways"
            onValueChanged: function () {
                if (value === 0) {
                    styleIndicator1.text = "Tyyli:\nPerinteinen"
                }
                else {
                    styleIndicator1.text = "Tyyli:\nVapaa      "
                }
            }
        }
    }

    RowLayout {
        SpinBox {
            id: travels
            from: 0
            to: items.length -1
            value: 0

            property var items: ["20","25","30","32","35","42","45","50","52","53","60","62","75","100"]
            validator: RegExpValidator {
                regExp: new RegExp("(20|25|30|32|35|42|45|50|52|53|60|62|75|100)","i")
            }

            textFromValue: function(value) {
                return items[value];
            }

            valueFromText: function(text) {
                for (var i = 0; i < items.length; ++i) {
                    if (items[i].toLowerCase().indexOf(text.toLowerCase()) === 0)
                        return i;
                }
                return travels.value
            }
        }

        Text {
            text: "km"
            font.pixelSize: 15
        }
    }

    RowLayout {
        CheckBox {
            id: juniorBox
        }

        Text {
            id: juniorText
            text: qsTr("Juniorisarja")
            font.pixelSize: 15
        }
    }
}
