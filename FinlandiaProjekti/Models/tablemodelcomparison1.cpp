#include "tablemodelcomparison1.h"


TableModelComparison1::TableModelComparison1(std::shared_ptr<DataHandler> handler, QObject *parent)
    : QAbstractTableModel(parent),
      handler_(handler)
{
}

int TableModelComparison1::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return table_.size();
}

int TableModelComparison1::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return roleNames().size();
}

QVariant TableModelComparison1::data(const QModelIndex &index, int role) const
{
    QVariant variant;
    const int row = index.row();
    const int column = role;

    switch (column) {
    case TULOS:{
        variant = table_.at(row).tulos;
        break;
    }
    case SIJA:{
        variant = table_.at(row).sija;
        break;
    }
    case NIMI:{
        variant = table_.at(row).nimi;
        break;
    }
    case SYNTYMAVUOSI:{
        variant = table_.at(row).syntymavuosi;
        break;
    }
    case KANSALLISUUS:{
        variant = table_.at(row).kansallisuus;
        break;
    }
    }

    return variant;
}

QHash<int, QByteArray> TableModelComparison1::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(TULOS, "tulos");
    roles.insert(SIJA, "sija");
    roles.insert(NIMI, "nimi");
    roles.insert(SYNTYMAVUOSI, "syntymavuosi");
    roles.insert(KANSALLISUUS, "kansallisuus");

    return roles;
}

bool TableModelComparison1::setData(const QModelIndex &index, const QVariant &value, int role)
{
    rowComparison tableRow = table_.at(index.row());
    switch (role) {
    case TULOS:
        tableRow.tulos = value.toString();
        break;
    case SIJA:
        tableRow.sija = value.toString();
        break;
    case NIMI:
        tableRow.nimi = value.toString();
        break;
    case SYNTYMAVUOSI:
        tableRow.syntymavuosi = value.toString();
        break;
    case KANSALLISUUS:
        tableRow.kansallisuus = value.toString();
        break;
    }

    return true;
}

void TableModelComparison1::resetModel()
{
    beginResetModel();
    table_.clear();
    endResetModel();
}

bool TableModelComparison1::updateDataVertailu(const QString &travel, const int &year,
                                               const std::vector<QString> &names)
{
    resetModel();

    const int index = table_.size();
    beginInsertRows(QModelIndex(), index, index);

    if(!handler_->vertailu(table_, travel, year, names)) {
        resetModel();
        setErrorMessage(handler_->errorMessage());
        endInsertRows();
        return false;
    }

    qDebug() << "Model 1 updated";

    endInsertRows();
    return true;


    qDebug() << "names recieved by model:";
    for ( auto name : names) {
        qDebug() << " " << name;
    }
}

QString TableModelComparison1::errorMessage() const
{
    return errorMessage_;
}

void TableModelComparison1::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}
