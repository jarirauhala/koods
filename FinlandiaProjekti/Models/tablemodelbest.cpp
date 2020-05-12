#include "tablemodelbest.h"


TableModelBest::TableModelBest(std::shared_ptr<DataHandler> handler, QObject *parent)
    : QAbstractTableModel(parent),
      handler_(handler)
{
}

int TableModelBest::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return table_.size();
}

int TableModelBest::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return roleNames().size();
}

QVariant TableModelBest::data(const QModelIndex &index, int role) const
{
    QVariant variant;
    const int row = index.row();
    const int column = role;

    switch (column) {
    case SIJA:{
        variant = table_.at(row).sija;
        break;
    }
    case JOUKKUE:{
        variant = table_.at(row).joukkue;
        break;
    }
    case AIKAYHTEENSA:{
        variant = table_.at(row).aikaYhteensa;
        break;
    }
    }

    return variant;
}

QHash<int, QByteArray> TableModelBest::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(SIJA, "sija");
    roles.insert(JOUKKUE, "joukkue");
    roles.insert(AIKAYHTEENSA, "aikayhteensa");

    return roles;
}

bool TableModelBest::setData(const QModelIndex &index, const QVariant &value, int role)
{
    rowBest tableRow = table_.at(index.row());
    switch (role) {
    case SIJA:
        tableRow.sija = value.toString();
        break;
    case JOUKKUE:
        tableRow.joukkue = value.toString();
        break;
    case AIKAYHTEENSA:
        tableRow.aikaYhteensa = value.toString();
        break;
    }

    return true;
}

void TableModelBest::resetModel()
{
    beginResetModel();
    table_.clear();
    endResetModel();
}

bool TableModelBest::updateDataParhaatJoukkueet(const int &year, const QString &travel)
{
    resetModel();

    const int index = table_.size();
    beginInsertRows(QModelIndex(), index, index);

    if(!handler_->parhaatJoukkueet(table_, year, travel)) {
        resetModel();
        setErrorMessage(handler_->errorMessage());
        endInsertRows();
        return false;
    }

    endInsertRows();
    return true;
}

QString TableModelBest::errorMessage() const
{
    return errorMessage_;
}

void TableModelBest::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}


