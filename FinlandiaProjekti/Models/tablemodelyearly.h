#ifndef TABLEMODELYEARLY_H
#define TABLEMODELYEARLY_H

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

class TableModelYearly : public QAbstractTableModel
{
    Q_OBJECT

public:

    enum RoleName {
        VUOSI = 0,
        MATKA = 1,
        OSALLISTUJALKM = 2,
        HUONOINAIKA = 3,
        PARASAIKA = 4,
        KESKINOPEUS = 5,
    };

    explicit TableModelYearly(std::shared_ptr<DataHandler> handler,
                                   QObject *parent = nullptr);

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    // calls for datahandler
    bool updateDataVuosittaisetTilastot(const int &year);

    // Remove all data:
    void resetModel();

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

protected:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

private:
    QList<rowYearly> table_;
    std::shared_ptr<DataHandler> handler_;
    QString errorMessage_ = "";

};

#endif // TABLEMODELYEARLY_H
