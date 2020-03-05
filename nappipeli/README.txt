Tämä on Jari Rauhalan vuonna 2020 tekemä Nappipeli. Se
on tehty Vincitin koodarijahdin "Painikepeli" 
-ennakkotehtäväksi ja täyttää siinä annetut vaatimukset. 
Latasin GitHubiin node-modules kansiota lukuunottamatta 
kaikki pelin tiedostot. Peli pyörii osoitteessa:
https://nappipeli4.herokuapp.com/

Projekti koostuu palvelimesta sekä itse pelistä. Palvelin
on toteutettu Node.js:llä ja Expressillä, ja on, kuten 
sanottua, toiminnassa Herokun palvelimella. Se vastaa
edellä annettuun url-osoitteeseen tehtyyn pyyntöön
avaamalla React-sovelluksen. Palvelimen toteutus löytyy
GitHubista server.js -tiedostosta ja React-sovelluksen 
toteutus lähinnä src/App.js -tiedostosta.

Play-nappia painettaessa sovellus lähettää palvelimelle
XMLHttp-pyynnön salaiseen /secretpathforcounterfetching 
-polkuun. Palvelin pitää yllä laskuria, ja palauttaa tämän 
laskurin arvon kyseisen polun kautta. Sovellus tulkitsee, 
saako pelaaja lisää pisteitä laskurin arvon perusteella ja
päivittää pistelaskuria.

Pelaajaan liitetään pelin alkaessa eväste, johon tallentuu
pistemäärä. Koitin saada sen vanhenemaan vasta vuorokauden
kuluttua, mutta se mitätöityy aina selaimen suljettaessa.
En löytänyt ratkaisua sitten millään. Se kestää toki sivun 
uudelleen lataamisenja uuteen ikkunaan ja välilehteen 
avaamisen.

Jos https://nappipeli4.herokuapp.com/ ei jostain syystä
toimi, voitte kysyä minulta, että mikä homma, niin voin
koittaa korajta. Tätä kirjoittaessani se ainakin toimi. 
Jos siitä, tai muusta syystä joku haluaa pelata peliä 
lokaalisti, ladatkoon hän tämän GitHub-kansion tiedostot,
ajakoot komennon npm install asentaakseen node moduulit,
kirjautukoon herokuun, ajakoon komennon heroku local ja
avatkoon selaimellaan sivun http://localhost:5000/