/*
      USE RESISTOR TO S.PORT FROM 5v-ARDUINO.

			  The default S.Port rate for polling a GPS is 1 hz.

			  Use hardware serial for GPS. Disconnect GPS when programming.

          Also note that to avoid interrupt conflict with the mentioned SoftwareSerial library you need to disable attitude (roll/pitch)
          sensing in the NazaDecoder library by uncommenting the following line in NazaDecoder.h file:
          //#define ATTITUDE_SENSING_DISABLED
*/

#include "FrSkySportTelemetry/FrSkySportSensor.h"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.h"
#include "FrSkySportTelemetry/FrSkySportTelemetry.h"
#include "FrSkySportTelemetry/FrSkySportPolling.h"

#include "FrSkySportTelemetry/FrSkySportSensor.cpp"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.cpp"
#include "FrSkySportTelemetry/FrSkySportTelemetry.cpp"
#include "FrSkySportTelemetry/FrSkySportPolling.cpp"
#include <SoftwareSerial.h>

#include "FrSkySportTelemetry/FrSkySportSensorGps.h"
#include "FrSkySportTelemetry/FrSkySportSensorFcs.h"

#include "FrSkySportTelemetry/FrSkySportSensorGps.cpp"
#include "FrSkySportTelemetry/FrSkySportSensorFcs.cpp"

FrSkySportSensorFcs sensor_fcs_main;
FrSkySportSensorGps sensor_gps;

FrSkySportTelemetry frsky_telemetry;

#include "TinyGPSplus/TinyGPS++.h"
#include "TinyGPSplus/TinyGPS++.cpp"
TinyGPSPlus gps_parser;

float gps_lat = 0;
float gps_lng = 0;
int16_t gps_alt; //+- m
int16_t gps_speed; // m/s
float    gps_course; // 90.23 Course over ground in degrees (0-359, 0 = north)
int16_t gps_y, gps_m, gps_d; //17, 4, 29,  Date (year - 2000, month, day)
int16_t gps_h, gps_i, gps_s; // 12,59, 59);   // Time (hour, minute, second) - will be affected by timezone setings in your radio
byte gps_sat_count = 0;

#define GPS_SAT_MIN_COUNT 1

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_1ms = 0L;

void setup() {
  delay(100);
  frsky_telemetry.begin(FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_12,  &sensor_gps, &sensor_fcs_main);
  delay(100);
  Serial.begin(57600);
  //TODO TEST below
  //delay(100);
  //Serial.println(F("$PMTK300,1000,0,0,0,0*1C")); //1Hz for MTK chipset!!!!!!
  //delay(100);
  //Serial.flush();
}

void loop() {
  while (Serial.available()) {
    gps_parser.encode(Serial.read());
  }

  if (gps_parser.satellites.isValid()) {
    gps_sat_count = gps_parser.satellites.value();
  }

  //if (gps_parser.satellites.isValid() && gps_sat_count >= GPS_SAT_MIN_COUNT) {

  if (gps_parser.location.isValid())  {
    gps_lat = gps_parser.location.lat();
    gps_lng = gps_parser.location.lng();
  }
  if (gps_parser.altitude.isValid()) {
    gps_alt = gps_parser.altitude.meters();
  }
  if (gps_parser.speed.isValid()) {
    gps_speed = gps_parser.speed.kmph() * 1000 / 3600; // m\s
  }
  if (gps_parser.course.isValid()) {
    gps_course = gps_parser.course.deg();
  }
  if (gps_parser.date.isValid()) {
    gps_y = gps_parser.date.year() - 2000;
    gps_m = gps_parser.date.month();
    gps_d = gps_parser.date.day();
  }
  if (gps_parser.time.isValid()) {
    gps_h = gps_parser.time.hour();
    gps_i = gps_parser.time.minute();
    gps_s = gps_parser.time.second();
  }
  // }


  TIMEMACHINE_process();

  //GPS_process();

}



