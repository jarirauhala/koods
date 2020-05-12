#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <QString>
#include <vector>
#include <QDebug>

class InputValidator
{
public:
    InputValidator();

    // names will be parsed from input QString names and appended to namesVect
    // for years validateYear is called
    // if all parameters are valid, true is returned
    // if some is incorrect, errorMessage is written accordingly  and
    // false returned

    bool samanMatkanVertailu(const QString &year1,
                             const QString &year2, const QString &names,
                             std::vector<QString> &namesVect);
    bool eriMatkojenVertailu(const QString &year, const QString &names,
                             std::vector<QString> &namesVect);
    bool parhaatJoukkueet(const QString &year);
    bool urheilijanKehitys(const QString &name, const QString &year1,
                           const QString &year2);

    // checks if year is an ineger between 1974-2100
    bool validateYear(const QString &year);
    // parses names from QString separated by commas and appends them to vect
    // every name has to have a forename and a surname
    bool validateNames(std::vector<QString> &namesVect, const QString namesStr);

    QString errorMessage() const;
    void setErrorMessage(const QString &errorMessage);

    // checks the size of namesString, if empty updates errorMessage
    // and returns false
    bool isThereAnyNames(const QString namesStr);

    // separates words indicated by a comma from namesStr and appends to namesVect
    bool parseStringsSeparatedByComma(const QString namesStr, std::vector<QString> &namesVect);

    // separates first and second name from name, returns false and updates errorMessage if
    // there is too much whitespace of unwanted characters
    bool buildSeparateNames(const QString &name, QString &firstName, QString &secondName);

    // checks if either of parameters is of size 0
    // if so, returns false and updates errorMessage accordingly
    bool isaNameEmpty(QString firstName, QString secondName);

    bool isOnlyFirstLetterCapitalized(QString name);

    // checks the first and last letter of the given parameter
    // if they are not letters, returns false and updates errorMessage
    bool areFirstAndLastLetters(const QString &name);

    // checks if there are any ä,Ä,ö or Ö in given string
    // if are, false is returned
    bool isThereAnyUmlauts(const QString &names);

private:
    QString errorMessage_ = "";

};

#endif // INPUTVALIDATOR_H
