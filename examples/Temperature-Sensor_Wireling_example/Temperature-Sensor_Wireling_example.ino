/*************************************************************************
 * PCT2075 Temperature Sensor Wireling Example 
 * Reads and outputs PCT2075 values to the Serial Monitor when uploaded, 
 * including Temperature in degrees Celsius/Fahrenheit, Thyst - hysteresis, 
 * Tos - threshold, and the configuration register.
 * 
 * Initiated: 8-10-2017 by Brandon Farmer for TinyCircuits
 * Updated: 8-8-2019 by Laveréna Wienclaw for TinyCircuits
 *************************************************************************/

#include <Wire.h>
#include <TinyCircuits_PCT2075.h>
#include <Wireling.h>

TinyCircuits_PCT2075 tempSensor = TinyCircuits_PCT2075();

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

void setup() {
  SerialMonitorInterface.begin(9600);
  while(!SerialMonitorInterface);  // Blocks sensor printing data until Serial Monitor is opened

  // Enable and Power wirelings
  Wireling.begin();
  
  Wire.begin(); // begin I2C communication
  Wireling.selectPort(0);
//  const int tempPin = 0;       //IO Pin D2 = Interrupt Pin 0 

  //Initialize the sensor with config settings
  tempSensor.begin(PCT2075_ACTIVE_LOW, PCT2075_COMPARATOR, PCT2075_NORMAL, PCT2075_FAULT_6X);

//  pinMode(tempPin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(tempPin), interruptServiceRoutine, FALLING);

  tempSensor.wake(); // Wake up the module
}

void loop() {
  setup();
  float rawTemp = tempSensor.readTemp() / 32.0; // Divide by 32 to get rid of empty 5 LSB
  float tempC = (rawTemp * 0.125); // Conversion to degreesC noted on page 11 of datasheet
  float tempF = (tempC * 1.8 + 32); // Conversion from degreeC to degreeF

  if (tempSensor.checkMode() == 0) {
    tempSensor.writeOvertemp(30);
    tempSensor.writeHyst(29);
    
    SerialMonitorInterface.print("Temp.C = ");
    SerialMonitorInterface.print(tempC);
    SerialMonitorInterface.print(" C");
    SerialMonitorInterface.print("\t");
    SerialMonitorInterface.print("Temp.F = ");
    SerialMonitorInterface.print(tempF);
    SerialMonitorInterface.print(" F");
    SerialMonitorInterface.print("\t");
    SerialMonitorInterface.print("Thyst = "); // Hysteresis 
    SerialMonitorInterface.print(tempSensor.readHyst()); 
    SerialMonitorInterface.print("C");
    SerialMonitorInterface.print("\t");
    SerialMonitorInterface.print("Tos = "); // Threshold
    SerialMonitorInterface.print(tempSensor.readTos()); 
    SerialMonitorInterface.print("C");
    SerialMonitorInterface.print("\t");
    SerialMonitorInterface.print("Config: ");
    SerialMonitorInterface.print("0b");
    SerialMonitorInterface.print(tempSensor.readConfig(), BIN);
    SerialMonitorInterface.print("\t");
    SerialMonitorInterface.print("Mode = ");
    SerialMonitorInterface.println(tempSensor.checkMode()); 
    SerialMonitorInterface.println("---------------------------------------------------------------------------------------------------------------------------");

    delay(250);
//    tempSensor.sleep();
  }
  else {
    SerialMonitorInterface.println("SENSOR IN SLEEP MODE!"); 
    SerialMonitorInterface.println(tempSensor.readConfig(), BIN);
    tempSensor.wake(); 
    delay(250);  
  }
}
