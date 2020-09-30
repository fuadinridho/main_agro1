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
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
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

#define dataPin  30
#define clockPin 29

float air_temperature,air_humidity,air_pressure,rain_gauge,wind_speed,soil_temp,soil_moist,soil_ph,soil_EC;
unsigned int wind_direction;
double gpslat,gpslon;
String body;
WiFiUDP udp;
NTPClient ntpClient(udp, "id.pool.ntp.org", ((22*60*60)+(0*60))); // IST = GMT + 7:00


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
float arah;
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
  Wire.begin();
  MS5611.begin();
  gpsPort.begin(9600);
}


void loop()
{
   
//Sample++;
arah = arahAngin();

//Serial.println(" finished.");
//Serial.print("Counter: ");
//Serial.print(counter);
//Serial.print("; RPM: ");
//RPMcalc();
//Serial.print(RPM);
//Serial.print(" [m/s]");
phTanah = bacaTanah();

//curahHujan = bacaHujan();
//Serial.println(curahHujan);
//Serial.print(phTanah);
//GPSloop();
//delay(5000);
windSpeed = kecAngin();

pressure = read_baro();
ecTanah = ecSoil();
tempEcSoil();
//Serial.print(dat[0]);
//Serial.print('\t');
//Serial.print(dat[3]);
//Serial.print('\t');
suhu = read_temp();
kelembaban = read_hum();

body = bodyJSON(suhu,kelembaban,pressure,rain_gauge,windSpeed,arah,dat[2],dat[0],phTanah,dat[1],gpslat,gpslon);
//Serial.print(arah);
//Serial.print('\t');
//Serial.print(phTanah);
//Serial.print('\t');
//Serial.print(windSpeed);
//Serial.print('\t');
//Serial.print(pressure);
//Serial.print('\t');
//Serial.print(ecTanah);
//Serial.print('\t');
//Serial.print(dat[1]);//ec tanah
//Serial.print('\t');
//Serial.print(dat[2]);//temp tanah
//Serial.print('\t');
//Serial.print(suhu);
//Serial.print('\t');
//Serial.println(kelembaban);
Serial.println(body);
}
