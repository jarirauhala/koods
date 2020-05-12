#ifndef TABLEMODELALL_H
#define TABLEMODELALL_H

#include "rowstructs.h"
#include "datahandler.h"

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QHash>
#include <QVariant>
#include <QByteArray>
#include <QList>
#include <memory>
#include <QDebug>

class DataHandler;

class TablemodelAll : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum RoleName {
        VUOSI = 0,
        MATKA = 1,
        TULOS = 2,
        SIJA = 3,
        SIJAM = 4,
        SIJAN = 5,
        SUKUPUOLI = 6,
        NIMI = 7,
        PAIKKAKUNTA = 8,
        KANSALLISUUS = 9,
        SYNTYMAVUOSI = 10,
        JOUKKUE = 11
    };

    explicit TablemodelAll(std::shared_ptr<DataHandler> handler,
                         QObject *parent = nullptr);

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    // Remove all data:
    void resetModel();

    // calls for datahandler
    bool updateDataHaeAikojenMukaan(const int &year, const QString &timeMin, const QString &timeMax);
    bool updateDataTuloksetAakkosittain(const int &year);

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

protected:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;


private:
    QList<rowAll> table_;
    std::shared_ptr<DataHandler> handler_;

    void testPrintTable();

    QString errorMessage_ = "";

};

#endif // TABLEMODELALL_H
