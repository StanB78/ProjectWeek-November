# Gebruikershandleiding — digitale hartketting

## Starten

1. Open de bestanden `sketch.ino` en `diagram.json` in een nieuw ESP32-project op Wokwi.
2. Klik op **Start Simulation**.
3. De groene LED gaat aan: de bezoeker staat op **single**.

## Bediening

| Actie | Resultaat |
| --- | --- |
| 1x STATUS indrukken | Gele LED: **het is ingewikkeld** |
| 2x STATUS indrukken | Rode LED: **bezet** |
| 3x STATUS indrukken | Groene LED: **single** |
| AANDACHT indrukken | Alle LEDs knipperen drie keer met een pieptoon |
| Aandachtssignaal is klaar | De laatstgekozen relatiestatus wordt opnieuw getoond |

Een knopdruk moet ongeveer 40 ms ingedrukt blijven om te registreren. Knoppen zijn met `INPUT_PULLUP` aangesloten.

## Betekenis van de LEDs

- **Groen:** ik ben single.
- **Geel:** mijn relatiestatus is ingewikkeld.
- **Rood:** ik ben bezet.

De aandachtknop geeft alleen een **lokaal licht- en geluidssignaal**. Hij maakt niet automatisch contact met iemand anders.

## Veelvoorkomende problemen

- **Geen LED zichtbaar:** controleer of simulatie loopt, of de bedrading bij GPIO 18/19/21 klopt en of de kathodes naar GND gaan.
- **Knop doet niets:** controleer of de knop via GPIO 25/26 en GND is aangesloten. Klik kort maar niet te vluchtig.
- **Geen geluid:** controleer de Wokwi-buzzer en het geluidsniveau van de browser/computer.
- **Foutmelding in de code:** controleer of de volledige inhoud van `sketch.ino` is geplakt in een ESP32-Arduino-project.
