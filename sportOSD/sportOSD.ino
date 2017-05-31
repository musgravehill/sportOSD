
// UPLOAD FONT TABLE by mwOSD 1.7

#include "incl.h"


FrSkySportSensorXjt xjt; // Create XJT sensor with default ID
FrSkySportDecoder decoder; // Create decoder object without polling


float SYS_GPS_HOME_lat = 0.0f; //HOME TODO
float SYS_GPS_HOME_long = 0.0f; //HOME TODO

float SYS_GPS_NOW_lat = 0.0f;
float SYS_GPS_NOW_long = 0.0f;
int16_t SYS_GPS_HOME_dist = 0; //in metr
int16_t SYS_GPS_HOME_azimuth = 0; //0..360 degree ARROW TO HOME
int16_t SYS_GPS_NOW_course_over_ground = 0; //0..360 degree 0=North
int16_t SYS_GPS_NOW_speed = 0;
int16_t SYS_GPS_NOW_altitude = 0;
byte SYS_RSSI = 0;
float SYS_ACC_V = 0.0f;

byte SYS_GPS_countPositionSuccess = 0;
bool SYS_GPS_isHomeFixed = false; //when home position fixed and stored
byte SYS_GPS_MOCK_counter = 0;

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_250ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;


void setup() {
  MAX7456SETHARDWAREPORTS
  delay(1000);
  MAX7456Setup();
  SPORT_init();
#ifdef DEBUG || GPS_MOCK 
  Serial.begin(9600);
#endif  
}

void loop() {
  TIMEMACHINE_loop();
  OSD_render();
}



