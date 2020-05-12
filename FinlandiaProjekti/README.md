Tämä projekti on alkujaan harjoitustyö Tampereen yliopiston
kurssille TIE-20200 Ohjelmistojen suunnittelu.

Alkuperäisestä projektista on riisuttu pois tietokannan päivitys, eli
Python-skripti, joka hakee Finlandiahiihdon sivuilta tilastot paikalliseen
tietokantaan.

Projektista minun (Jari Rauhala) tekemääni on:
- Kokonaisuuden suunnittelu, arkkitehtuuri
- Kontrollerit kokonaisuuessaan
- Taulukkonäkymät ja niiden mallit kokonaisuuessaan
- Kuvaajien näkymiä oli vähän laitettu alulle, mutta 90% niistä on
  minun tekemää
- Datahandler-luokka SQL-kyselyitä lukuunottamatta
    (Luokka oli alunperin Miro Miettisen tekemä, mutta refaktoroin sen)
- prototyypit

Eli mitä on muiden tekemää
(- Python-skripti)
- SQL-kyselyt
- GraphViewDevelopmentin alustus
- GraphModel::timeToHour -funktio

Yhdessä tehtyä
- suunnittelu
- dokumentointi

Tekijät:
Juho Hulkko - juho.hulkko@tuni.fi
Markus Kylänpää - markus.kylanpaa@tuni.fi
Miro Miettinen - miro.miettinen@tuni.fi
Jari Rauhala - jari.rauhala@tuni.fi

Ryhmä:
Parmesan-kuorrutettu-sieni-tomaattirisotto

## Ohjelman kuvaus

(Projektityössä suunnitellaan ja toteutetaan rajapinta Finlandia-hiihdon tulosarkistoon. )
Tämän lisäksi suunnitellaan ja toteutetaan ohjelma, joka järjestelee, vertailee ja esittää tuloksia graafisesti.
Tarkempi kuvaus löytyy tiedostosta suunnitteludokumentti_loppu.pdf

Linkki tulosarkistoon: https://www.finlandiahiihto.fi/Tulokset/Tulosarkisto
