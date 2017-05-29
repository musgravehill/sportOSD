
// UPLOAD FONT TABLE, run RC-mini\FRSKY-SPORT\Max7456WriteFONT

#include "libs.h"
#include "defs.h"

Max7456 osd;
FrSkySportSensorXjt xjt; // Create XJT sensor with default ID
FrSkySportDecoder decoder; // Create decoder object without polling

static float GPS_scaleLonDown; // this is used to offset the shrinking longitude as we go towards the poles
float GPS_HOME_lat = 57.55555; //HOME TODO
float GPS_HOME_long = 39.55555; //HOME TODO
float GPS_NOW_lat;
float GPS_NOW_long;
uint16_t GPS_HOME_dist; //in metr
int16_t GPS_HOME_bearing; //0..360 degree
bool OSD_isRenderAllow = true; //false=>waiting for next Vsync interrupt event

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_250ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;

void setup() {
  OSD_init();
  SPORT_init();
  Serial.begin(9600);
}

void loop() {
  TIMEMACHINE_loop();
  OSD_render();
}



