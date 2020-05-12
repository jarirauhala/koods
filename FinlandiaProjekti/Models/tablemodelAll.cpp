#include "tablemodelAll.h"



TablemodelAll::TablemodelAll(std::shared_ptr<DataHandler> handler, QObject *parent) :
    QAbstractTableModel(parent),
    handler_(handler)
{
}

int TablemodelAll::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return table_.size();
}

int TablemodelAll::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return roleNames().size();
}

QVariant TablemodelAll::data(const QModelIndex &index, int role) const
{
    QVariant variant;
    const int row = index.row();
    const int column = role;

    switch (column) {
    case VUOSI:{
        variant = table_.at(row).vuosi;
        break;
    }
    case MATKA:{
        variant = table_.at(row).matka;
        break;
    }
    case TULOS:{
        variant = table_.at(row).tulos;
        break;
    }
    case SIJA:{
        variant = table_.at(row).sija;
        break;
    }
    case SIJAM:{
        variant = table_.at(row).sijaM;
        break;
    }
    case SIJAN:{
        variant = table_.at(row).sijaN;
        break;
    }
    case SUKUPUOLI:{
        variant = table_.at(row).sukupuoli;
        break;
    }
    case NIMI:{
        variant = table_.at(row).nimi;
        break;
    }
    case PAIKKAKUNTA:{
        variant = table_.at(row).paikkakunta;
        break;
    }
    case KANSALLISUUS:{
        variant = table_.at(row).kansallisuus;
        break;
    }
    case SYNTYMAVUOSI:{
        variant = table_.at(row).syntymavuosi;
        break;
    }
    case JOUKKUE:{
        variant = table_.at(row).joukkue;
        break;
    }
    }

    return variant;
}

QHash<int, QByteArray> TablemodelAll::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(VUOSI, "vuosi");
    roles.insert(MATKA, "matka");
    roles.insert(TULOS, "tulos");
    roles.insert(SIJA, "sija");
    roles.insert(SIJAM, "sijaM");
    roles.insert(SIJAN, "sijaN");
    roles.insert(SUKUPUOLI, "sukupuoli");
    roles.insert(NIMI, "nimi");
    roles.insert(PAIKKAKUNTA, "paikkakunta");
    roles.insert(KANSALLISUUS, "kansallisuus");
    roles.insert(SYNTYMAVUOSI, "syntymavuosi");
    roles.insert(JOUKKUE, "joukkue");

    return roles;
}

bool TablemodelAll::setData(const QModelIndex &index, const QVariant &value, int role)
{
    rowAll tableRow = table_.at(index.row());
    switch (role) {
    case VUOSI:
        tableRow.vuosi = value.toString();
        break;
    case MATKA:
        tableRow.matka = value.toString();
        break;
    case TULOS:
        tableRow.tulos = value.toString();
        break;
    case SIJA:
        tableRow.sija = value.toString();
        break;
    case SIJAM:
        tableRow.sijaM = value.toString();
        break;
    case SIJAN:
        tableRow.sijaN = value.toString();
        break;
    case SUKUPUOLI:
        tableRow.sukupuoli = value.toString();
        break;
    case NIMI:
        tableRow.nimi = value.toString();
        break;
    case PAIKKAKUNTA:
        tableRow.paikkakunta = value.toString();
        break;
    case KANSALLISUUS:
        tableRow.kansallisuus = value.toString();
        break;
    case SYNTYMAVUOSI:
        tableRow.syntymavuosi = value.toString();
        break;
    case JOUKKUE:
        tableRow.joukkue = value.toString();
        break;
    }

    return true;
}

void TablemodelAll::resetModel()
{
    beginResetModel();
    table_.clear();
    endResetModel();
}

bool TablemodelAll::updateDataHaeAikojenMukaan(const int &year, const QString &timeMin, const QString &timeMax)
{
    resetModel();

    const int index = table_.size();
    beginInsertRows(QModelIndex(), index, index);

    if(!handler_->haeAikojenMukaan(table_, year, timeMin, timeMax)) {
        resetModel();
        setErrorMessage(handler_->errorMessage());
        endInsertRows();
        return false;
    }

    endInsertRows();
    return true;
}

bool TablemodelAll::updateDataTuloksetAakkosittain(const int &year)
{
    resetModel();

    const int index = table_.size();
    beginInsertRows(QModelIndex(), index, index);

    if(!handler_->tuloksetAakkosittain(table_, year)) {
        resetModel();
        setErrorMessage(handler_->errorMessage());
        endInsertRows();
        return false;
    }

    endInsertRows();
    return true;
}

void TablemodelAll::testPrintTable()
{
    for(auto i : table_){
        qDebug() << "table contents: "
                 << i.joukkue << i.kansallisuus
                 << i.matka << i.nimi
                 << i.paikkakunta << i.sija
                 << i.sijaM << i.sijaN
                 << i.sukupuoli << i.syntymavuosi
                 << i.tulos << i.vuosi;
    }
}

QString TablemodelAll::errorMessage() const
{
    return errorMessage_;
}

void TablemodelAll::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}
