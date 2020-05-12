import QtQuick 2.0
import QtQuick.Controls 1.4
import QtCharts 2.3

Item{

    ChartView {
        id: windDevelopment

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        height: parent.height - 50

        title: "Vuosittaiset tilastot"
        antialiasing: true
        onSeriesAdded: populateChartData()

        ValueAxis {
            id: tulosInt
            max: 12
        }
        ValueAxis {
            id: vuosiInt
            max: 2000
            min: 1990
            labelFormat: "%.0f"
        }

         LineSeries {
            id:seriesOne
            name: "Kehitys"
            axisX: vuosiInt
            axisY: tulosInt
        }
    }

    function lowerHorizontalTicsOfLargeTable() {

        if (vuosiInt.tickCount > 40) {
            while (vuosiInt.tickCount % 5 != 0) {
                vuosiInt.tickCount -= 1;
            }
            vuosiInt.tickCount = vuosiInt.tickCount / 5;
            vuosiInt.tickCount += 1;

        }
        else if (vuosiInt.tickCount > 20) {
            while (vuosiInt.tickCount % 2 != 0) {
                vuosiInt.tickCount -= 1;
            }
            vuosiInt.tickCount = vuosiInt.tickCount / 2;
        }
    }

    function populateChartData()
    {
        let name = modelGraph.getName();
        let trip = modelGraph.getTrip();
        vuosiInt.min = modelGraph.minYear() - 1;
        vuosiInt.max = modelGraph.maxYear() - (-1);
        vuosiInt.tickCount = vuosiInt.max-vuosiInt.min - (-1)
        seriesOne.name = name + " - aika tunteina - matkalla " + trip;

        lowerHorizontalTicsOfLargeTable();

        while (modelGraph.isThereMoreData()) {
            let y = modelGraph.getPointY();
            let x = modelGraph.getPointX();
            seriesOne.append(x,y);
        }
    }
}
