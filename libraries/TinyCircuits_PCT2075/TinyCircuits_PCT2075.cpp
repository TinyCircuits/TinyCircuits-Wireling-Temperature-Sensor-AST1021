//*******************************************************************
// TinyCircuits - PCT2075 Temperature Sensor Library 
// Written by: Brandon Farmer for TinyCircuits 
//
// Initiated: 8/10/2017
//   Updated: 8/8/2019 
//
//*******************************************************************

#include <avr/pgmspace.h>
#include <math.h> 
#include <stdlib.h> 
#include <Arduino.h> 
#include <Wire.h> 
#include "TinyCircuits_PCT2075.h"

// Constructor 
TinyCircuits_PCT2075::TinyCircuits_PCT2075(void) { 
	//Nothing 
}

// Start Device and set Configuration Register
void TinyCircuits_PCT2075::begin(PCT2075_Polarity_t p, PCT2075_Interrupt_t i, PCT2075_Shutdown_t s, PCT2075_Fault_t f) {
	uint8_t x = (p | i | s | f); 
	Wire.begin(); 
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_CONF);
	Wire.write(x);
	Wire.endTransmission();
}

// Read Configuration Register 
uint8_t TinyCircuits_PCT2075::readConfig(void) {
	uint8_t x;
	
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_CONF); 
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 1); 
	x = Wire.read(); 
	
	return x; 
}

// Retrieve Temperature Data 
int16_t TinyCircuits_PCT2075::readTemp(void) {
	int16_t temp; 
	
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_TEMP);
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 2); 
	temp = Wire.read(); //Holds MSB of data
	temp<<=8;
	temp |= Wire.read(); //Holds LSB of data
	
	return temp; 
}

// Write Hysteresis Register 
void TinyCircuits_PCT2075::writeHyst(uint16_t threshold) {
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_THYST); 
	Wire.write(threshold);
	threshold>>=8;
	Wire.write(threshold); 
	Wire.endTransmission(); 
}

// Write Overtemp Register 
void TinyCircuits_PCT2075::writeOvertemp(uint16_t threshold) {
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_TOS); 
	Wire.write(threshold); 
	threshold>>=8;
	Wire.write(threshold); 
	Wire.endTransmission();
}

// Read Hysteresis Register 
uint16_t TinyCircuits_PCT2075::readHyst(void) {
	uint16_t x; uint16_t y; 
	
	Wire.beginTransmission(PCT2075_ADDRESS);
	Wire.write(PCT2075_THYST); 
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 2); 
	x = Wire.read(); 
	y = Wire.read(); 
	
	x <<= 8; 
	x |= y;
	x >>= 8; 
	
	return x; 
}

// Read Overtemperature Shutdown Register 
uint16_t TinyCircuits_PCT2075::readTos(void) {
	uint16_t x; uint16_t y; 
	
	Wire.beginTransmission(PCT2075_ADDRESS);
	Wire.write(PCT2075_TOS); 
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 2); 
	x = Wire.read(); 
	y = Wire.read(); 
	
	x <<= 8; 
	x |= y;
	x >>= 8; 
	
	return x;
}

// Sleep Mode (Shut-down ~<1.0uA)
void TinyCircuits_PCT2075::sleep(void) {
	uint8_t data; 
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_CONF); 
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 1);
	data = Wire.read(); 
	
	data |= 0x01; 
	
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_CONF);
	Wire.write(data); 
	Wire.endTransmission(); 
}

// Wake (back to Normal mode ~70uA)
void TinyCircuits_PCT2075::wake(void) {
	uint8_t data; 
	
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_CONF); 
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 1);
	data = Wire.read(); 
	
	data &= 0x1E; 
	
	Wire.beginTransmission(PCT2075_ADDRESS);
	Wire.write(PCT2075_CONF); 
	Wire.write(data); 
	Wire.endTransmission(); 
}

// Check sleep/wake mode 
bool TinyCircuits_PCT2075::checkMode(void) {
	uint8_t state; 
	
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_CONF); 
	Wire.endTransmission(); 
	
	Wire.requestFrom(PCT2075_ADDRESS, 1);
	state = Wire.read(); 
	
	state &= 0x01;  
	
	return state; 
}

// Sets sample period (100ms to 3.1s)
void setSampleTime(uint8_t time) {
	time = (time & 0x1F);
	
	Wire.beginTransmission(PCT2075_ADDRESS); 
	Wire.write(PCT2075_TIDLE); 
	Wire.write(time);
	Wire.endTransmission();
}














