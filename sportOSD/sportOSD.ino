
// UPLOAD FONT TABLE by mwOSD 1.7

//TODO
// 0. avg-filter for alt, cog, home-azimuth, gps-lat\long
// gps-lat\long avg-filter for HOME_POS init!!!!!
// SYS_VID_V  add sensor

#include "incl.h"

FrSkySportSensorXjt xjt; // Create XJT sensor with default ID
FrSkySportDecoder decoder; // Create decoder object WITH POLLING


float SYS_GPS_HOME_lat = 0.0f; //HOME TODO
float SYS_GPS_HOME_long = 0.0f; //HOME TODO
int16_t SYS_GPS_HOME_altitude = 0.0f; //HOME TODO

float SYS_GPS_NOW_lat = 0.0f;
float SYS_GPS_NOW_long = 0.0f;
int16_t SYS_GPS_HOME_dist = 0; //in metr
int16_t SYS_GPS_HOME_azimuth = 0; //0..360 degree ARROW TO HOME
int16_t SYS_GPS_NOW_cog = 0; //0..360 degree 0=North
int16_t SYS_GPS_NOW_speed = 0;
int16_t SYS_GPS_NOW_altitude = 0; //may be minus negative
byte SYS_RSSI = 0;
float SYS_MAIN_V = 0.0f;
float SYS_VID_V = 0.0f;
int16_t GPS_HOME_arrow_degree = 0; //0=to screen top, 180= to screen bottom

byte SYS_GPS_countPositionSuccess = 0;
bool SYS_GPS_isHomeFixed = false; //when home position fixed and stored


//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_333ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;


void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
#ifdef GPS_MOCK
  Serial.begin(9600);
#endif
  delay(100);
  SPORT_init();
  delay(100);
  MAX7456SETHARDWAREPORTS
  delay(100);
  MAX7456Setup();
}

void loop() {
  SPORT_getData();
  TIMEMACHINE_loop();  
}



