/*************************************************************************
   PCT2075 Temperature Sensor Wireling Example
   Simplified to reading just the temperature in F and C

   Written for TinyCircuits by: Laveréna Wienclaw
   Published: January 2022
 *************************************************************************/

#include <Wire.h>
#include <Wireling.h>
#include <TinyCircuits_PCT2075.h>

TinyCircuits_PCT2075 tempSensor = TinyCircuits_PCT2075();

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

void setup() {
  SerialMonitorInterface.begin(9600);
  Wire.begin(); 
  Wireling.begin();

  //Initialize the sensor with config settings
  Wireling.selectPort(0);
  tempSensor.begin(PCT2075_ACTIVE_LOW, PCT2075_COMPARATOR, PCT2075_NORMAL, PCT2075_FAULT_6X);
  tempSensor.wake(); // Wake up the module
}

void loop() {
  float rawTemp = tempSensor.readTemp() / 32.0; // Divide by 32 to get rid of empty 5 LSB
  float tempC = (rawTemp * 0.125); // Conversion to degreesC noted on page 11 of datasheet
  float tempF = (tempC * 1.8 + 32); // Conversion from degreeC to degreeF

  SerialMonitorInterface.print("Temp.C = ");
  SerialMonitorInterface.print(tempC);
  SerialMonitorInterface.print(" C");
  SerialMonitorInterface.print("\t");
  SerialMonitorInterface.print("Temp.F = ");
  SerialMonitorInterface.print(tempF);
  SerialMonitorInterface.print(" F");
  SerialMonitorInterface.println();

  delay(250);
}
