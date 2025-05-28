# Actividad-2-Equipos-
Repositorio para actividad 2 equipos del grupo 7

## 1.	Introducción

El objetivo es realizar una pequeña aplicación de medición, control, actuación y presentación del clima que se ejecute en el dispositivo programable. Se adiciona a lo ejecutado en la actividad 1 (medición y presentación) la parte de control y actuación integrando todo el sistema con instrumentación programable.

## 2. Realización de ejemplos

## 3.	Sistema conjunto de medición, control y actuación

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

<p align="center">
  <strong>El código se encuentra en este enlace:</strong> <a href="[https://wokwi.com/projects/1234567890abcdef](https://wokwi.com/projects/431637870217802753)">Simulación en Wokwi</a>
</p>



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


   
