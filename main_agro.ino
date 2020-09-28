#include <SPI.h>
#include <Wire.h>
//#include "RTClib.h"
#include <NMEAGPS.h> // GPS
#include <GPSport.h>
#include <NMEAGPS_cfg.h>
#include <GPSfix_cfg.h>
#include <MS5611.h> //barometer
#include "Config.h"
#include "i2cArduino.h"
#include <SHT1x.h>
///////////////////////////////////////////////////////
//#define RainPin 16    // The Rain input is connected to digital pin 2 on the arduino
// pin defenition wind direction
#define utara 24
#define tl 33
#define timur 32
#define tenggara 31
#define selatan 25
#define bd 26
#define barat 27
#define bl 28
///////////////////////////////////////////////////////////////////////////////////
// Pin definitions anemometer
# define windPin 2 // Receive the data from sensor

#define dataPin  29
#define clockPin 30

// Constants definitions
const float pi = 3.14159265; // pi number
int period = 10000; // Measurement period (miliseconds)
int delaytime = 10000; // Time between samples (miliseconds)
int radio = 90; // Distance from center windmill to outer cup (mm)
int jml_celah = 18; // jumlah celah sensor

// Variable definitions
unsigned int Sample = 0; // Sample number
unsigned int counter = 0; // B/W counter for sensor
unsigned int RPM = 0; // Revolutions per minute
float speedwind = 0; // Wind speed (m/s)
//////////////////////////////////////////////////////////////////////////////////////
//analog pin 
#define phTanahPin A9  //sambungkan kabel hitam (output) ke pin A0

//variable
int sensorTanahValue = 0;        //ADC value from sensor
float outputTanahValue = 0.0;        //pH value after conversion
//////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
static NMEAGPS gps;
MS5611 MS5611(0x77);
SVCS3 vcs;
SHT1x sht1x(dataPin, clockPin);

///////////////////////////////////////////////////////////////////////////////////////
static void GPSloop();
String arah;
float phTanah;
float curahHujan;
double longitude,latitude;
float windSpeed;
float sudutX,sudutY,sudutZ;
float akselX,akselY,akselZ;
bool first=false;
double pressure; 
float e25;
float ec ;
float temp; 
float vwc;
float dat[4];
float ecTanah;
float kelembaban;
float suhu; 

//const char* param(char buffer[], int deviceId, float temp, float hum, float flux, float baro, float longitude, float latitude) {
//  char valueBuffer[10];
//
//  strcpy_P(buffer, (const char *)F(""));
//  strcat_P(buffer, (const char *)F("device_id="));
//  strcat(buffer, itoa(deviceId, valueBuffer, 10));
//  strcat_P(buffer, (const char *)F("&temperature="));
//  strcat(buffer, dtostrf(temp, 2, 2, valueBuffer));
//  strcat_P(buffer, (const char*)F("&humidity="));
//  strcat(buffer, dtostrf(hum, 2, 2, valueBuffer));
//  strcat_P(buffer, (const char*)F("&luminous_flux="));
//  strcat(buffer, dtostrf(flux, 2, 2, valueBuffer));
//  strcat_P(buffer, (const char*)F("&air_pressure="));
//  strcat(buffer, dtostrf(baro, 2, 2, valueBuffer));
//  strcat_P(buffer, (const char*)F("&longitude="));
//  strcat(buffer, dtostrf(longitude, 2, 2, valueBuffer));
//  strcat_P(buffer, (const char*)F("&latitude="));
//  strcat(buffer, dtostrf(latitude, 2, 2, valueBuffer));
//
//  return buffer;
//}

void setup() 
{
  Serial.begin(115200);
  
  pinMode(utara,INPUT_PULLUP);
  pinMode(tl,INPUT_PULLUP);
  pinMode(timur,INPUT_PULLUP);
  pinMode(tenggara,INPUT_PULLUP);
  pinMode(selatan,INPUT_PULLUP);
  pinMode(bd,INPUT_PULLUP);
  pinMode(barat,INPUT_PULLUP);
  pinMode(bl,INPUT_PULLUP);

  pinMode(2, INPUT);
  digitalWrite(2, HIGH);

//   MS5611.begin(MS5611_ULTRA_HIGH_RES);
  // MS5611.getOversampling();
  vcs.init(0x63);

  gpsPort.begin(9600);
}


void loop()
{
   
//Sample++;
//windvelocity();
//Serial.println(" finished.");
//Serial.print("Counter: ");
//Serial.print(counter);
//Serial.print("; RPM: ");
//RPMcalc();
//Serial.print(RPM);
//Serial.print("; Wind speed: ");
//WindSpeed();
//Serial.print(speedwind);
//Serial.print(" [m/s]");
//arah = arahAngin();
//Serial.print(arah);
//phTanah = bacaTanah();
//Serial.print(phTanah);
//curahHujan = bacaHujan();
//Serial.println(curahHujan);
//Serial.print(phTanah);
//GPSloop();
//delay(5000);
//windSpeed = kecAngin();
//Serial.println(windSpeed);
//pressure = read_baro();
//Serial.println(pressure);
//ecTanah = ecSoil();
//tempEcSoil();
//Serial.print(dat[0]);
//Serial.print('\t');
//Serial.print(dat[1]);
//Serial.print('\t');
//Serial.print(dat[2]);
//Serial.print('\t');
//Serial.print(dat[3]);
//Serial.print('\t');
//Serial.println(ecTanah);
suhu = read_temp();
kelembaban = read_hum();
Serial.print(suhu);
Serial.print('\t');
Serial.println(kelembaban);
}
