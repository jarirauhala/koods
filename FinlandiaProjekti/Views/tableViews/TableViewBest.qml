import QtQuick 2.0
import QtQuick.Controls 1.4


Item {
    id: windd

    TableView {
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        height: parent.height - 50
        model: tableModelBest

        TableViewColumn {
            id: sarakea
            role: "sija"
            title: "Sija"
            width: (parent.width - 20) / 3
        }

        TableViewColumn {
            id: sarakeb
            role: "joukkue"
            title: "Joukkue"
            width: (parent.width - 20) / 3
        }

        TableViewColumn {
            id: sarakec
            role: "aikayhteensa"
            title: "Aika keskimäärin"
            width: (parent.width - 20) / 3
        }
    }
}

