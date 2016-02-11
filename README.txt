// General Info //

Portable-CO2-Sensor-with-Datalogger
February 2016

This repository is contains information to program an Arduino to read data from a CO2 Sensor and writes to a .txt file on an SD card. 

// Hardware Info //

> sensor: SPRINTIR WR (0-100%) CO2 sensor [GC-0018]
http://www.co2meter.com/collections/co2-sensors/products/sprintir-100-percent-co2-sensor
> SD shield: Seeduino SDCard Shield v4.0 [16GB microSDHC] 
http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0 


// Repository File Structure //

> Portable-CO2-Sensor-with-Datalogger
	> Arduino Sketch for data collection and logging
> general info
	> datasheet for CO2 Sensor (SPRINT IR WR 0-100%)
	> manual for CO2 Sensor (COZIR Guide)
	> instructions for Seeduino SDCard Shield V4 (from wikipedia)

// Important Notes //

> Many thanks to all of those that made this sketch possible. 
> This sketch was created by combining these sketches:
  / 1 / Test CO2 Sensor sketch by Andrew Pelling:
	> http://www.pellinglab.net/diy/diyco2incubator/
	> https://github.com/pellinglab/DIY-Incubator-Dec2014/blob/master/Test_CO2_Sensor/Test_CO2_Sensor.ino
  / 2 / SD card datalogger sketch by Tom Igoe:
	> https://www.arduino.cc/en/Tutorial/Datalogger
  / 3 / Seeduino SDCardshield V4 sketch: 
	> http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0
 