// TinyCircuits - PCT2075 Temperature Sensor Library 
// Written by: Brandon Farmer for TinyCircuits 
//
// Initiated: Thu. 8/10/2017 @  6:45PM 
//   Updated: Fri. 8/25/2017 @  3:30PM  
//
// Revision 0 - Original Release
//	RELEASED: MM/DD/YYYY ***Not Yet Released***
//
//*******************************************************************

#ifndef _TinyCircuits_PCT2075_H_
#define _TinyCircuits_PCT2075_H_

#include <Arduino.h>
#include <Wire.h>

#define PCT2075_ADDRESS 		(0x48)		//3LSB determined by Resistors - Default 000

#define PCT2075_TEMP 			(0x00) 		//Stores Temperature Data (16-bit)
#define PCT2075_CONF 			(0x01)		//Sets operating conditions (8-bit) 
#define PCT2075_THYST 			(0x02)		//Hysteresis Register (16-bit, Default 75°C)
#define PCT2075_TOS 			(0x03)		//Overtemp. Shutdown Register, stores threshold (16-bit, Default 80°C) Essentially an Interrupt Pin? 
#define PCT2075_TIDLE 			(0x04)		//Temperature Conversion Cycle - default 100ms period

typedef enum {
	PCT2075_ACTIVE_LOW = 0x00, 				//Active  LOW Interrupt Output
	PCT2075_ACTIVE_HIGH = 0x04 				//Active HIGH Interrupt Output
} PCT2075_Polarity_t; 

typedef enum {
	PCT2075_COMPARATOR = 0x00, 				//Comparator Mode 
	PCT2075_INTERRUPT = 0x02 				// Interrupt Mode 
} PCT2075_Interrupt_t; 

typedef enum {
	PCT2075_NORMAL = 0x00, 					//Normal Operation
	PCT2075_SHUTDOWN = 0x01					//Shutdown (sleep mode)
} PCT2075_Shutdown_t; 

typedef enum {
	PCT2075_FAULT_1X = 0x00, 						
	PCT2075_FAULT_2X = 0x08, 
	PCT2075_FAULT_4X = 0x10, 
	PCT2075_FAULT_6X = 0x18
} PCT2075_Fault_t; 


class TinyCircuits_PCT2075 {
	public: 
		TinyCircuits_PCT2075(); 			//Constructor 
		
		void begin(PCT2075_Polarity_t = PCT2075_ACTIVE_LOW, PCT2075_Interrupt_t = PCT2075_COMPARATOR, PCT2075_Shutdown_t = PCT2075_NORMAL, PCT2075_Fault_t = PCT2075_FAULT_1X); 
		int16_t readTemp(void); 					//Reads the Temperature Value 
		uint16_t readHyst(void); 					//Reads the Low Temperature Value 
		uint16_t readTos(void); 					//Reads the High Temperature Value 
		void writeHyst(uint16_t threshold); 		//Sets Low Temperature Value 
		void writeOvertemp(uint16_t threshold); 	//Sets High Temperature Value 
		uint8_t readConfig(void);					//Reads the settings from the CONFIG register
		void sleep(void);							//Puts the device to sleep 
		void wake(void); 							//Wakes the device up 
		bool checkMode(void);						//Is the device awake or asleep?
		void setSampleTime(uint8_t time); 			//0 to 31 in increments of 100ms (100ms to 3.1s )
	
	private: 
		//None 
};

#endif 


