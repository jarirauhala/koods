#include "tablemodelyearly.h"

TableModelYearly::TableModelYearly(std::shared_ptr<DataHandler> handler, QObject *parent)
    : QAbstractTableModel(parent),
      handler_(handler)
{
}

int TableModelYearly::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return table_.size();
}

int TableModelYearly::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return roleNames().size();
}

QVariant TableModelYearly::data(const QModelIndex &index, int role) const
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
    case OSALLISTUJALKM:{
        variant = table_.at(row).osallistujalkm;
        break;
    }
    case HUONOINAIKA:{
        variant = table_.at(row).huonoinAika;
        break;
    }
    case PARASAIKA:{
        variant = table_.at(row).parasAika;
        break;
    }
    case KESKINOPEUS:{
        variant = table_.at(row).keskinopeus;
        break;
    }
    }

    return variant;
}

QHash<int, QByteArray> TableModelYearly::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(VUOSI, "vuosi");
    roles.insert(MATKA, "matka");
    roles.insert(OSALLISTUJALKM, "osallistujalkm");
    roles.insert(HUONOINAIKA, "huonoinAika");
    roles.insert(PARASAIKA, "parasAika");
    roles.insert(KESKINOPEUS, "keskinopeus");

    return roles;
}

bool TableModelYearly::setData(const QModelIndex &index, const QVariant &value, int role)
{
    rowYearly tableRow = table_.at(index.row());
    switch (role) {
    case VUOSI:
        tableRow.vuosi = value.toString();
        break;
    case MATKA:
        tableRow.matka = value.toString();
        break;
    case OSALLISTUJALKM:
        tableRow.osallistujalkm = value.toString();
        break;
    case HUONOINAIKA:
        tableRow.huonoinAika = value.toString();
        break;
    case PARASAIKA:
        tableRow.parasAika = value.toString();
        break;
    case KESKINOPEUS:
        tableRow.keskinopeus = value.toString();
        break;
    }

    return true;
}

void TableModelYearly::resetModel()
{
    beginResetModel();
    table_.clear();
    endResetModel();
}

bool TableModelYearly::updateDataVuosittaisetTilastot(const int &year)
{
    resetModel();

    const int index = table_.size();
    beginInsertRows(QModelIndex(), index, index);

    if(!handler_->vuosittaisetTilastot(table_, year)) {
        resetModel();
        setErrorMessage(handler_->errorMessage());
        endInsertRows();
        return false;
    }

    endInsertRows();
    return true;
}

QString TableModelYearly::errorMessage() const
{
    return errorMessage_;
}

void TableModelYearly::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}
