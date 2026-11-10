/*
  Niet-zo-single-feestje | ESP32-hartketting
  Fase 2: Realiseren - Hackathon Software Developer

  Werking:
  - GROEN  = single
  - GEEL   = het is ingewikkeld
  - ROOD   = bezet
  - Knop STATUS wisselt tussen deze drie statussen.
  - Knop AANDACHT laat alle lampjes drie keer knipperen
    met een kort geluidje. Hierna komt de gekozen status terug.

  Dit prototype communiceert NIET met andere kettingen.
  Er worden GEEN persoonsgegevens opgeslagen of verzonden.
*/

#include <Arduino.h>

// Aansluitingen (ESP32 GPIO-nummers)
constexpr uint8_t LED_GROEN = 18;
constexpr uint8_t LED_GEEL = 19;
constexpr uint8_t LED_ROOD = 21;
constexpr uint8_t KNOP_STATUS = 25;
constexpr uint8_t KNOP_AANDACHT = 26;
constexpr uint8_t BUZZER = 23;

constexpr unsigned long DEBOUNCE_MS = 40;
constexpr unsigned long KNIPPER_INTERVAL_MS = 180;
constexpr uint8_t AANTAL_ANIMATIE_FASEN = 6; // 3x aan en 3x uit

enum RelatieStatus : uint8_t {
  SINGLE = 0,
  INGEWIKKELD = 1,
  BEZET = 2
};

// Houdt bij of een druk op een knop echt is (geen contactdender).
struct Knop {
  uint8_t pin;
  int vorigeMeting = HIGH;
  int stabieleStand = HIGH;
  unsigned long laatsteWijzigingMs = 0;
};

Knop statusKnop = {KNOP_STATUS};
Knop aandachtKnop = {KNOP_AANDACHT};

RelatieStatus gekozenStatus = SINGLE;
bool animatieActief = false;
uint8_t animatieFase = 0;
unsigned long laatsteAnimatieStapMs = 0;

// Geeft true terug precies wanneer de knop stabiel is ingedrukt.
bool isNetIngedrukt(Knop &knop, unsigned long nu) {
  const int meting = digitalRead(knop.pin);

  if (meting != knop.vorigeMeting) {
    knop.vorigeMeting = meting;
    knop.laatsteWijzigingMs = nu;
  }

  if ((nu - knop.laatsteWijzigingMs) >= DEBOUNCE_MS &&
      meting != knop.stabieleStand) {
    knop.stabieleStand = meting;
    return meting == LOW;
  }

  return false;
}

// Zet de LEDs op de gekozen relatie-status.
void toonStatus() {
  digitalWrite(LED_GROEN, gekozenStatus == SINGLE ? HIGH : LOW);
  digitalWrite(LED_GEEL, gekozenStatus == INGEWIKKELD ? HIGH : LOW);
  digitalWrite(LED_ROOD, gekozenStatus == BEZET ? HIGH : LOW);
}

void printStatus() {
  Serial.print("Gekozen status: ");
  switch (gekozenStatus) {
    case SINGLE: Serial.println("SINGLE (groen)"); break;
    case INGEWIKKELD: Serial.println("INGEWIKKELD (geel)"); break;
    case BEZET: Serial.println("BEZET (rood)"); break;
  }
}

// Statusknop gaat in een rondje: single -> ingewikkeld -> bezet.
void volgendeStatus() {
  gekozenStatus = static_cast<RelatieStatus>((gekozenStatus + 1) % 3);
  if (!animatieActief) {
    toonStatus();
  }
  printStatus();
}

// Oneven fasen zijn uit, even fasen aan (0, 2, 4).
void toonAnimatieFase(uint8_t fase) {
  const bool lichtAan = (fase % 2 == 0);
  digitalWrite(LED_GROEN, lichtAan ? HIGH : LOW);
  digitalWrite(LED_GEEL, lichtAan ? HIGH : LOW);
  digitalWrite(LED_ROOD, lichtAan ? HIGH : LOW);

  if (lichtAan) {
    tone(BUZZER, 740 + (fase * 100));
  } else {
    noTone(BUZZER);
  }
}

void startAandacht(unsigned long nu) {
  if (animatieActief) {
    return; // Geen dubbele animaties tegelijk.
  }
  animatieActief = true;
  animatieFase = 0;
  laatsteAnimatieStapMs = nu;
  toonAnimatieFase(animatieFase);
  Serial.println("Aandachtssignaal gestart!");
}

// Niet-blokkerende animatie: de ESP32 blijft knoppen lezen.
void werkAnimatieBij(unsigned long nu) {
  if (!animatieActief ||
      (nu - laatsteAnimatieStapMs) < KNIPPER_INTERVAL_MS) {
    return;
  }

  laatsteAnimatieStapMs = nu;
  animatieFase++;

  if (animatieFase >= AANTAL_ANIMATIE_FASEN) {
    animatieActief = false;
    noTone(BUZZER);
    toonStatus();
    Serial.println("Aandachtssignaal klaar; status hersteld.");
    return;
  }

  toonAnimatieFase(animatieFase);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_GROEN, OUTPUT);
  pinMode(LED_GEEL, OUTPUT);
  pinMode(LED_ROOD, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Interne pull-up: losgelaten = HIGH, ingedrukt = LOW.
  pinMode(KNOP_STATUS, INPUT_PULLUP);
  pinMode(KNOP_AANDACHT, INPUT_PULLUP);

  noTone(BUZZER);
  toonStatus();
  Serial.println("Niet-zo-single hartketting gestart!");
  Serial.println("STATUS-knop: wissel relatiestatus.");
  Serial.println("AANDACHT-knop: licht- en geluidssignaal.");
  printStatus();
}

void loop() {
  const unsigned long nu = millis();

  if (isNetIngedrukt(statusKnop, nu)) {
    volgendeStatus();
  }

  if (isNetIngedrukt(aandachtKnop, nu)) {
    startAandacht(nu);
  }

  werkAnimatieBij(nu);
}
