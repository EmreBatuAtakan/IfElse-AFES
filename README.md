# AFES

AFES stands for Autonomous Fire Extinguisher System. The robot's main goal is to detect and act early on cargo ship fires before the help arrives. 


## Description

Two [ESP32](https://www.espressif.com/en/products/socs/esp32)s are used to establish a communication system between the robot and the sensor box with the help of [ESP-NOW](https://www.espressif.com/en/solutions/low-power-solutions/esp-now). If a certain level of gas is read on the sensor box, the robot was activated. 


### The Robot

To make the robot know where to go, it is decided to make the robot follow a line. Therefore, a [3-Channel Line Tracking Sensor Module](https://makerselectronics.com/product/line-tracker-module-3-channels) is used on the robot. 

For robot movement; 
* 4 [59mm Omni Wheel](https://en.wikipedia.org/wiki/Omni_wheel)s, 
* 4 [Titan 12V 500 Rpm Geared DC Motor](https://www.jsumo.com/titan-dc-gearhead-motor-12v-500-rpm-sp)s, 
* 4 [L298N Motor Driver Module](https://www.st.com/resource/en/datasheet/l298.pdf)s are used.

The robot base has an octagon shape and [Holonomic Drive](https://wiki.purduesigbots.com/hardware/vex-drivetrains/holonomic-drive) is used.

To fit the shaft of Titan Motors into the Omni wheels, custom pieces were produced using Solidworks and a 3D printer.

To be able to extinguish fire in an area, two fire extinguishers are stacked up on the robot base. To be accurate on where to blow the extinguishers, 6 [Flame Sensor Module](https://cdn.shopify.com/s/files/1/0672/9409/files/flame_sensor_manual_and_code.pdf?682)s that are placed around the robot are used.


### The Sensor Box

The sensor box has gas sensors to calculate the values of certain gases to make the robot act accordingly.

Some of the sensors and the gases they detect can be listed as;

| SENSOR | GAS DETECTED |
| --- | --- |
| [MQ-135](https://www.electronicoscaldas.com/datasheet/MQ-135_Hanwei.pdf) | NH3(Ammonia), NOx, alcohol, Benzene, smoke, CO2(Carbon dioxide) |
| [MQ-2](https://www.pololu.com/file/0J309/MQ2.pdf) | LPG, Propane, Hydrogen, Methane, other combustible steam |
| [MQ-7](https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-7.pdf) | CO(Carbon monoxide) |
| [MQ-9](https://www.electronicoscaldas.com/datasheet/MQ-9_Hanwei.pdf) | CO(Carbon monoxide), CH4, LPG |


## Getting Started

### Dependencies

#### Hardware Dependencies
* [ESP32](https://www.espressif.com/en/products/socs/esp32)
* [3-Channel Line Tracking Sensor Module](https://makerselectronics.com/product/line-tracker-module-3-channels)
* [59mm Omni Wheel](https://en.wikipedia.org/wiki/Omni_wheel)
* [Titan 12V 500 Rpm Geared DC Motor](https://www.jsumo.com/titan-dc-gearhead-motor-12v-500-rpm-sp)
* [L298N Motor Driver Module](https://www.st.com/resource/en/datasheet/l298.pdf)
* [Flame Sensor Module](https://cdn.shopify.com/s/files/1/0672/9409/files/flame_sensor_manual_and_code.pdf?682)
* [MQ-135](https://www.electronicoscaldas.com/datasheet/MQ-135_Hanwei.pdf)
* [MQ-2](https://www.pololu.com/file/0J309/MQ2.pdf)
* [MQ-7](https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-7.pdf)
* [MQ-9](https://www.electronicoscaldas.com/datasheet/MQ-9_Hanwei.pdf)

> Alternatives can be used if possible.

#### Software Dependencies
* [Arduino Software](https://www.arduino.cc/en/software)
* [ESP-NOW](https://www.espressif.com/en/solutions/low-power-solutions/esp-now)

> Alternatives can be used if possible.

### Executing program

* Run using Arduino Software.
