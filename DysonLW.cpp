/******************************************************************************
DysonLW.cpp
Library for interfacing with the Project Dyson long wave pyranometer 
Bobby Schulz @ Northern Widget LLC
7/5/2018
https://github.com/NorthernWidget-Skunkworks/Project-Dyson

This script is used to interface to the Dyson shortwave pyranometer module and provide 
conversions for some of the values into the appropriate human-readable units.

"The laws of nature are constructed in such a way as to make the universe as interesting as possible."
-Freeman Dyson

Distributed as-is; no warranty is given.
******************************************************************************/

#include "Wire.h"
#include "math.h"
#include "DysonLW.h"

DysonLW::DysonLW() 
{

}

uint8_t DysonLW::begin() 
{
	Wire.begin();
  WriteWord_LE(ADC_ADR, ADC_CONF, ADC0); //Set to single shot mode with 
}

float DysonLW::GetThermo()
{
  return GetADC(ADC1)*(1.25e-4); //Convert to voltage 
}


float DysonLW::GetTemp()
{
  float Val = float(GetADC(ADC0))*(1.25e-4);
  return TempConvert(Val, 1.8, 10000.0, A, B, C, D, 10000.0) - 273.15;
}

float DysonLW::TempConvert(float V, float Vcc, float R, float A, float B, float C, float D, float R25)
{
  // float Rt = (Vcc/V)*R - R;  //Use if thermistor is on TOP side of voltage divider
  float Rt = -R/(1 - (Vcc/V)); //Use if thermistor is on BOTTOM side of voltage divider  
  float LogRt = log(Rt/R25);
  float T = 1.0/(A + B*LogRt + C*pow(LogRt, 2.0) + D*pow(LogRt, 3.0));
  return T;
}
 
//ADD referance compensation!  

String DysonLW::GetHeader()
{
  return ", IR_Long [mV], PyrgT [C]";
}

String DysonLW::GetString()
{
  return "," + String( GetThermo()) + "," + String(GetTemp());
}

unsigned int DysonLW::GetADC(unsigned int Num)
{
  unsigned int ADC_Config = ADC0 | (Num << 12); //Use to select which ADC to get data from
  WriteWord_LE(ADC_ADR, ADC_CONF, ADC_Config); //Setup registers
  delay(300);  //Wait for next sample to be read
  return ReadWord_LE(ADC_ADR, ADC_CONV); //Read from register
}

uint8_t DysonLW::WriteWord_LE(uint8_t Adr, uint8_t Command, unsigned int Data)  //Writes value to 16 bit register
{
  Wire.beginTransmission(Adr);
  Wire.write(Command); //Write Command value
  Wire.write((Data >> 8) & 0xFF); //Write MSB
  Wire.write(Data & 0xFF); //Write LSB
  return Wire.endTransmission();
  // return Error;  //Invert error so that it will return 0 is works
}

int DysonLW::ReadWord_LE(uint8_t Adr, uint8_t Command)  //Send command value, returns entire 16 bit word
{
  bool Error = SendCommand(Adr, Command);
  Wire.beginTransmission(Adr);
  uint8_t ByteHigh = Wire.read();  //Read in high and low bytes (big endian)
  uint8_t ByteLow = Wire.read();
  Wire.endTransmission();
  // if(Error == true) return ((ByteHigh << 8) | ByteLow); //If read succeeded, return concatonated value
  // else return -1; //Return error if read failed
  return ((ByteHigh << 8) | ByteLow); //DEBUG!
}

uint8_t DysonLW::SendCommand(uint8_t Adr, uint8_t Command)
{
    Wire.beginTransmission(Adr);
    Wire.write(Command);
    return Wire.endTransmission(); 
}