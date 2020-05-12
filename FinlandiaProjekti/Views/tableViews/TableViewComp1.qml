import QtQuick 2.0
import QtQuick.Controls 1.4

TableView {
    id: windComp1
    implicitHeight: parent.parent.height - 50
    implicitWidth: parent.parent.width / 2

    model: tableModelComp1

    TableViewColumn {
        id: sarakea
        role: "tulos"
        title: "Tulos"
        width: (parent.width) / 10
    }

    TableViewColumn {
        id: sarakeb
        role: "sija"
        title: "Sija"
        width: (parent.width) / 10
    }

    TableViewColumn {
        id: sarakec
        role: "nimi"
        title: "Nimi"
        width: (parent.width) / 10
    }
    TableViewColumn {
        id: saraked
        role: "syntymavuosi"
        title: "Syntymävuosi"
        width: (parent.width) / 10
    }
    TableViewColumn {
        id: sarakee
        role: "kansallisuus"
        title: "Kansallisuus"
        width: (parent.width) / 10
    }
}
