#include "datahandler.h"

// if you're using macOS, change the following path to:
//static const char* DATABASE_PATH = "../../../../FinlandiaProjekti/Models/database2.db";

// if using widows, use:
static const char* DATABASE_PATH = "../FinlandiaProjekti/Models/database2.db";

DataHandler::DataHandler() //: DB(nullptr)
{
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(DATABASE_PATH);
}


bool DataHandler::vertailu(QList<rowComparison> &table, const QString &travel, const int &year, const std::vector<QString> &names)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    qDebug() << "datahandlerin saamat nimet:";
    for (auto nimi : names) {
        qDebug () << nimi;
    }

    table.clear();

    QString nameString = "";

    for (std::vector<QString>::size_type i = 0; i < names.size(); ++i) {
        qDebug() << names.at(i);
        if(i != names.size() - 1 ){
            nameString += ("name= '" + names.at(i) + "' OR ");
        } else {
            nameString += ("name= '" + names.at(i)+ "'");
        }
    }


    QString s = "SELECT result,ranking,name,born,nationality "
                "FROM athletes" +
                QString::number(year) +
                " WHERE event = \'" + travel + "\' "
                "AND (" + nameString + ");";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowComparison newRow;

    while (query.next()) {
        queryIsEmpty = false;

        newRow.tulos = query.value(0).toString();
        newRow.sija = query.value(1).toString();
        newRow.nimi = query.value(2).toString();
        newRow.syntymavuosi = query.value(3).toString();
        newRow.kansallisuus = query.value(4).toString();

        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("No results found\n"
                        + travel + ", " + QString::number(year));
        setErrorMessage("Tuloksia ei löytynyt");

        db_.close();
        return false;
    }

    db_.close();
    return true;

}

bool DataHandler::vuosittaisetTilastot(QList<rowYearly> &table, const int &year)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    QString s = "SELECT year,  event, COUNT(event), "
                "MAX(result), MIN(result), ROUND(AVG(result)*60, 2) "
                "FROM athletes" + QString::number(year) +
                " GROUP BY event;";

    qDebug () << s;

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowYearly newRow;

    while (query.next()) {
        queryIsEmpty = false;

        newRow.vuosi = query.value(0).toString();
        newRow.matka = query.value(1).toString();
        newRow.osallistujalkm = query.value(2).toString();
        newRow.huonoinAika = query.value(3).toString();
        newRow.parasAika = query.value(4).toString();
        newRow.keskinopeus = query.value(5).toString();

        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("Tuloksia ei löytynyt");
        db_.close();
        return false;
    }

    db_.close();

    return true;
}

bool DataHandler::tuloksetAakkosittain(QList<rowAll> &table, const int &year)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    QString s = "SELECT * "
                "FROM athletes" +
                QString::number(year) +
                " WHERE ((team IS NOT NULL) AND (team IS NOT ' '))"
                " ORDER BY team;";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowAll newRow;

    while (query.next()) {
        queryIsEmpty = false;
        qDebug()<<"OJ:" << query.value(12).toString();

        newRow.vuosi = query.value(1).toString();
        newRow.matka = query.value(2).toString();
        newRow.tulos = query.value(3).toString();
        newRow.sija = query.value(4).toString();
        newRow.sijaM = query.value(5).toString();
        newRow.sijaN = query.value(6).toString();
        newRow.sukupuoli = query.value(7).toString();
        newRow.nimi = query.value(8).toString();
        newRow.paikkakunta = query.value(9).toString();
        newRow.kansallisuus = query.value(10).toString();
        newRow.syntymavuosi = query.value(11).toString();
        newRow.joukkue = query.value(12).toString();

        table.append(newRow);

    }

    if (queryIsEmpty) {
        setErrorMessage("No results found");
        db_.close();
        return false;
    }

    db_.close();
    return true;
}

bool DataHandler::parhaatJoukkueet(QList<rowBest> &table, const int &year, const QString &travel)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    QString s = "SELECT "
                "ROW_NUMBER () OVER (ORDER BY id) sija, team, "
                "round(avg(result), 4) AS ka "
                "FROM athletes" + QString::number(year) + " "
                "WHERE event='"+ travel + "' "
                "GROUP BY team "
                "ORDER BY ka "
                "LIMIT 10;";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowBest newRow;

    while (query.next()) {
        queryIsEmpty = false;

        newRow.sija = query.value(0).toString();
        newRow.joukkue = query.value(1).toString();
        newRow.aikaYhteensa = query.value(2).toString();

        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("Tuloksia ei löytynyt");
        db_.close();
        return false;
    }

    db_.close();
    return true;
}

bool DataHandler::haeAikojenMukaan(QList<rowAll> &table, const int &year, const QString &timeMin, const QString &timeMax)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    QString s = "SELECT * FROM athletes" +
            QString::number(year) +
            " WHERE result BETWEEN '" + replaceFirstOccurrence(timeMin, ".", ":") +
            "' AND '" + replaceFirstOccurrence(timeMax, ".", ":")  + "';";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowAll newRow;

    while (query.next()) {
        queryIsEmpty = false;

        newRow.vuosi = query.value(1).toString();
        newRow.matka = query.value(2).toString();
        newRow.tulos = query.value(3).toString();
        newRow.sija = query.value(4).toString();
        newRow.sijaM = query.value(5).toString();
        newRow.sijaN = query.value(6).toString();
        newRow.sukupuoli = query.value(7).toString();
        newRow.nimi = query.value(8).toString();
        newRow.paikkakunta = query.value(9).toString();
        newRow.kansallisuus = query.value(10).toString();
        newRow.syntymavuosi = query.value(11).toString();
        newRow.joukkue = query.value(12).toString();

        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("Tuloksia ei löytynyt");
        db_.close();
        return false;
    }

    db_.close();
    return true;
}

bool DataHandler::urheilijanKehitys(QList<rowDevelopment> &table, const QString &name, const QString &year1,
                                    const QString &year2, const QString &travel)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
        return false;
    }

    table.clear();

    QString s = "SELECT year, event, result, name "
                        "FROM athletesAll "
                        "WHERE name= '" + name + "' "
                        "AND year BETWEEN " + year1 +
                        " AND " + year2 +
                        " AND event= '" + travel + "';";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowDevelopment newRow;

    while (query.next()) {
        queryIsEmpty = false;

        newRow.vuosi = query.value(0).toString();
        newRow.matka = query.value(1).toString();
        newRow.tulos = query.value(2).toString();
        newRow.nimi = query.value(3).toString();

        qDebug()<<"Table has:" <<  newRow.vuosi <<
                  newRow.matka <<
                  newRow.tulos <<
                  newRow.nimi;

        table.append(newRow);
    }

    if (queryIsEmpty) {
        qDebug() << "empty query";

        setErrorMessage("Tuloksia ei löytynyt");
        db_.close();
        return false;
    }

    db_.close();
    return true;
}

bool DataHandler::keskinopeusSijoituksenMukaan(QList<rowAvgTime> &table, const QString &travel, const QString &year1, const QString &year2, const QString &rankMax)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    QString s = "SELECT year, AVG(result) FROM athletesAll "
                "WHERE event='" + travel + "' AND "
                "ranking BETWEEN 1 AND " + rankMax + " AND "
                "year BETWEEN " + year1 + " AND " + year2 + " GROUP BY year;";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowAvgTime newRow;

    while (query.next()) {

        queryIsEmpty = false;
        newRow.vuosi = query.value(0).toString();
        newRow.keskinopeus = query.value(1).toString();

        qDebug () << "vuosi:" << newRow.vuosi << "keskinopeus:" << newRow.keskinopeus;


        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("No results found");
        db_.close();
        return false;
    }


    db_.close();
    return true;
}

bool DataHandler::parhaanSijoitus(QList<rowRankBest> &table, const QString &gender, const QString &year1, const QString &year2, const QString &travel)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    QString s = "SELECT year, ranking FROM athletesAll WHERE event='" + travel +
                "' AND ranking" + gender + "= 1 "
                " AND year BETWEEN " + year1 + " AND " + year2 + ";";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowRankBest newRow;

    while (query.next()) {

        queryIsEmpty = false;
        newRow.vuosi = query.value(0).toString();
        newRow.sijoitus = query.value(1).toString();


        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("No results found");
        db_.close();
        return false;
    }

    db_.close();
    return true;
}

bool DataHandler::jakaumaMaittain(QList<rowDistribution> &table, const QString &year1, const QString &year2)
{
    if (!db_.open()) {
        setErrorMessage("Database did not open\nfor some reason");
    }

    table.clear();

    // amount is limited by 15 countries with most participants so that the view looks reasonable
    QString s = "SELECT nationality,  COUNT(nationality) as amount FROM athletesAll"
                " WHERE year BETWEEN " + year1 +" AND " + year2 +
                " GROUP BY nationality ORDER BY amount DESC LIMIT 15;";

    QSqlQuery query;
    query.exec(s);

    bool queryIsEmpty = true;
    rowDistribution newRow;

    while (query.next()) {

        queryIsEmpty = false;
        newRow.maa = query.value(0).toString();
        newRow.lukum = query.value(1).toString();


        table.append(newRow);
    }

    if (queryIsEmpty) {
        setErrorMessage("No results found");
        db_.close();
        return false;
    }

    db_.close();
    return true;
}


void DataHandler::populateTestTables()
{
    // All
    rowAll testRowAll1 = {
        "2019",
        "P50",
        "2:00:00",
        "1",
        "1",
        "",
        "M",
        "Beskrovniy Ivan",
        "Sankt-Petersburg",
        "RU",
        "02",
        "Zelenogorsk"
    };
    rowAll testRowAll2 = {
        "2019",
        "P50",
        "2:10:00",
        "2",
        "2",
        "",
        "M",
        "Dvoskin Aleksei",
        "Sankt-Petersburg",
        "RU",
        "01",
        "Zelenogorsk"
    };
    testTableAll_.append(testRowAll1);
    testTableAll_.append(testRowAll2);

    // Comparison
    rowComparison testRowComparison1 = {
        "1:00:00",
        "1",
        "Vladimir",
        "1995",
        "RU"
    };
    rowComparison testRowComparison2 = {
        "2:00:00",
        "2",
        "Sergei",
        "2000",
        "RU"
    };
    testTableComparison_.append(testRowComparison1);
    testTableComparison_.append(testRowComparison2);

    // Yearly
    rowYearly testRowYearly1 = {
        "2019",
        "P40",
        "150",
        "8:00:00",
        "0:00:10",
        "2:00:02"
    };
    rowYearly testRowYearly2 = {
        "2019",
        "P50",
        "160",
        "7:00:00",
        "0:20:00",
        "2:05:02"
    };
    testTableYearly_.append(testRowYearly1);
    testTableYearly_.append(testRowYearly2);

    // Best
    rowBest testRowBest1 = {
        "1",
        "team1",
        "8:44:41"
    };
    rowBest testRowBest2 = {
        "...",
        "...",
        "..."
    };
    rowBest testRowBest3 = {
        "10",
        "team10",
        "16:52:03"
    };
    testTableBest_.append(testRowBest1);
    testTableBest_.append(testRowBest2);
    testTableBest_.append(testRowBest3);
    // Development
    rowDevelopment testRowDevelopment1 = {
        "2018",
        "P50",
        "7:00:00",
        "Georgi Stroganoff"
    };
    rowDevelopment testRowDevelopment2 = {
        "2019",
        "P50",
        "6:00:00",
        "Georgi Stroganoff"
    };
    testTableDevelopment_.append(testRowDevelopment1);
    testTableDevelopment_.append(testRowDevelopment1);
}

QString DataHandler::replaceFirstOccurrence(const QString time,
    const std::string& toReplace,
    const std::string& replaceWith)
{
    QString sQstr;
    std::string s = time.toStdString();
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) {
        sQstr = QString::fromStdString(s);
        return sQstr;
    }
    s = s.replace(pos, toReplace.length(), replaceWith) + ":00";
    sQstr = QString::fromStdString(s);
    return sQstr;
}

void DataHandler::appendEmptyRows(QList<rowAvgTime> &table, const QString &year1, const QString &year2)
{
    rowAvgTime newEmptyRow;
    newEmptyRow.keskinopeus = "0";

    QList<rowAvgTime> newTable;

    int year = year1.toInt();
    int lastYear = year2.toInt();

    qDebug()<<"int years:" << year << lastYear;


    for (; year != lastYear ; ++year) {

        bool yearAlreadyExcists = false;

        for (rowAvgTime excistingRow : table) {
            if (excistingRow.vuosi == QString::number(year)) {
                yearAlreadyExcists = true;
                newTable.append(excistingRow);
                break;
            }
        }

        if (!yearAlreadyExcists) {
            newEmptyRow.vuosi = QString::number(year);
            newTable.append(newEmptyRow);
        }
    }

    table.clear();
    table = newTable;

    for (rowAvgTime excistingRow : table) {
        qDebug()<<"table has:" << excistingRow.vuosi << excistingRow.keskinopeus;
    }

}

QString DataHandler::errorMessage() const
{
    return errorMessage_;
}

void DataHandler::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}


