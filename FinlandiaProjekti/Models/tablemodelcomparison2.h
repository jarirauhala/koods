#ifndef TABLEMODELCOMPARISON2_H
#define TABLEMODELCOMPARISON2_H

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

class TableModelComparison2 : public QAbstractTableModel
{
    Q_OBJECT

public:

    enum RoleName {
        TULOS = 0,
        SIJA = 1,
        NIMI = 2,
        SYNTYMAVUOSI = 3,
        KANSALLISUUS = 4,
    };

    explicit TableModelComparison2(std::shared_ptr<DataHandler> handler,
                                   QObject *parent = nullptr);

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    // calls for datahandler
    bool updateDataVertailu(const QString &travel, const int &year,
                            const std::vector<QString> &names);

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
    QList<rowComparison> table_;
    std::shared_ptr<DataHandler> handler_;
    QString errorMessage_ = "";

};

#endif // TABLEMODELCOMPARISON2_H
