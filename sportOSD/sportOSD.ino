
// UPLOAD FONT TABLE, run RC-mini\FRSKY-SPORT\Max7456WriteFONT

#include "libs.h"
#include "defs.h"

Max7456 osd;
FrSkySportSensorXjt xjt; // Create XJT sensor with default ID
FrSkySportDecoder decoder; // Create decoder object without polling


float SYS_GPS_HOME_lat = 57.55555; //HOME TODO
float SYS_GPS_HOME_long = 39.55555; //HOME TODO

float SYS_GPS_NOW_lat = 0.0f;
float SYS_GPS_NOW_long = 0.0f;
int16_t SYS_GPS_HOME_dist = 0; //in metr
int16_t SYS_GPS_HOME_azimuth = 0; //0..360 degree ARROW TO HOME
int16_t SYS_GPS_NOW_course_over_ground = 0; //0..360 degree 0=North
int16_t SYS_GPS_NOW_speed = 0;
int16_t SYS_GPS_NOW_altitude = 0;
byte SYS_RSSI = 0;
float SYS_ACC_V = 0.0f;

bool OSD_isRenderAllow = true; //false=>waiting for next Vsync interrupt event

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_250ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;

void setup() {
  OSD_init();
  SPORT_init();
  Serial.begin(9600);
  GPS_mock();
}

void loop() {
  TIMEMACHINE_loop();
  OSD_render();
}



