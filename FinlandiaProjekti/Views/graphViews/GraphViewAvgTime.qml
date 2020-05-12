import QtQuick 2.0
import QtQuick.Controls 1.4
import QtCharts 2.3

Item{

    ChartView {
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        height: parent.height - 50

        title: ""
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

        ScatterSeries {
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
        modelGraph.parsePointsForPlottingAvg()
        let travel = modelGraph.travel();
        let rankMax = modelGraph.rankMax();

        vuosiInt.min = modelGraph.minYear() - 1;
        vuosiInt.max = modelGraph.maxYear() - (-1);
        vuosiInt.tickCount = vuosiInt.max-vuosiInt.min - (-1)

        lowerHorizontalTicsOfLargeTable();

        seriesOne.name = "Top "
                + rankMax
                + " urheilijoiden keskimäärinen aika tunteina"
                + "\nvuosina "
                + modelGraph.minYear()
                + "-"
                + modelGraph.maxYear()
                + " matkalla "
                + travel

        while (modelGraph.isThereMoreData()) {
            let y = modelGraph.getPointY();
            let x = modelGraph.getPointX();
            console.log("appending:",y,",",x)
            seriesOne.append(x,y);
        }
    }
}
