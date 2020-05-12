import QtQuick 2.0
import QtQuick.Controls 1.4


Item {
    id: windYearly

    TableView {
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        height: parent.height - 50

        model: tableModelYearly

        TableViewColumn {
            id: sarakea
            role: "vuosi"
            title: "Vuosi"
            width: (parent.width - 20) / 6
        }

        TableViewColumn {
            id: sarakeb
            role: "matka"
            title: "Matka"
            width: (parent.width - 20) / 6
        }

        TableViewColumn {
            id: sarakec
            role: "osallistujalkm"
            title: "Osallistujia"
            width: (parent.width - 20) / 6
        }
        TableViewColumn {
            id: saraked
            role: "huonoinAika"
            title: "Huonoin aika"
            width: (parent.width - 20) / 6
        }
        TableViewColumn {
            id: sarakee
            role: "parasAika"
            title: "Paras aika"
            width: (parent.width - 20) / 6
        }
        TableViewColumn {
            id: sarakef
            role: "keskinopeus"
            title: "Aika keskimäärin (min)"
            width: (parent.width - 20) / 6
        }
    }
}

