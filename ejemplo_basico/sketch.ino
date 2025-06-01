#include <LiquidCrystal.h>
#include <DHT.h>
#include <Servo.h>

// -------------------- Pines --------------------
#define DHTPIN 7
#define DHTTYPE DHT22
#define LDR_PIN A0
#define VIENTO_PIN A5  // Potenciómetro
#define SERVO_PIN 6   // Servo motor para viento

// LEDs blancos (luz artificial escalonada)
const int luzPins[] = {8, 9, 10, 6, 13, A1, A2, A3};

// LEDs de estado
#define LED_CALOR A4     // Calefacción
#define LED_FRIO A5      // Refrigeración
#define LED_CONFORT 0    //Temperatura ambiente

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
Servo vientoServo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  vientoServo.attach(SERVO_PIN);

  // LEDs iluminación artificial
  for (int i = 0; i < 8; i++) {
    pinMode(luzPins[i], OUTPUT);
  }

  // LEDs de estado
  pinMode(LED_CALOR, OUTPUT);
  pinMode(LED_FRIO, OUTPUT);
  pinMode(LED_CONFORT, OUTPUT);
}

void loop() {
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  int luz = analogRead(LDR_PIN); // 0–1023
  int vientoRaw = analogRead(VIENTO_PIN); // lectura del potenciómetro
  int vientoGrados = map(vientoRaw, 0, 1023, 0, 180); // escala a 0–180°
  vientoServo.write(vientoGrados);

  // Mostrar por monitor serie
  Serial.print("Temp: "); Serial.print(temperatura);
  Serial.print(" °C | Humedad: "); Serial.print(humedad);
  Serial.print(" % | Luz: "); Serial.print(luz);
  Serial.print(" | Viento: "); Serial.println(vientoGrados);

  // -------------------- CONTROL TEMPERATURA --------------------
  bool calefaccion = false;
  bool refrigeracion = false;

  if (temperatura < 22) {
    calefaccion = true;
  } else if (temperatura > 28) {
    refrigeracion = true;
  }

  digitalWrite(LED_CALOR, calefaccion);
  digitalWrite(LED_FRIO, refrigeracion);

  // -------------------- ILUMINACIÓN ARTIFICIAL --------------------
  int numLedsEncendidos = 0;

  if (luz < 200) {
    numLedsEncendidos = 8;
  } else if (luz < 400) {
    numLedsEncendidos = 6;
  } else if (luz < 600) {
    numLedsEncendidos = 4;
  } else if (luz < 800) {
    numLedsEncendidos = 2;
  } else {
    numLedsEncendidos = 0;
  }

  for (int i = 0; i < 8; i++) {
    digitalWrite(luzPins[i], i < numLedsEncendidos ? HIGH : LOW);
  }

  // -------------------- CONFORT AMBIENTAL --------------------
  bool confort = (temperatura >= 22 && temperatura <= 28) && (luz >= 800);
  digitalWrite(LED_CONFORT, confort);

  // -------------------- LCD DISPLAY --------------------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura, 1);
  lcd.print("C H:");
  lcd.print(humedad, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  if (calefaccion) {
    lcd.print("Calor ");
  } else if (refrigeracion) {
    lcd.print("Frio ");
  } else {
    lcd.print("Estable ");
  }

  lcd.print("V:");
  lcd.print(vientoGrados);
  lcd.print(" ");

  delay(2000);
}
