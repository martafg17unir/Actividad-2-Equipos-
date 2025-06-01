#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// ----- PINES -----
#define DHTPIN 2
#define DHTTYPE DHT22

#define LDR_PIN A0
#define MQ2_PIN A1

#define DATA_PIN 3
#define CLOCK_PIN 4
#define LATCH_PIN 5

#define SERVO_COOL_PIN 11
#define SERVO_HEAT_PIN 12

#define HUMID_PIN 6
#define DEHUMID_PIN 7

DHT dht(DHTPIN, DHTTYPE);
Servo servoCool;
Servo servoHeat;

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Variables
byte leds = 0;
int numLEDs = 0;

float tempAnterior = 0;
String estado = "Reposo";
unsigned long tiempoInicio = 0;
unsigned long tiempoEnfriando = 0;
unsigned long tiempoCalentando = 0;
unsigned long tiempoHumidificando = 0;
unsigned long tiempoDeshumidificando = 0;

unsigned long ultimoCambioPantalla = 0;
bool mostrarPantallaAlterna = false;

bool humidificadorActivo = false;
bool deshumidificadorActivo = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(20, 4);
  lcd.backlight();

  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  pinMode(HUMID_PIN, OUTPUT);
  pinMode(DEHUMID_PIN, OUTPUT);

  servoCool.attach(SERVO_COOL_PIN);
  servoHeat.attach(SERVO_HEAT_PIN);

  tiempoInicio = millis();
}

void loop() {
  // ---- LECTURAS ----
  tempAnterior = tempAnterior == 0 ? dht.readTemperature() : tempAnterior;
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int luz = analogRead(LDR_PIN);
  int gas = analogRead(MQ2_PIN);

  // ---- ESTADO TEMP ----
  String estadoActual = "Reposo";
  if (temp > 28) {
    servoCool.write(90);
    servoHeat.write(0);
    estadoActual = "Enfriando";
  } else if (temp < 22) {
    servoHeat.write(90);
    servoCool.write(0);
    estadoActual = "Calentando";
  } else {
    servoCool.write(0);
    servoHeat.write(0);
  }

  // ---- CONTROL HUMEDAD ----
  humidificadorActivo = false;
  deshumidificadorActivo = false;

  if (hum < 75) {
    digitalWrite(HUMID_PIN, HIGH);
    digitalWrite(DEHUMID_PIN, LOW);
    humidificadorActivo = true;
  } else if (hum > 85) {
    digitalWrite(HUMID_PIN, LOW);
    digitalWrite(DEHUMID_PIN, HIGH);
    deshumidificadorActivo = true;
  } else {
    digitalWrite(HUMID_PIN, LOW);
    digitalWrite(DEHUMID_PIN, LOW);
  }

  // ---- TIEMPO Y CONSUMO ----
  unsigned long ahora = millis();
  unsigned long duracion = ahora - tiempoInicio;

  if (estadoActual == "Enfriando") tiempoEnfriando += duracion;
  else if (estadoActual == "Calentando") tiempoCalentando += duracion;

  if (humidificadorActivo) tiempoHumidificando += duracion;
  if (deshumidificadorActivo) tiempoDeshumidificando += duracion;

  tiempoInicio = ahora;
  estado = estadoActual;

  // ---- CONTROL ILUMINACIÓN ----
  numLEDs = map(luz, 1023, 0, 8, 0);
  leds = 0;
  for (int i = 0; i < numLEDs; i++) bitSet(leds, i);

  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, leds);
  digitalWrite(LATCH_PIN, HIGH);

  // ---- NIVEL DE GAS ----
  String nivelGas = gas > 700 ? "Alto" : gas > 400 ? "Medio" : "Bajo";

  // ---- CONSUMO TOTAL ----
  float consumoWh = 0;
  consumoWh += (tiempoEnfriando / 1000.0 / 3600.0) * 5.0;
  consumoWh += (tiempoCalentando / 1000.0 / 3600.0) * 5.0;
  consumoWh += (tiempoHumidificando / 1000.0 / 3600.0) * 3.0;
  consumoWh += (tiempoDeshumidificando / 1000.0 / 3600.0) * 4.0;
  consumoWh += ((numLEDs * duracion) / 1000.0 / 3600.0) * 0.1;

  // ---- CAMBIO DE PANTALLA ----
  if (millis() - ultimoCambioPantalla > 4000) {
    mostrarPantallaAlterna = !mostrarPantallaAlterna;
    ultimoCambioPantalla = millis();
  }

  // ---- LCD ----
  lcd.clear();
  delay(10);

  if (!mostrarPantallaAlterna) {
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(tempAnterior, 1);
    lcd.print("=>");
    lcd.print(temp, 1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Estado: ");
    lcd.print(estado);
    lcd.print("       ");



    lcd.setCursor(0, 3);
    lcd.print("Gas:");
    lcd.print(nivelGas);
    lcd.print(" E:");
    if (consumoWh < 0.01) {
      lcd.print(consumoWh * 1000, 1);
      lcd.print("mWh");
    } else {
      lcd.print(consumoWh, 2);
      lcd.print("Wh ");
    }

  } else {

    lcd.setCursor(0, 1);
    lcd.print("LDR: ");
    lcd.print(analogRead(LDR_PIN));
    lcd.print("       ");

    lcd.setCursor(0, 2);
    lcd.print("LEDs activos: ");
    lcd.print(numLEDs);
    lcd.print("     ");
  
    lcd.setCursor(0, 2);
    lcd.print("Hum: ");
    lcd.print(hum, 0);
    lcd.print("% ");

    lcd.setCursor(0, 3);
    lcd.print("H:");
    lcd.print(humidificadorActivo ? "ON " : "OFF");
    lcd.print(" D:");
    lcd.print(deshumidificadorActivo ? "ON" : "OFF");
  }

  if (abs(temp - tempAnterior) >= 0.1) {
    tempAnterior = temp;
  }

  delay(2000);
}
