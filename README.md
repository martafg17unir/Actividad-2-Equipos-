# Actividad-2-Equipos-
Repositorio para actividad 2 equipos del grupo 7

## 1.	Introducción

El objetivo es realizar una pequeña aplicación de medición, control, actuación y presentación del clima que se ejecute en el dispositivo programable. Se adiciona a lo ejecutado en la actividad 1 (medición y presentación) la parte de control y actuación integrando todo el sistema con instrumentación programable.

## 2. Realización de ejemplos

## 3.	Sistema conjunto de medición, control y actuación

Como se especifica en el guión de la actividad, el objetivo general es diseñar e implementar un sistema de medición, control, actuación y presentación de variables climáticas utilizando Arduino UNO y otros componentes electrónicos, que simule el mantenimiento de condiciones óptimas para un sistema de baterías basado en la información climática recogida por sensores. 
Para la medición del estado del clima se utilizó el proyecto creado para la Actividad 1, que realiza mediciones de temperatura, humedad e iluminación. El sistema de baterías debe mantenerse en torno a 25 °C y 80% de humedad.
En cuanto a la aplicación de estándares de seguridad y calidad en control; si la temperatura es superior a 28 °C se activa el enfriamiento, si es inferior a 22 °C se activa el calentamiento, y entre ambas temperaturas se encuentra en reposo (zona muerta). Para la iluminación, si hay menos luz ambiente, se encienden más LEDs como iluminación artificial. En lo relativo a la humedad,  existen dos relés que actúan como humidificador y deshumidificador. Cuando la humedad baja de 75%, el humidificador se activa, y cuando ésta supera el 85%, se activa el deshumidificador, con el objetivo de mantener esta variable alrededor del 80%.

Componente	Función en el circuito
DHT22	Sensor temperatura y humedad
LDR	Sensor iluminación ambiental
MQ2	Sensor calidad del aire
8 LEDs	Iluminación artificial
74HC595	Expande las salidas digitales de Arduino
Servo 1	Enfriamiento (simulado)
Servo 2	Calentamiento (simulado)
Display LCD	Visualización
Relay Module 1 	Humidificador
Relay Module 2	Deshumidificador
El sistema realiza una estimación continua del consumo energético total expresado en vatios-hora (Wh), teniendo en cuenta el tiempo de actividad acumulado de los diferentes componentes del montaje. Cada componente tiene una potencia de funcionamiento asignada de manera estimada (servomotores 5W, relé humidificador 3W, relé deshumidificador 4W, LEDs 0.1W cada unidad encendida).
 
<img width="469" alt="image" align = "center" src="https://github.com/user-attachments/assets/2fcb6aef-01ef-4a8d-b495-1ba9b612b2bd" />

<img width="469" alt="image" align = "center" src="https://github.com/user-attachments/assets/58869ec0-05c6-462e-9fe5-9aabe5dd34c9" />




   
