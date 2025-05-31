#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <Servo.h>

// —————— definiciones pines —————————
#define DHT22_PIN    2    // DHT22
#define LDR_PIN      A0   // LDR
#define POT_PIN      A1   // Potenciómetro (calidad aire)

const int DATA_PIN    = 8;   // 74HC595: DS
const int CLOCK_PIN   = 10;   // 74HC595: SHCP
const int LATCH_PIN   = 9;   // 74HC595: STCP

const int SERVO_HEAT_PIN = 5;   // servo calefacción
const int SERVO_COOL_PIN = 6;  // servo refrigeración

// —————— parámetros de control —————————
const float TEMP_SETPOINT     = 25.0;  // °C deseados
const float TEMP_HYSTERESIS   = 2.0;   // zona muerta ±2 °C

const float LIGHT_SETPOINT    = 80.0;  // % de iluminación deseada

// —————— variables globales —————————
dht DHT;
LiquidCrystal_I2C lcd(0x27,16,2);
Servo servoHeat, servoCool;

float hum, temp;
int ldrVal, gasValue;
float voltageLDR, resistanceLDR, lux;

String nivelAire, nivelGas, calidadAire;

int ledLevel = 0;  // escalón actual [0..8]

// —————— setup —————————
void setup(){
  lcd.init();
  lcd.backlight();

  // 74HC595
  pinMode(DATA_PIN,  OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  // servos
  servoHeat.attach(SERVO_HEAT_PIN);
  servoCool.attach(SERVO_COOL_PIN);
  // posición neutra (válvulas cerradas)
  servoHeat.write(90);
  servoCool.write(90);

  // nada más
}

// —————— loop —————————
void loop(){
  // --- 1) lectura sensores ---
  int chk = DHT.read22(DHT22_PIN);
  hum = DHT.humidity;
  temp = DHT.temperature;

  ldrVal = analogRead(LDR_PIN);
  voltageLDR   = ldrVal / 1024.0 * 5.0;
  resistanceLDR= 2000 * voltageLDR / (1 - voltageLDR/5.0);
  const float GAMMA = 0.7, RL10 = 50;
  lux = pow(RL10*1e3*pow(10, GAMMA)/resistanceLDR, 1.0/GAMMA);

  gasValue = analogRead(POT_PIN);

  // --- 2) evaluación calidad de aire (igual que antes) ---
  if ((temp>=15 && temp<=25) && (hum>40 && hum<60))      nivelAire = "Bueno";
  else if ((temp>=5 && temp<=35) && (hum>=30 && hum<=70)) nivelAire = "Normal";
  else                                                    nivelAire = "Malo";

  if (gasValue<=341)        nivelGas = "Bueno";
  else if (gasValue<=681)   nivelGas = "Normal";
  else                      nivelGas = "Malo";

  calidadAire = ((nivelAire=="Malo" || nivelGas=="Malo") ? "Mala Calidad" : "Buena Calidad");

  // --- 3) control de TEMPERATURA con servos ---
  float tMin = TEMP_SETPOINT - TEMP_HYSTERESIS;
  float tMax = TEMP_SETPOINT + TEMP_HYSTERESIS;

  if (temp < tMin) {
    // hace frío → abrir calefacción
    servoHeat.write(0);    // válvula calefacción abierta
    servoCool.write(90);   // válvula frío cerrada
  }
  else if (temp > tMax) {
    // hace calor → abrir refrigeración
    servoCool.write(180);  // válvula frío abierta
    servoHeat.write(90);   // válvula calefacción cerrada
  }
  else {
    // dentro de zona muerta → todo cerrado
    servoHeat.write(90);
    servoCool.write(90);
  }

  // --- 4) control de ILUMINACIÓN con 8 LEDs via 74HC595 ---
  // calculamos % de brillo (0=oscuro,100=muy claro)
  float brilloPct = (voltageLDR / 5.0) * 100.0;

  if (brilloPct < LIGHT_SETPOINT && ledLevel < 8) {
    ledLevel++;
  }
  else if (brilloPct > LIGHT_SETPOINT && ledLevel > 0) {
    ledLevel--;
  }
  updateLEDs(ledLevel);

  // --- 5) presentación en LCD (igual que antes) ---
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:"); lcd.print(temp,1); lcd.print((char)223); lcd.print("C ");
  lcd.print("H:"); lcd.print(hum,0);   lcd.print("%");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Luz:"); lcd.print(lux,0); lcd.print(" lux");
  delay(1500);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Nivel aire:");
  lcd.setCursor(0,1); lcd.print(nivelAire);
  delay(1500);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Nivel gas:");
  lcd.setCursor(0,1); lcd.print(nivelGas);
  delay(1500);

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Calidad aire:");
  lcd.setCursor(0,1); lcd.print(calidadAire);
  delay(1500);
}

// —————— función para actualizar LEDs vía 74HC595 —————————
void updateLEDs(int level){
  byte dataOut = 0;
  // encendemos los 'level' primeros LEDs
  for(int i=0; i<8; i++){
    if(i < level) dataOut |= (1 << i);
  }
  digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, dataOut);
  digitalWrite(LATCH_PIN, HIGH);
}
