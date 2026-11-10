# Fase 2 | Realiseren — werkbeschrijving

## 1. Doel

Een hartketting of broche voor bezoekers van het Valentijnsfeest van Poppodium 013 digitaal laten werken. De bezoeker kan zijn/haar relatiestatus zichtbaar maken en met een knop een kort aandachtssignaal geven.

## 2. Gebruikte techniek

- **Microcontroller:** ESP32 DevKit V1.
- **Simulator:** Wokwi.
- **Programmeertaal:** Arduino C++ (`sketch.ino`).
- **Versiebeheer:** Git (zelf aanmaken en gebruiken met het projectteam).
- **Onderdelen:** 3 LEDs (groen, geel, rood), 3 weerstanden van 220 ohm, 2 drukknoppen, 1 buzzer.

## 3. Gerealiseerde functionaliteit in de aangeleverde code

**Functie A — Relatiestatus instellen**

- Bij het opstarten is de status SINGLE: groen brandt.
- Bij iedere duidelijke druk op de STATUS-knop gaat het systeem een status verder.
- De overige status-LEDs gaan uit, zodat normaal maar één relatiestatus zichtbaar is.
- De gekozen status wordt in de Serial Monitor getoond.

**Functie B — Aandachtssignaal**

- Bij het indrukken van AANDACHT starten 3 lichtflitsen met een geluidssignaal.
- De signalering is niet-blokkerend met `millis()` in plaats van lange `delay()`-aanroepen.
- Na afloop keert de gekozen relatiestatus terug.
- Een tweede druk op AANDACHT tijdens dezelfde animatie start geen tweede animatie.

**Functie C — Betrouwbare knoppen**

- De knoppen gebruiken `INPUT_PULLUP`: normaal HIGH, ingedrukt LOW.
- De software filtert contactdender via een stabiele wachttijd van 40 milliseconden.
- Eén druk leidt hierdoor in de bedoelde werking tot maar één statuswissel.

## 4. Programmastructuur

- `setup()`: pinnen instellen, Serial Monitor starten en beginstatus tonen.
- `loop()`: beide knoppen uitlezen en de animatie bijwerken.
- `isNetIngedrukt()`: detectie van stabiel drukken.
- `volgendeStatus()` en `toonStatus()`: de juiste LED kiezen.
- `startAandacht()`, `toonAnimatieFase()` en `werkAnimatieBij()`: drie flitsen en een geluidssignaal zonder het programma te blokkeren.

## 5. Technische keuzes

- Voor een **ESP32** is gekozen om de opdracht in **Wokwi** te kunnen simuleren en later uit te breiden met bijvoorbeeld BLE.
- Drie aparte LEDs maken de drie statussen eenvoudig te begrijpen.
- Knoppen en licht vormen een eenvoudig te demonstreren prototype.
- Er worden geen persoonsgegevens opgeslagen of draadloos verzonden.
- Door kleine functies, duidelijke namen en commentaar blijft de code begrijpelijk en onderhoudbaar.

## 6. Wat moet het team zelf nog doen?

- [ ] Het ontwerp **daadwerkelijk laten goedkeuren** door de docent (als opdrachtgever).
- [ ] Het prototype **daadwerkelijk starten en controleren** in Wokwi.
- [ ] De bestanden in een **eigen Git-repository** zetten.
- [ ] Taken verdelen, eigen commits maken, teamcode reviewen en voortgang op een scrumbord bijhouden.
- [ ] De **tweede overlegbijeenkomst** vastleggen: ontwerpreview, sprintplanning 2, taakverdeling en actiepunten (wie/wat/wanneer).
- [ ] De taken hieronder invullen met de **echte** personen en data:

| Taak | Verantwoordelijke | Afgerond op | Git-commit / bewijs |
| --- | --- | --- | --- |
| ESP32-schakeling opbouwen | _invullen_ | _invullen_ | _invullen_ |
| Statusknop programmeren | _invullen_ | _invullen_ | _invullen_ |
| Aandachtssignaal programmeren | _invullen_ | _invullen_ | _invullen_ |
| Integreren en controleren in Wokwi | _invullen_ | _invullen_ | _invullen_ |
| Code review / documentatie | _invullen_ | _invullen_ | _invullen_ |

## 7. Begrenzing van deze oplevering

Deze documenten en de code zijn voorbereid voor fase 2. Een test in de **echte Wokwi-simulator**, akkoord van de docent en teamwork zijn niet uitgevoerd of geclaimd. In fase 3 zijn daarnaast volgens de projectleeswijzer een integratietest, acceptatietest, testrapport, video en verbetervoorstellen nodig.
