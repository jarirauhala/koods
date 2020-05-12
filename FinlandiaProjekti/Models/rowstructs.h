#ifndef ROWSTRUCTS_H
#define ROWSTRUCTS_H

#include <QString>


// a struct is used to hold information of a row of a table
// i.e. the elements of a struct define the columns of a table

// rowAll has all the information available. It is used in
// Hae aikojen mukaan & Tulokset aakkosittain
struct rowAll {
    QString vuosi;
    QString matka;
    QString tulos;
    QString sija;
    QString sijaM;
    QString sijaN;
    QString sukupuoli;
    QString nimi;
    QString paikkakunta;
    QString kansallisuus;
    QString syntymavuosi;
    QString joukkue;
};

// used in comparing views:
// Saman matkan vertailu & Eri matkojen vertailu
struct rowComparison
{
    QString tulos;
    QString sija;
    QString nimi;
    QString syntymavuosi;
    QString kansallisuus;
};

// used in Vuosittaiset tilastot
struct rowYearly
{
    QString vuosi;
    QString matka;
    QString osallistujalkm;
    QString huonoinAika;
    QString parasAika;
    QString keskinopeus;
};

// used in Parhaat joukkueet
struct rowBest
{
    QString sija;
    QString joukkue;
    QString aikaYhteensa;
};
//used in Urheilijan kehitys
struct rowDevelopment
{
    QString vuosi;
    QString matka;
    QString tulos;
    QString nimi;
};

// used in Keskinopeus sijoituksen mukaan
struct rowAvgTime {
    QString keskinopeus;
    QString vuosi;
};

// used in parhaan sijoitus
struct rowRankBest {
    QString sijoitus;
    QString vuosi;
};

// used in jakauma maittain
struct rowDistribution {
    QString maa;
    QString lukum;
};

#endif // ROWSTRUCTS_H
