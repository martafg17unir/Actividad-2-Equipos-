#include <Servo.h>

Servo myservo;  // crea un objeto servo para controlar el motor

int pos = 0;    // variable para almacenar la posición

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // conecta el servo al pin digital 9
}

void loop() {
  // de 0 a 180 grados
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);    // envía la posición al servo
    delay(15);             // espera para que el servo alcance la posición
  }

  // de 180 a 0 grados
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);    // envía la posición al servo
    delay(15);             // espera para que el servo alcance la posición
  }
}
