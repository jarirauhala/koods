#include "./Controllers/inputvalidator.h"
#include "./Controllers/clickhandler.h"
#include "./Models/tablemodelAll.h"
#include "./Models/tablemodelbest.h"
#include "./Models/tablemodelcomparison1.h"
#include "./Models/tablemodelcomparison2.h"
#include "./Models/tablemodelyearly.h"
#include "./Models/datahandler.h"
#include "./Models/graphmodel.hh"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include <memory>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto validator{std::make_shared<InputValidator>() };
    auto dataHandler{std::make_shared<DataHandler>() };

    auto modelAll{std::make_shared<TablemodelAll>(dataHandler) };
    auto modelBest{std::make_shared<TableModelBest>(dataHandler) };
    auto modelComp1{std::make_shared<TableModelComparison1>(dataHandler) };
    auto modelComp2{std::make_shared<TableModelComparison2>(dataHandler) };
    auto modelYearly{std::make_shared<TableModelYearly>(dataHandler) };
    auto modelGraph{std::make_shared<GraphModel>(dataHandler) };
    auto cHandler{std::make_shared<ClickHandler>(validator, modelAll, modelBest,
                                                 modelComp1, modelComp2, modelYearly,
                                                 modelGraph) };

    auto context{ engine.rootContext() };
    context->setContextProperty("clickHandler", cHandler.get());
    context->setContextProperty("tableModelAll", modelAll.get());
    context->setContextProperty("tableModelBest", modelBest.get());
    context->setContextProperty("tableModelComp1", modelComp1.get());
    context->setContextProperty("tableModelComp2", modelComp2.get());
    context->setContextProperty("tableModelYearly", modelYearly.get());
    context->setContextProperty("modelGraph", modelGraph.get());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
