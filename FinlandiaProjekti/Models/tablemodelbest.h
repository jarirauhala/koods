#ifndef TABLEMODELBEST_H
#define TABLEMODELBEST_H

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

class TableModelBest : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum RoleName {
        SIJA = 0,
        JOUKKUE = 1,
        AIKAYHTEENSA = 2
    };

    explicit TableModelBest(std::shared_ptr<DataHandler> handler,
                            QObject *parent = nullptr);


    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    // Remove all data:
    void resetModel();

    // calls for datahandler
    bool updateDataParhaatJoukkueet(const int &year, const QString &travel);

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

protected:
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QHash<int,QByteArray> roleNames() const override;

private:
    QList<rowBest> table_;
    std::shared_ptr<DataHandler> handler_;

    QString errorMessage_ = "";

};

#endif // TABLEMODELBEST_H
