char *listSensor[13] = {
"air_temperature",
"air_humidity",
"air_pressure",
"rain_gauge",
"wind_speed",
"wind_direction",
"soil_temp",
"soil_moist",
"soil_ph",
"soil_EC",
};

char *listUnit[13] = {
"Celcius",
"% RH",
"hPa",
"mm/min",
"m/s",
"derajat",
"Celcius",
"%",
"ph",
"mS/cm"
};



String bodyJSON(float at, float ah, float ap, float rg, float ws, int wd,float st,float sm,float sp,float se,double gla,double glo)
{

    String hasilJSON;
    StaticJsonDocument<1100> doc;
    doc[F("version")] = F("PR-alpha.0.1");
    doc[F("node_id")] = "3425345234";
//    char waktu[100];
//    waktuChr(waktu);
    doc[F("time")] = "2020-09-30 "  + ntpClient.getFormattedTime();
    // JsonArray& item = root.createNestedArray("item");
    
    for (int i = 0; i < 10; i++)
    {  
        StaticJsonDocument<100> sensorJSON;
        sensorJSON[F("sensor_type")] = listSensor[i];
        sensorJSON[F("scale")] = listUnit[i];\
        switch (i)
        {
        case 0:sensorJSON[F("value")] = at;break;
        case 1:sensorJSON[F("value")] = ah;break;
        case 2:sensorJSON[F("value")] = ap;break;
        case 3:sensorJSON[F("value")] = rg;break;
        case 4:sensorJSON[F("value")] = ws;break;
        case 5:sensorJSON[F("value")] = wd;break;
        case 6:sensorJSON[F("value")] = st;break;
        case 7:sensorJSON[F("value")] = sm;break;
        case 8:sensorJSON[F("value")] = sp;break;
        case 9:sensorJSON[F("value")] = se;break;
//        case 10:sensorJSON[F("value")] = gla;break;
//        case 11:sensorJSON[F("value")] = glo;break;
              
        default:
            break;
        }
        
        doc[F("item")].add(sensorJSON);
    }

    doc[F("checksumkey")]="ASFDFJKL4857293845729834AX==";

    serializeJson(doc, hasilJSON);
    return hasilJSON; 
}

const char* waktuChr(char buffer[]) {
  char valueBuffer[10];
    ntpClient.update();

  strcpy_P(buffer, (const char *)F(""));
  strcat_P(buffer, (const char *)F("\"2020-09-28 "));
//  strcat_P(buffer, (const char *)ntpClient.getFormattedTime());
//  strcat_P(buffer, (const char *)F(":"));
//  strcat_P(buffer, (const char *)(ntpClient.getMinutes()));
//  strcat_P(buffer, (const char *)F(":"));
//  strcat_P(buffer, (const char *)(ntpClient.getSeconds()));
  strcat_P(buffer, (const char *)F("\""));

  return buffer;
}
