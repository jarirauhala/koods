#ifndef CLICKHANDLER_H
#define CLICKHANDLER_H

#include "inputvalidator.h"
#include "../Models/tablemodelAll.h"
#include "../Models/tablemodelbest.h"
#include "../Models/tablemodelcomparison1.h"
#include "../Models/tablemodelcomparison2.h"
#include "../Models/tablemodelyearly.h"
#include "../Models/graphmodel.hh"

#include <QObject>
#include <memory>

class InputValidator;
class TablemodelAll;
class TableModelBest;
class TableModelComparison1;
class TableModelComparison2;
class TableModelYearly;
class GraphModelDevelopment;
class GraphModel;

// ClickHandler class is called by different views.
// It calls InputValidator to validate inputs
// recieved as parameters.
// For proper inputs model is called. for updating
// In case of an invalid input or an error in model
// updating false is returned and Q_PROPERTY
// errorMessage updated.


class ClickHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString errorMessage MEMBER errorMessage_ NOTIFY errorMessageChanged)

public:
    explicit ClickHandler(std::shared_ptr<InputValidator> validator,
                          std::shared_ptr<TablemodelAll> modelAll,
                          std::shared_ptr<TableModelBest> modelBest,
                          std::shared_ptr<TableModelComparison1> modelComp1,
                          std::shared_ptr<TableModelComparison2> modelComp2,
                          std::shared_ptr<TableModelYearly> modelYearly,
                          std::shared_ptr<GraphModel> modelGraph,
                          QObject *parent = nullptr);



    //
    Q_INVOKABLE bool eriMatkojenVertailuClicked(const QString &year, const QString &travel1,
                                               const QString &travel2, const QString &names);
    Q_INVOKABLE bool haeAikojenMukaanClicked(const QString &year, const QString &timeMin,
                                             const QString &timeMax);
    Q_INVOKABLE bool parhaatJoukkueetClicked(const QString &year, const QString &travel);
    Q_INVOKABLE bool samanMatkanVertailuClicked(const QString &travel, const QString &year1,
                                                const QString &year2, const QString &names);
    Q_INVOKABLE bool tuloksetAakkosittainClicked(const QString &year);
    Q_INVOKABLE bool vuosittaisetTilastotClicked(const QString &year);

    // graph views
    Q_INVOKABLE bool urheilijanKehitysClicked(const QString &name, const QString &year1,
                                              const QString &year2, const QString &matka);

    Q_INVOKABLE bool jakaumaMaittainClicked(const QString &year1, const QString &year2);
    Q_INVOKABLE bool keskinopeusSijoituksenMukaanClicked(const QString &year1, const QString &year2,
                                                         const QString &travel, const QString &rankMax);
    Q_INVOKABLE bool parhaanSijoitusClicked(const QString &gender, const QString &year1,
                                            const QString &year2, const QString &travel);

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

signals:
    void errorMessageChanged();

public slots:

private:
    QString errorMessage_;
    std::shared_ptr<InputValidator> validator_;
    std::shared_ptr<TablemodelAll> modelAll_;
    std::shared_ptr<TableModelBest> modelBest_;
    std::shared_ptr<TableModelComparison1> modelComp1_;
    std::shared_ptr<TableModelComparison2> modelComp2_;
    std::shared_ptr<TableModelYearly> modelYearly_;
    std::shared_ptr<GraphModelDevelopment> modelDevelopment_;
    std::shared_ptr<GraphModel> modelGraph_;
};

#endif // CLICKHANDLER_H
