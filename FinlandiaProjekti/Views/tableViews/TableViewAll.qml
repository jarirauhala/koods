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

        model: tableModelAll

        TableViewColumn {
            id: sarakea
            role: "vuosi"
            title: "Vuosi"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakeb
            role: "matka"
            title: "Matka"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakec
            role: "tulos"
            title: "Tulos"
            width: (parent.width - 20) / 12
        }
        TableViewColumn {
            id: saraked
            role: "sija"
            title: "Sija"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakee
            role: "sijaM"
            title: "Sija_m"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakef
            role: "sijaN"
            title: "Sija_n"
            width: (parent.width - 20) / 12
        }
        TableViewColumn {
            id: sarakeg
            role: "sukupuoli"
            title: "Sukupuoli"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakeh
            role: "nimi"
            title: "Nimi"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakei
            role: "paikkakunta"
            title: "Paikkakunta"
            width: (parent.width - 20) / 12
        }
        TableViewColumn {
            id: sarakej
            role: "kansallisuus"
            title: "Kansallisuus"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakel
            role: "syntymavuosi"
            title: "Syntymävuosi"
            width: (parent.width - 20) / 12
        }

        TableViewColumn {
            id: sarakem
            role: "joukkue"
            title: "Joukkue"
            width: (parent.width - 20) / 12
        }
    }
}

