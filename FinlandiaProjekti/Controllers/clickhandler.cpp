#include "clickhandler.h"


#include <QDebug>

ClickHandler::ClickHandler(std::shared_ptr<InputValidator> validator,
                           std::shared_ptr<TablemodelAll> modelAll,
                           std::shared_ptr<TableModelBest> modelBest,
                           std::shared_ptr<TableModelComparison1> modelComp1,
                           std::shared_ptr<TableModelComparison2> modelComp2,
                           std::shared_ptr<TableModelYearly> modelYearly,
                           std::shared_ptr<GraphModel> modelGraph,
                           QObject *parent):
    QObject(parent),
    validator_(validator),
    modelAll_(modelAll),
    modelBest_(modelBest),
    modelComp1_(modelComp1),
    modelComp2_(modelComp2),
    modelYearly_(modelYearly),
    modelGraph_(modelGraph)

{

}

bool ClickHandler::eriMatkojenVertailuClicked(const QString &year, const QString &travel1,
                                             const QString &travel2, const QString &names)
{
    std::vector<QString> namesVect;

    if(validator_->eriMatkojenVertailu(year, names, namesVect)) {
        int yearInt = year.toInt();
        if (modelComp1_->updateDataVertailu(travel1,yearInt,namesVect)) {
            if (modelComp2_->updateDataVertailu(travel2,yearInt,namesVect)) {
                return true;
            }
            else {
                setErrorMessage(modelComp2_->errorMessage());
                return false;
            }
        }
        else {
            setErrorMessage(modelComp1_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }
}

bool ClickHandler::haeAikojenMukaanClicked(const QString &year, const QString &timeMin,
                                           const QString &timeMax)
{
    if(validator_->validateYear(year)) {
        int yearInt = year.toInt();
        if(modelAll_->updateDataHaeAikojenMukaan(yearInt, timeMin, timeMax)) {
            return true;
        }
        else {
            setErrorMessage(modelAll_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }
}

bool ClickHandler::parhaatJoukkueetClicked(const QString &year, const QString &travel)
{
    if(validator_->parhaatJoukkueet(year)) {
        int yearInt = year.toInt();
        if(modelBest_->updateDataParhaatJoukkueet(yearInt, travel)) {
            return true;
        }
        else {
            setErrorMessage(modelBest_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }}

bool ClickHandler::samanMatkanVertailuClicked(const QString &travel, const QString &year1,
                                              const QString &year2, const QString &names)
{
    std::vector<QString> namesVect;

    if(validator_->samanMatkanVertailu(year1,year2,names,namesVect)) {
        int yearInt1 = year1.toInt();
        int yearInt2 = year2.toInt();
        if (modelComp1_->updateDataVertailu(travel,yearInt1,namesVect)) {
            if (modelComp2_->updateDataVertailu(travel,yearInt2,namesVect)) {
                return true;
            }
            else {
                setErrorMessage(modelComp2_->errorMessage());
                return false;
            }
        }
        else {
            setErrorMessage(modelComp1_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }
}

bool ClickHandler::tuloksetAakkosittainClicked(const QString &year)
{
    if(validator_->validateYear(year)) {
        int yearInt = year.toInt();
        if (modelAll_->updateDataTuloksetAakkosittain(yearInt)) {
            return true;
        }
        else {
            setErrorMessage(modelYearly_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }}

bool ClickHandler::vuosittaisetTilastotClicked(const QString &year)
{
    if(validator_->validateYear(year)) {
        int yearInt = year.toInt();
        if (modelYearly_->updateDataVuosittaisetTilastot(yearInt)) {
            return true;
        }
        else {
            setErrorMessage(modelYearly_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }
}

bool ClickHandler::urheilijanKehitysClicked(const QString &name, const QString &year1,
                                            const QString &year2, const QString &matka)
{
    if(validator_->urheilijanKehitys(name, year1, year2))
    {
        if (modelGraph_->updateDataUrheilijanKehitys (name, year1, year2, matka)){
            return true;
        }
        else {
            setErrorMessage(modelGraph_->errorMessage());
            return false;
        }
    }
    else {
        setErrorMessage(validator_->errorMessage());
        return false;
    }
}

//void ClickHandler::updateUrheilijanKehitys()
//{
//    modelDevelopment_->updateChart();
//}

bool ClickHandler::jakaumaMaittainClicked(const QString &year1, const QString &year2)
{
    // no need for input validation

    if (modelGraph_->updateJakaumaMaittain(year1, year2)){
        return true;
    }
    else {
        setErrorMessage(modelGraph_->errorMessage());
        return false;
    }
}

bool ClickHandler::keskinopeusSijoituksenMukaanClicked(const QString &year1, const QString &year2, const QString &travel, const QString &rankMax)
{
    // no need for input validation

    if (modelGraph_->updateDataKeskinopeusSijoituksenMukaan(year1, year2, travel, rankMax)){
        return true;
    }
    else {
        setErrorMessage(modelGraph_->errorMessage());
        return false;
    }
}

bool ClickHandler::parhaanSijoitusClicked(const QString &gender, const QString &year1, const QString &year2, const QString &travel)
{
    // no need for input validation

    if (modelGraph_->updateDataParhaanSijoitus (gender, year1, year2, travel)){
        return true;
    }
    else {
        setErrorMessage(modelGraph_->errorMessage());
        return false;
    }
}

QString ClickHandler::errorMessage() const
{
    return errorMessage_;
}

void ClickHandler::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}
