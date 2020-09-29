float cbfr;
float humbfr;

float arahAngin(){
  float arah;
  if(digitalRead(utara)==LOW){arah = 0;}
  else if(digitalRead(tl)==LOW){arah = 45;}
  else if(digitalRead(timur)==LOW){arah = 90;}
  else if(digitalRead(tenggara)==LOW){arah = 135;}
  else if(digitalRead(selatan)==LOW){arah = 180;}
  else if(digitalRead(bd)==LOW){arah = 225;}
  else if(digitalRead(barat)==LOW){arah = 270;}
  else if(digitalRead(bl)==LOW){arah = 315;}
  return arah;
}
// Measure wind speed
void addcount()
{
counter++;
}

float kecAngin(){
  Sample++;
  float windSpeed;
  speedwind = 0;
  counter = 0;
  attachInterrupt(0, addcount, CHANGE);
  unsigned long millis();
  long startTime = millis();
  while(millis() < (startTime + period)) {}

  detachInterrupt(1);

  RPM=((counter/jml_celah)*60)/(period/1000); // Calculate revolutions per minute (RPM)
  speedwind = ((2 * pi * radio * RPM)/60) / 1000; // Calculate wind speed on m/s
  counter++;
  windSpeed = speedwind;

  return windSpeed;
}


float bacaTanah(){
  float phTanah;
  //read the analog in value:
  int sensorTanahValue = analogRead(phTanahPin);

  //Mathematical conversion from ADC to pH
  //rumus didapat berdasarkan datasheet 
  float outputTanahValue = (-0.0693*sensorTanahValue)+7.3855;
  phTanah = outputTanahValue;
  return phTanah;
}

//float bacaHujan(){
//  float curahHujan;
//  float dailyRain;                   // rain accumulated for the day
//  float hourlyRain;                  // rain accumulated for one hour
//  float dailyRain_till_LastHour;

// DateTime now = rtc.now();
//  // ++++++++++++++++++++++++ Count the bucket tips ++++++++++++++++++++++++++++++++
//  if ((bucketPositionA==false)&&(digitalRead(RainPin)==LOW)){
//    bucketPositionA=true;
//    dailyRain+=bucketAmount;                               // update the daily rain
//  }
//  
//  if ((bucketPositionA==true)&&(digitalRead(RainPin)==HIGH)){
//    bucketPositionA=false;  
//  } 
//  // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  
//  if(now.minute() != 0) first = true;                     // after the first minute is over, be ready for next read
//  
//  if(now.minute() == 0 && first == true){
// 
//    hourlyRain = dailyRain - dailyRain_till_LastHour;      // calculate the last hour's rain 
//    dailyRain_till_LastHour = dailyRain;
//    curahHujan = dailyRain*2.54*10; //satuan mm
//    first = false;                                        // execute calculations only once per hour
//  }
//  
//  if(now.hour()== 0) {
//    dailyRain = 0.0;                                      // clear daily-rain at midnight
//    dailyRain_till_LastHour = 0.0;   
//  }
//  return curahHujan;
//}

double read_baro()
{
  double realPressure2;
  realPressure2 = MS5611.getPressure() * 0.01;
  return realPressure2;
  
//  float realTemperature2 = MS5611.getTemperature(true);
//  long realPressure2 = MS5611.getPressure(true);
//  double realAltitude2 = MS5611.getAltitude(realPressure2);
//  return realPressure2/101325.0;
}

void tempEcSoil(){
  float e25 = vcs.getE25();
  float ec = vcs.getEC();
  float temp = vcs.getTemp();
  float vwc = vcs.getVWC();
  float dat[4]={0,0,0,0};
  vcs.getData(dat);
  delay(1000);  
}

float ecSoil(){
  float ecTanah;
  ecTanah = vcs.getEC();
  return ecTanah;
}

float read_temp(){
  float temp_c;
  temp_c = sht1x.readTemperatureC();
  if(temp_c<0 || temp_c>80){temp_c = cbfr;}
  cbfr = temp_c;
  return temp_c;
}

float read_hum(){
  float humidity;
  humidity = sht1x.readHumidity();
  if(humidity<0 || humidity>100){humidity = humbfr;}
  humbfr = humidity;
  return humidity;
}
