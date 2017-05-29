
// UPLOAD FONT TABLE, run RC-mini\FRSKY-SPORT\Max7456WriteFONT

#include "defs.h"

#include <SPI.h>  //<> => standart location
#include "max7456/max7456.h" //"" => local location
Max7456 osd;

#include "FrSkySportTelemetry/FrSkySportSensor.h"
#include "FrSkySportTelemetry/FrSkySportSensorXjt.h"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.h"
#include "FrSkySportTelemetry/FrSkySportDecoder.h"
#include <SoftwareSerial.h>

FrSkySportSensorXjt xjt;            // Create XJT sensor with default ID
FrSkySportDecoder decoder;        // Create decoder object without polling

static float GPS_scaleLonDown; // this is used to offset the shrinking longitude as we go towards the poles
float GPS_HOME_lat = 57.55555; //HOME
float GPS_HOME_long = 39.55555; //HOME
float GPS_NOW_lat;
float GPS_NOW_long;
uint16_t GPS_HOME_dist;
int16_t GPS_HOME_bearing;

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_250ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;

void setup() {
  pinMode(PIN_VSYNC, INPUT);

  
  SPI.begin();
  osd.init(6); //d10 or d6 on microMinimOSD ?
  osd.setDisplayOffsets(60, 18);
  osd.setBlinkParams(_8fields, _BT_BT);
  osd.activateOSD();

  // Configure the decoder serial port and sensors (remember to use & to specify a pointer to sensor)
  decoder.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_5, &xjt);
  Serial.begin(115200);
}

void loop() {

  //TODO VSYNC interrupt on d2 => re-draw OSD flag
  TIMEMACHINE_loop();
}



