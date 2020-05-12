import QtQuick 2.0
import QtQuick.Controls 1.4
import QtCharts 2.3


Item {
    ChartView {

        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        height: parent.height - 50

        id: pieChartView

        function populateSeries() {
            modelGraph.parsePointsForPlottingDist();
            pieChartView.title = "Osallistujien jakauma maittain\nvuosina "
                    + modelGraph.minYear()
                    + "-"
                    + modelGraph.maxYear()

            while (modelGraph.isThereMoreData()) {
                let val = modelGraph.getPointY();
                let label = modelGraph.getPointX();
                pieSeries.append(label,val);
            }
        }

        theme: ChartView.ChartThemeBlueIcy
        antialiasing: true

        onSeriesAdded: populateSeries()

        PieSeries {
            id: pieSeries
        }
    }

}

