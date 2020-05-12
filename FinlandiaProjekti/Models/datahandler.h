#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "rowstructs.h"
#include <QList>
#include <QString>
#include <QDebug>
#include <stdio.h>
//#include <sqlite3.h>
#include <iostream>
#include <QDir>
#include <string>

#include <QtSql>
#include <QSqlDatabase>



class DataHandler
{
public:
    DataHandler();

    // Tables
    //   travel = "matka"
    // Action: These functions are to define data to be represented as tables
    // i.e. to be used by table models.

    // Return: If the search was succesfull, true. In case of an error a proper error
    // message is written to errorMessage_ and flase is returned.

    // Parameters: They take an empty table to be populated as reference.
    // Other paremeters are search keys defined by user and validated by InputValidator.
    // timeMin and timeMax are time in hours with three-digit-percision
    // year is [1974, 2099]
    // A name in names vector consists of first and second name, separated by a single whitespace,
    // and has no other characters than letters. Both names begin with a capital letter and have no
    // other capital letters.
    bool haeAikojenMukaan( QList<rowAll> &table, const int &year,
                           const QString &timeMin, const QString &timeMax);

    bool vertailu(QList<rowComparison> &table, const QString &travel,
                  const int &year,const std::vector<QString> &names);

    bool vuosittaisetTilastot(QList<rowYearly> &table, const int &year);

    bool tuloksetAakkosittain(QList<rowAll> &table, const int &year);

    bool parhaatJoukkueet(QList<rowBest> &table, const int &year,
                          const QString &travel);

    // kuvaajia?
    bool urheilijanKehitys(QList<rowDevelopment> &table, const QString &name, const QString &year1,
                           const QString &year2, const QString &travel);

    bool keskinopeusSijoituksenMukaan(QList<rowAvgTime> &table, const QString &travel,
                                      const QString &year1, const QString &year2,
                                      const QString &rankMax);

    bool parhaanSijoitus(QList<rowRankBest> &table, const QString &gender,
                         const QString &year1, const QString &year2,
                         const QString &travel);

    bool jakaumaMaittain(QList<rowDistribution> &table, const QString &year1,
                         const QString &year2);

    // keskinopeusSijoituksenMukaan();
    // parhaanSijoitus();
    // jakaumaMaittain();

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

private:

    // for testing purposes until proper functionality
    QList<rowAll> testTableAll_;

    QList<rowComparison> testTableComparison_;

    QList<rowBest> testTableBest_;

    QList<rowYearly> testTableYearly_;

    QList<rowDevelopment> testTableDevelopment_;

    void populateTestTables();

    QString errorMessage_ = "Error in data handling";

    QSqlDatabase db_;

    //sqlite3* DB;

    QString replaceFirstOccurrence(const QString time,
                                   const std::string &toReplace,
                                   const std::string &replaceWith);

    // appends empty rows to table, between year1 and year2
    // leaves years already appended untouched
    void appendEmptyRows(QList<rowAvgTime> &table, const QString &year1,
                         const QString &year2);
};

#endif // DATAHANDLER_H
