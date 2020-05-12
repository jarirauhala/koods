#include "graphmodel.hh"

GraphModel::GraphModel(std::shared_ptr<DataHandler> handler, QObject *parent) :
    QObject(parent),
    handler_(handler)

{

}


bool GraphModel::updateDataUrheilijanKehitys(const QString &name, const QString &year1,
                                             const QString &year2, const QString &travel)
{
    if(!handler_->urheilijanKehitys(tableDevelopment_, name, year1, year2, travel)) {
        setErrorMessage(handler_->errorMessage());
        return false;
    }

    year1_ = year1;
    year2_ = year2;

    parsePointsForPlottingDev();
    return true;
}

bool GraphModel::updateJakaumaMaittain(const QString &year1, const QString &year2)
{
    bool dataOK = handler_->jakaumaMaittain(tableDistribution_, year1, year2);

    if(!dataOK) {
        setErrorMessage(handler_->errorMessage());
        return false;
    }


    year1_ = year1;
    year2_ = year2;

    return true;
}

bool GraphModel::updateDataKeskinopeusSijoituksenMukaan(const QString &year1, const QString &year2, const QString &travel, const QString &rankMax)
{
    bool dataOK = handler_->keskinopeusSijoituksenMukaan(tableAvgTime_, travel, year1, year2, rankMax);

    if(!dataOK) {
        setErrorMessage(handler_->errorMessage());
        return false;
    }

    year1_ = year1;
    year2_ = year2;
    travel_ = travel;
    rankMax_ = rankMax;

    parsePointsForPlottingAvg();

    return true;
}

bool GraphModel::updateDataParhaanSijoitus(const QString &gender, const QString &year1, const QString &year2, const QString &travel)
{
    bool dataOK = handler_->parhaanSijoitus(tableRankBest_, gender, year1, year2, travel);

    if(!dataOK) {
        setErrorMessage(handler_->errorMessage());
        return false;
    }

    year1_ = year1;
    year2_ = year2;
    gender_ = gender;
    travel_ = travel;

    parsePointsForPlottingBest();

    return true;
}

QString GraphModel::timeToHour(QString time)
{
    double result=0;
    bool okh=0;
    bool okm=0;
    bool oks=0;

    double hours=time.split(":")[0].toDouble(&okh);
    if (okh==true)
    {
        result=result+hours;
    }
    double minutes=time.split(":")[1].toDouble(&okm);
    double seconds=time.split(":")[2].toDouble(&oks);


    if (okm==true)
    {
        result=result+(minutes/60);
    }
    if (oks==true)
    {
        result=result+(seconds/3600);
    }

    QString resultQStr;
    resultQStr = QString::number(result);

    return resultQStr;
}

bool GraphModel::isThereMoreData()
{
    if (points_.size() != 0) {
        return true;
    }
    else {
        return false;
    }
}

QString GraphModel::getName()
{
    if (!isThereMoreData()) {
        return "NO DATA";
    }

    QString nimi;
    nimi = tableDevelopment_[0].nimi;
    return nimi;
}

QString GraphModel::getTrip()
{
    if (!isThereMoreData()) {
        return "NO DATA";
    }

    QString matka;
    matka = tableDevelopment_[0].matka;
    return matka;
}

void GraphModel::parsePointsForPlottingDist()
{
    dataPoint newPoint;

    points_.clear();

    for (rowDistribution row : tableDistribution_) {

        QString country = row.maa;
        QString amount = row.lukum;

        newPoint.x = country;
        newPoint.y = amount;

        points_.append(newPoint);
    }
}

void GraphModel::parsePointsForPlottingAvg()
{
    dataPoint newPoint;

    points_.clear();

    for (rowAvgTime row : tableAvgTime_) {
        QString year = row.vuosi;
        QString time = row.keskinopeus;

        newPoint.x = year;
        newPoint.y = time;

        points_.append(newPoint);
    }
}

void GraphModel::parsePointsForPlottingBest()
{
    dataPoint newPoint;

    points_.clear();

    for (rowRankBest row : tableRankBest_) {
        QString year = row.vuosi;
        QString rank = row.sijoitus;

        newPoint.x = year;
        newPoint.y = rank;

        points_.append(newPoint);
    }
}

QString GraphModel::getBiggestRank()
{
    int biggest = 0;
    for (rowRankBest row : tableRankBest_) {
        QString rank = row.sijoitus;

        int rankint = rank.toInt();

        if (rankint > biggest) {
            biggest = rankint;
        }
    }

    ++biggest;

    QString biggestStr = QString::number(biggest);
    return biggestStr;
}

void GraphModel::parsePointsForPlottingDev()
{
    QString year;
    QString time;
    dataPoint newPoint;

    points_.clear();

    for (rowDevelopment row : tableDevelopment_) {

        time = timeToHour(row.tulos);
        year = row.vuosi;

        newPoint.x = year;
        newPoint.y = time;
        points_.append(newPoint);
    }

}

QString GraphModel::getPointX()
{

    if (!isThereMoreData()) {
        return "-1";
    }

    QString x;
    x = points_[0].x;

    points_.pop_front();
    return x;
}

QString GraphModel::getPointY()
{
    if (!isThereMoreData()) {
        return "-1";
    }
    QString y;
    y = points_[0].y;
    return y;
}

QString GraphModel::errorMessage() const
{
    return errorMessage_;
}

void GraphModel::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}

