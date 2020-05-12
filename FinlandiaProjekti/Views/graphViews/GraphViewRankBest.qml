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
            max: 5
            labelFormat: "%.0f"
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

    function lowerVerticalTicsOfLargeTable() {
        if (tulosInt.tickCount > 300) {
            while (tulosInt.tickCount % 30 != 0) {
                tulosInt.tickCount -= 1;
            }
            tulosInt.tickCount = vuosiInt.tickCount / 30;
            tulosInt.tickCount += 1;
        }
        else if (tulosInt.tickCount > 100) {
            while (tulosInt.tickCount % 15 != 0) {
                tulosInt.tickCount -= 1;
            }
            tulosInt.tickCount = vuosiInt.tickCount / 15;
            tulosInt.tickCount += 1;
        }
        else if (tulosInt.tickCount > 40) {

            while (tulosInt.tickCount % 5 != 0) {
                tulosInt.tickCount -= 1;
            }

            tulosInt.tickCount = tulosInt.tickCount / 5;
            tulosInt.tickCount += 1;



        }
        else if (tulosInt.tickCount > 20) {
            while (tulosInt.tickCount % 2 != 0) {
                tulosInt.tickCount -= 1;
            }
            tulosInt.tickCount = tulosInt.tickCount / 2;
        }
    }

    function populateChartData()
    {
        modelGraph.parsePointsForPlottingBest()
        let gender = modelGraph.gender();
        let travel = modelGraph.travel();

        vuosiInt.min = modelGraph.minYear() - 1;
        vuosiInt.max = modelGraph.maxYear() - (-1);
        vuosiInt.tickCount = vuosiInt.max-vuosiInt.min - (-1)


        lowerHorizontalTicsOfLargeTable();

        tulosInt.max = modelGraph.getBiggestRank()
        tulosInt.tickCount = tulosInt.max - (-1)

        console.log("ticks:", tulosInt.tickCount)


        lowerVerticalTicsOfLargeTable();

        console.log("ticks:", tulosInt.tickCount)


        console.log("gender:", gender)

        if (gender === "F") {
            seriesOne.name = "Parhaan naisen sijoitus\nvuosina "
                    + modelGraph.minYear() + "-" + modelGraph.maxYear()
                    + " matkalla " + travel
        }
        else {
            seriesOne.name = "Parhaan miehen sijoitus\nvuosina "
                    + modelGraph.minYear() + "-" + modelGraph.maxYear()
                    + " matkalla " + travel
        }

        while (modelGraph.isThereMoreData()) {
            let y = modelGraph.getPointY();
            let x = modelGraph.getPointX();
            seriesOne.append(x,y);
        }
    }
}
