#ifndef GRAPHMODEL_HH
#define GRAPHMODEL_HH

#include "Models/rowstructs.h"
#include "datahandler.h"


#include <QObject>
#include <memory>

class DataHandler;

class GraphModel : public QObject
{
    Q_OBJECT

    struct dataPoint {
        QString x;
        QString y;
    };

    struct dataSeries {
        QString nimi;
        QString matka;
        QList<dataPoint> points;
    };


public:
    explicit GraphModel(std::shared_ptr<DataHandler> handler,
                        QObject *parent = nullptr);

    bool updateDataUrheilijanKehitys(const QString &name, const QString &year1,
                                     const QString &year2, const QString &travel);

    bool updateJakaumaMaittain(const QString &year1, const QString &year2);
    bool updateDataKeskinopeusSijoituksenMukaan (const QString &year1, const QString &year2,
                                                 const QString &travel, const QString &rankMax);
    bool updateDataParhaanSijoitus (const QString &gender, const QString &year1,
                                    const QString &year2, const QString &travel);

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

    bool updateData();
    QString timeToHour(QString time);


    Q_INVOKABLE bool isThereMoreData(); // checks if there is something in points_
    Q_INVOKABLE QString getPointX(); // returns x coord of first point in points and removes the point from points_
    Q_INVOKABLE QString getPointY(); // returns y coord of first point in points
    Q_INVOKABLE QString maxYear() {return year2_;}
    Q_INVOKABLE QString minYear() {return year1_;}

    // Urheilijan kehitys
    Q_INVOKABLE void parsePointsForPlottingDev(); // prepares points from tableDevelopment_ to be plotted and stores them to points_
    Q_INVOKABLE QString getName(); // returns the name of the skier
    Q_INVOKABLE QString getTrip(); // returns the trip

    // Jakauma maittain
    Q_INVOKABLE void parsePointsForPlottingDist();

    // Keskinopeus sijoituksen mukaan
    Q_INVOKABLE void parsePointsForPlottingAvg();
    Q_INVOKABLE QString travel() {return travel_;}
    Q_INVOKABLE QString rankMax() {return rankMax_;}

    // Parhaan sijoitus
    Q_INVOKABLE void parsePointsForPlottingBest();
    Q_INVOKABLE QString gender() {return gender_;}
    Q_INVOKABLE QString getBiggestRank();


signals:

private:
    std::shared_ptr<DataHandler> handler_;

    QList<rowDevelopment> tableDevelopment_;
    QList<rowDistribution> tableDistribution_;
    QList<rowAvgTime> tableAvgTime_;
    QList<rowRankBest> tableRankBest_;

    QString year1_;
    QString year2_;
    QString gender_;
    QString travel_;
    QString rankMax_;


    QString errorMessage_ = "";

    QList<dataPoint> points_;

};

#endif // GRAPHMODEL_HH
