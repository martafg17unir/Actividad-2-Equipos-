# Actividad-2-Equipos-
Repositorio para actividad 2 equipos del grupo 7

## 1.	Introducción

El objetivo es realizar una pequeña aplicación de medición, control, actuación y presentación del clima que se ejecute en el dispositivo programable. Se adiciona a lo ejecutado en la actividad 1 (medición y presentación) la parte de control y actuación integrando todo el sistema con instrumentación programable.

## 2. Realización de ejemplos

Todos los ejemplos se han realizado siguiendo el guion de esta práctica, pero se han adaptado a las limitaciones de WOKWI y se han orientado hacia lo que se pide, que es crear un sistema de control y actuación de temperatura y humedad, otro de iluminación y finalmente, juntar ambos. Se incluye el código utilizado e imágenes.

### 2.1.	Ejemplo de aplicación Servomotor
En este ejemplo se muestra cómo controlar un servomotor directamente desde un pin digital del Arduino sin necesidad de fuente de alimentación externa, ya que no se aplica carga sobre el servo y su consumo es bajo. Utilizando la biblioteca Servo.h, se crea un objeto llamado myservo que permite controlar el ángulo del motor. En la función setup(), se vincula el servo al pin digital 9 y se inicia la comunicación serial. En la función loop(), mediante bucles for, el servo se mueve progresivamente de 0° a 180° y luego regresa a 0°, con retardos de 15 ms entre cada movimiento para garantizar una rotación suave.

<img width="210" alt="image" src="https://github.com/user-attachments/assets/25e6b236-9e9f-47d0-b935-95e55a9d5594" />


###  2.2	Ejemplo de aplicación de control de 8 leds con 74HC595
Una forma de lograr el control de la iluminación es mediante un registro de desplazamiento y 8 leds. Este diseño va a servir para no desperdiciar energía y dar la iluminación necesaria en función del grado de oscuridad. Además, va a permitirnos usar menos pines de la placa.

<img width="277" alt="image" src="https://github.com/user-attachments/assets/26fe91b7-b76b-4ca2-b668-c4eb8460113f" />

###  2.3	Ejemplo básico de sistema de medición, control y actuación
El sistema interpreta la temperatura y humedad mediante un sensor DHT22, detecta el nivel de luz con una LDR y simula la presencia de viento mediante un potenciómetro conectado a un servo motor. En función de los valores obtenidos, el sistema activa LEDs indicadores (calor, frío, confort), enciende la iluminación artificial de forma escalonada, posiciona el servo y muestra la información en una pantalla LCD.
La lógica principal implementa control automático de temperatura con zona muerta (reposo térmico), iluminación artificial en función de la luz ambiente y un indicador de confort ambiental basado en una combinación de temperatura adecuada y buena iluminación.

| Componente        | Función en el circuito                         |
|-------------------|------------------------------------------------|
| DHT22             | Sensor temperatura y humedad                   |
| LDR               | Sensor iluminación ambiental                   |
| MQ2               | Sensor calidad del aire                        |
| 8 LEDs blancos    | Iluminación artificial                         |
| 3 LEDs RGB        | Indicadores de estado térmico                  |
| Potenciómetro     |Simula la fuerza del viento                     |
| Servo             | Gira proporcionalmente a la “fuerza del viento”|
| Display LCD       | Visualización                                  |

<img width="442" alt="image" src="https://github.com/user-attachments/assets/6fe179eb-7fa2-4d40-8881-a1e857ad9c15" />

**El código se encuentra en este enlace: https://wokwi.com/projects/431642408807903233

## 2.3.1 Realización de pruebas:

### Pruebas de control y actuación sobre la temperatura:
Temperatura inferior a 22ºC:
  -Se activa el modo calefacción.
  -Se enciende el LED rojo.
  -En la LCD se muestra “Calor” y el ángulo actual del viento.
  -LEDs blancos pueden encenderse según la luz.

<img width="374" alt="image" src="https://github.com/user-attachments/assets/7941d5f7-d401-4d0b-921e-62089d3006d8" />

Temperatura superior a 28ºC:
  -Se activa el modo refrigeración.
  -Se enciende el LED azul.
  -En la LCD se muestra “Frio” y el ángulo del servo.
  -LEDs blancos pueden encenderse según la luz.

<img width="389" alt="image" src="https://github.com/user-attachments/assets/41cf8697-8c61-41db-9797-f38dda1e9981" />

Temperatura entre 22º y 28ºC:
  -Si la luz es suficiente (≥800), se enciende el LED verde de confort.
  -Estado mostrado en la LCD: “Estable”.

<img width="404" alt="image" src="https://github.com/user-attachments/assets/557cecbd-0f6f-4c18-b917-0d496a523301" />

## 3. Ejemplo final: 	Sistema conjunto de medición, control y actuación

Como se especifica en el guión de la actividad, el objetivo general es diseñar e implementar un sistema de medición, control, actuación y presentación de variables climáticas utilizando Arduino UNO y otros componentes electrónicos, que simule el mantenimiento de condiciones óptimas para un sistema de baterías basado en la información climática recogida por sensores. 
Para la medición del estado del clima se utilizó el proyecto creado para la Actividad 1, que realiza mediciones de temperatura, humedad e iluminación. El sistema de baterías debe mantenerse en torno a 25 °C y 80% de humedad.
En cuanto a la aplicación de estándares de seguridad y calidad en control; si la temperatura es superior a 28 °C se activa el enfriamiento, si es inferior a 22 °C se activa el calentamiento, y entre ambas temperaturas se encuentra en reposo (zona muerta). Para la iluminación, si hay menos luz ambiente, se encienden más LEDs como iluminación artificial. En lo relativo a la humedad,  existen dos relés que actúan como humidificador y deshumidificador. Cuando la humedad baja de 75%, el humidificador se activa, y cuando ésta supera el 85%, se activa el deshumidificador, con el objetivo de mantener esta variable alrededor del 80%.

| Componente        | Función en el circuito                       |
|-------------------|----------------------------------------------|
| DHT22             | Sensor temperatura y humedad                 |
| LDR               | Sensor iluminación ambiental                 |
| MQ2               | Sensor calidad del aire                      |
| 8 LEDs            | Iluminación artificial                       |
| 74HC595           | Expande las salidas digitales de Arduino     |
| Servo 1           | Enfriamiento (simulado)                      |
| Servo 2           | Calentamiento (simulado)                     |
| Display LCD       | Visualización                                |
| Relay Module 1    | Humidificador                                |
| Relay Module 2    | Deshumidificador                             |

El sistema realiza una estimación continua del consumo energético total expresado en vatios-hora (Wh), teniendo en cuenta el tiempo de actividad acumulado de los diferentes componentes del montaje. Cada componente tiene una potencia de funcionamiento asignada de manera estimada (servomotores 5W, relé humidificador 3W, relé deshumidificador 4W, LEDs 0.1W cada unidad encendida).

<p align="center">
  <img src="https://github.com/user-attachments/assets/2fcb6aef-01ef-4a8d-b495-1ba9b612b2bd" width="600" />
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/58869ec0-05c6-462e-9fe5-9aabe5dd34c9" width="600" />
</p>


**El código se encuentra en este enlace: [Simulación en Wokwi](https://wokwi.com/projects/431637870217802753)**


## 4. Realización de pruebas

### 4.1 Pruebas de control y actuación sobre la temperatura:

Temperatura inferior a 22ºC:
 -	Se activa el motor de calefacción.
 -	Se muestra la temperatura anterior y la actual
 -	Se muestra el estado del sistema
 
<p align="center">
<img width="291" alt="image" src="https://github.com/user-attachments/assets/c0fdd6b9-9e56-4565-b3bc-a86f4b998f8c" />
</p>

Temperatura superior a 28ºC:
 -	Se activa el motor de enfriamiento.
 -	Se muestra la temperatura anterior y la actual
 -	Se muestra el estado del sistema

<p align="center">
<img width="296" alt="image" src="https://github.com/user-attachments/assets/46761ee4-112d-41af-8d4b-8135964f093b" />
</p>

Temperatura entre 22º y 28ºC:
 -	Ningún motor activado
 -	Estado: en reposo

<p align="center">
<img width="302" alt="image" src="https://github.com/user-attachments/assets/880e65cd-0805-47cb-8247-aaf682e5daf8" />
<p align="center">
 
## 5.	Conclusión
El sistema creado permite el control automático de temperatura, humedad e iluminación, lo que representa una solución eficaz y adaptable para entornos que requieren condiciones ambientales estables. Entre sus ventajas destacan su bajo coste, la facilidad de programación, la integración de varios sensores y actuadores, la visualización en tiempo real, y el cálculo del consumo energético.
Como desventajas, el sistema depende de sensores de bajo coste cuya precisión puede ser limitada, y no cuenta con almacenamiento de datos ni conectividad remota, lo que reduce sus posibilidades de monitorización avanzada. 


   
