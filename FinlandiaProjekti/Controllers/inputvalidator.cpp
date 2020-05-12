#include "inputvalidator.h"

InputValidator::InputValidator()
{
}

bool InputValidator::samanMatkanVertailu(const QString &year1, const QString &year2, const QString &names, std::vector<QString> &namesVect)
{
    if(!validateYear(year1)) {
        return false;
    }
    if(!validateYear(year2)) {
        return false;
    }
    if(!validateNames(namesVect,names)) {
        return false;
    }
    return true;
}

bool InputValidator::eriMatkojenVertailu(const QString &year, const QString &names, std::vector<QString> &namesVect)
{

    if(!validateYear(year)) {
        return false;
    }

    if(!validateNames(namesVect,names)) {
        return false;
    }

    return true;
}

bool InputValidator::parhaatJoukkueet(const QString &year)
{
    if(!validateYear(year)) {
        return false;
    }
    return true;
}

bool InputValidator::urheilijanKehitys(const QString &name, const QString &year1, const QString &year2)
{
    if(!validateYear(year1)) {
        return false;
    }

    if(!validateYear(year2)) {
        return false;
    }

    if(year2 < year1) {
        setErrorMessage("Vuoden 2 on oltava pienempi\nkuin vuoden 1");
        return false;
    }

    //then validate the singular name

    if(!isThereAnyNames(name)) {
        return false;
    }

    QString firstName = "";
    QString secondName = "";


    if(!areFirstAndLastLetters(name)) {
        return false;
    }

    if(!buildSeparateNames(name, firstName, secondName)) {
        return false;
    }

    if(!isaNameEmpty(firstName, secondName)) {
        return false;
    }

    if(!isOnlyFirstLetterCapitalized(firstName)) {
        return false;
    }

    if(!isOnlyFirstLetterCapitalized(secondName)) {
        return false;
    }

    return true;
}

bool InputValidator::validateYear(const QString &year)
{

    QString::size_type length;

    length = year.size();

    if(length == 0) {
        setErrorMessage("Anna vuosiluku!");
        return false;
    }

    if (length != 4) {
        setErrorMessage("Vuosiluvussa on \noltava 4 numeroa");
        return false;
    }

    bool ok;
    int convertedYear = year.toInt(&ok, 10);

    if (!ok) {
        setErrorMessage("Vuosiluvun on \noltava luku");
        return false;
    }
    if (convertedYear < 1974) {
        setErrorMessage("Ensimmäinen Finlandia\nhiihdettiin vasta vuonna 1974\n");
        return false;
    }
    if (convertedYear > 2099) {
        setErrorMessage("Kokeilehan vuotta\ntältä vuosisadalta");
        return false;
    }

    return true;
}

bool InputValidator::validateNames(std::vector<QString> &namesVect, const QString namesStr)
{    
    if(!isThereAnyNames(namesStr)) {
        namesVect.clear();
        return false;
    }

    if(!isThereAnyUmlauts(namesStr)) {
        namesVect.clear();
        return false;
    }

    if(!parseStringsSeparatedByComma(namesStr, namesVect)) {
        namesVect.clear();
        return false;
    }

    QString firstName;
    QString secondName;

    for (QString name : namesVect) {

        firstName = "";
        secondName = "";

        if(!areFirstAndLastLetters(name)) {
            namesVect.clear();
            return false;
        }

        if(!buildSeparateNames(name, firstName, secondName)) {
            namesVect.clear();
            return false;
        }

        if(!isaNameEmpty(firstName, secondName)) {
            namesVect.clear();
            return false;
        }

        if(!isOnlyFirstLetterCapitalized(firstName)) {
            namesVect.clear();
            return false;
        }

        if(!isOnlyFirstLetterCapitalized(secondName)) {
            namesVect.clear();
            return false;
        }
    }

    return true;
}

QString InputValidator::errorMessage() const
{
    return errorMessage_;
}

void InputValidator::setErrorMessage(const QString &errorMessage)
{
    errorMessage_ = errorMessage;
}

bool InputValidator::isThereAnyNames(const QString namesStr)
{

    if(namesStr.size() == 0) {
        setErrorMessage("Syötä nimi");
        return false;
    }
    return true;
}

bool InputValidator::parseStringsSeparatedByComma(const QString namesStr, std::vector<QString> &namesVect)
{
    QString name = "";
    bool betweenCommaAndFirstLetter = false;

    for (QChar c : namesStr) {
        if (betweenCommaAndFirstLetter && c!= ",") {
            if (!c.isSpace()) {
                name += c;
                betweenCommaAndFirstLetter = false;
            }
        }
        else {
            if (c == ",") {
                if (name.size() == 0) {
                    setErrorMessage("Syötit tyhjän nimen");
                    return false;
                }
                betweenCommaAndFirstLetter = true;
                namesVect.push_back(name);
                name = "";
            }
            else {
                name += c;
            }
        }
    }
    namesVect.push_back(name);
    return true;
}

bool InputValidator::buildSeparateNames(const QString &name, QString &firstName, QString &secondName)
{
    int spaceCounter = 0;
    bool firstNameFinished = false;

    for (QChar c : name) {

        // check for too much whitespace
        if (c.isSpace()) {
            spaceCounter += 1;
            if (spaceCounter != 1) {
                setErrorMessage("Syötä vain etu- ja sukunimi:\n'" + name +"'");
                return false;
            }
            firstNameFinished = true;
        }
        // check if there is other characters than letters
        else {
            if (!c.isLetter()) {
                setErrorMessage("Nimessä sallitaan vain kirjaimia:\n'" + name +"'");
                //return false;
            }
            if (firstNameFinished) {
                secondName += c;
            }
            else {
                firstName += c;
            }
        }
    }
    return true;
}

bool InputValidator::isaNameEmpty(QString firstName, QString secondName)
{
    if (firstName.size() == 0) {
        setErrorMessage("Anna sekä etu- että sukunimi:\n' _ " + secondName +"'");
        return false;
    }
    if(secondName.size() == 0) {
        setErrorMessage("Anna sekä etu- että sukunimi:\n'" + firstName +" _ '");
        return false;
    }
    return true;
}

bool InputValidator::isOnlyFirstLetterCapitalized(QString name)
{
    for (int i = 0; i<name.size(); i++) {
        if (i == 0) {
            if (name[i].isLower()) {
                setErrorMessage("Nimen on alettava isolla\nalkukirjaimella:\n'" + name +"'");
                return false;
            }
        }
        else {
            if (name[i].isUpper()) {
                setErrorMessage("Vain alkukirjain saa olla isolla:\n'" + name +"'");
                name.clear();
                //return false;
            }
        }
    }
    return true;
}

bool InputValidator::areFirstAndLastLetters(const QString &name)
{
    if (!name[0].isLetter()) {
        setErrorMessage("Nimen on alettava kirjaimella:\n'" + name +"'");
        return false;
    }
    int size = name.size();
    if (!name[size-1].isLetter()) {
        setErrorMessage("Nimen on loputtava kirjaimeen:\n'" + name +"'");
        return false;
    }
    return true;
}

bool InputValidator::isThereAnyUmlauts(const QString &names)
{
    for (auto c : names) {
        if (c == "ä" || c == "Ä" || c == "ö" || c == "Ö") {
            setErrorMessage("Syötteessä ei saa olla ääkkösiä");
            return false;
        }
        else {
            return true;
        }
    }
    return true;
}
