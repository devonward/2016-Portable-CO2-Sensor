/*============================================================
 This sketch records CO2 levels (from a SPRINTIR WR CO2 sensor)
 and logs the data in a .txt file on an SD Card. 
 =============================================================
 
 This sketch was created by combining these sketches:
 / 1 / Test CO2 Sensor sketch by Andrew Pelling
 https://github.com/pellinglab/DIY-Incubator-Dec2014/blob/master/Test_CO2_Sensor/Test_CO2_Sensor.ino
 / 2 / SD card datalogger sketch by Tom Igoe
 https://www.arduino.cc/en/Tutorial/Datalogger
 / 3 / Seeduino SDCardshield V4 sketch 
 http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0
 
 sensor: SPRINTIR WR (0-100%) CO2 sensor [GC-0018]
 http://www.co2meter.com/collections/co2-sensors/products/sprintir-100-percent-co2-sensor
 SD shield: Seeduino SDCard Shield v4.0 [16GB microSDHC] 
 http://www.seeedstudio.com/wiki/SD_Card_shield_V4.0 
 
 */

#include <SPI.h>
#include <SD.h>
#include "cozir.h"
#include "SoftwareSerial.h"

SoftwareSerial nss(2, 3); // Tx, Rx from the sensor to Pins 2, 3 on Arduino
COZIR czr(nss);

float c, ppm, t, l, f, h, reading = 0;  // create variables for data collection
float ppmmultiplier = 100; // based on the hardware specs (100 for range of 0-100% CO2) 
float multiplier = 0.01;   // 0.01 = 100/10,000 (Hardware multiplier/ppm conversion)
                           // For more details see sensor specificaiton sheet  

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

//id
unsigned long i=0;
int interval = 100;
 
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  czr.SetOperatingMode(CZR_POLLING);
  
  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if(dataFile) { 
    dataFile.println("/card initialized");
    String headerString = "timer(ms), data, ppm, percent";
    dataFile.println(headerString);
    dataFile.close();
    // print to the serial port too:
    Serial.println("/card initialized");
    Serial.println(headerString);
  }
  else {
    Serial.println("Error. Couldn't open log file");
  }
  delay(100);
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";
  // read CO2 levels
  c = czr.CO2();                         // read the sensor, CO2 values output as ppm
  /* ======================
  Optional extras values if your COZIR
  CO2 sensor is equipped with extra sensors
  =========================
  l = czr.Light();                       // read the Light sensor values 
  t = czr.Celsius();                     // read the Temp sensor values (output in Celsius)
  f = czr.Fahrenheit();                  // read the Temp sensor values (output in Fahrenheit)
  h = czr.Humidity();                    // read the Humidity sensor
  ======================== */
  ppm = c*ppmmultiplier;                 // converts reading to ppm
  reading = c*multiplier;                // converts ppm reading to percentage
  
  //converts int values to strings for datalogging
  dataString = String(i*interval) + ", " +  String(c) + ", " + String(ppm) + ", " + String(reading) + ";";

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  
  if(dataFile) {                         // check if the file is available, write to it
    dataFile.println(dataString);        // log the dataString in dataFile
    dataFile.close();                    // close dataFile
    Serial.println(dataString);          // print to the serial port too:
  }
  else {                                  // else send failure report to serial monitor
    Serial.println("Error. Couldn't open log file");
  }
  i++;                                    // increment the time 
  delay(interval);
  
}









