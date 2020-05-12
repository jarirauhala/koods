import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.11

RowLayout {
    id: splitCompView
    TableViewComp1 {
        id: comp1
        width: parent.parent.width / 2
        height: parent.parent.height
    }

    TableViewComp2 {
        width: parent.parent.width / 2
        height: parent.parent.height
    }
}
