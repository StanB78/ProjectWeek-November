# Niet-zo-single-feestje — Fase 2: Realiseren

Dit is een **digitaal prototype van een slimme hartketting** voor het Valentijnsfeest van Poppodium 013 (hackathon ROC Nijmegen). Gebouwd met een **ESP32** en bedoeld voor simulatie in **Wokwi**.

> Dit is een uitgewerkte **basisversie** van de realisatiefase. De opdracht laat de functionaliteit vrij; het team moet dit ontwerp nog afstemmen met de opdrachtgever/docent en zelf testen in Wokwi. Er is geen toestemming van de opdrachtgever, uitgevoerde Wokwi-test of individuele bijdrage verzonnen.

## Wat kan de ketting?

1. De bezoeker drukt op **STATUS** om te wisselen: **single (groen)** → **ingewikkeld (geel)** → **bezet (rood)** → terug naar single.
2. De bezoeker drukt op **AANDACHT** voor **drie korte lichtflitsen met geluid**.
3. Daarna wordt automatisch de gekozen relatiestatus weer zichtbaar.
4. De **Serial Monitor** toont de acties, zodat je het programma kunt uitleggen en fouten makkelijker kunt vinden.

**Afbakening:** de ketting is een simulatie van **één** broche of ketting en heeft **geen Bluetooth-verbinding of contact met andere kettingen**. De aandachtsknop zendt dus *geen* bericht naar een andere persoon. Er worden geen namen, contactgegevens of locatiegegevens verzameld.

## Waarom ESP32?

- Dit prototype kan de GPIO-pinnen, knoppen, leds en buzzer van de ESP32 gebruiken.
- Wokwi is volgens de projectleeswijzer de geschikte simulator voor ESP32.
- De ESP32 biedt later opties voor Bluetooth als het team een vervolgversie wil maken.
- In deze eerste versie is draadloze communicatie bewust niet gebruikt: dat is eenvoudiger en privacyvriendelijker.

## Projectbestanden

| Bestand | Doel |
| --- | --- |
| `sketch.ino` | Volledige ESP32-code (Arduino/C++) |
| `diagram.json` | Onderdelen, pinnen en bedrading in Wokwi |
| `GEBRUIKERSHANDLEIDING.md` | Zo bedien je het prototype |
| `FASE2_WERKBESCHRIJVING.md` | Technische toelichting, implementatie en nog uit te voeren teamwerk |
| `TESTCONTROLE.md` | Controles om het prototype zelf in Wokwi te testen |

## Zo start je in Wokwi

1. Open <https://wokwi.com/projects/new/esp32>.
2. Open `sketch.ino` in dit pakket; kopieer de volledige inhoud naar het tabblad **sketch.ino** van Wokwi.
3. Open `diagram.json` in dit pakket; vervang de inhoud van het tabblad **diagram.json** van Wokwi daarmee.
4. Klik op **Start Simulation**.
5. Het **groene** lampje hoort aan te zijn. Klik op de **blauwe STATUS-knop**: geel, daarna rood, daarna groen. Klik op **AANDACHT**: alle drie de lampjes knipperen drie keer en er klinkt geluid.
6. Open de **Serial Monitor** om de logmeldingen te bekijken.

> Bij het aanmaken van een nieuw Wokwi-project kan de indeling van de editor iets verschillen. De twee benodigde bestanden zijn `sketch.ino` en `diagram.json`.

## Aansluitschema

| Component | ESP32 GPIO | Aansluiten |
| --- | --- | --- |
| Groene LED (single) | 18 | GPIO 18 → 220Ω weerstand → anode (+), kathode (-) → GND |
| Gele LED (ingewikkeld) | 19 | GPIO 19 → 220Ω weerstand → anode (+), kathode (-) → GND |
| Rode LED (bezet) | 21 | GPIO 21 → 220Ω weerstand → anode (+), kathode (-) → GND |
| STATUS-knop | 25 | Ene contact → GPIO 25, andere contact → GND (`INPUT_PULLUP`) |
| AANDACHT-knop | 26 | Ene contact → GPIO 26, andere contact → GND (`INPUT_PULLUP`) |
| Buzzer | 23 | Plus (+) → GPIO 23, min (-) → GND |

De ESP32 werkt met **3,3 V GPIO-signalen**. De drie leds krijgen elk een eigen 220Ω-serieweerstand.

## Git gebruiken

De schoolopdracht vraagt ook om een Git-repository. Maak in de projectmap een repository en commit je werk:

```bash
git init
git add .
git commit -m "Fase 2: ESP32 hartketting prototype"
```

Voor het samenvoegen van teamwerk kun je per functie een aparte branch gebruiken en daarna elkaars code reviewen. Leg je eigen commits en teamafspraken daadwerkelijk vast.

## Opdrachtkoppeling

Dit pakket vormt het technische onderdeel van **fase 2 (Realiseren)**: werkende bedoelde programmalogica, een Wokwi-schakeling en gebruiks- en systeemdocumentatie. Het vervangt niet: goedkeuring van het ontwerp, een gedeelde Git-repo met echte teamcommits, een demonstratie in Wokwi, de vier overlegverslagen en de onderdelen van fase 3 en fase 4.
