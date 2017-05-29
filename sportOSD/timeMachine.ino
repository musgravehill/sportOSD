void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_250ms) > 250L) {
    TIMEMACHINE_250ms();
    TIMEMACHINE_prevMicros_250ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_1000ms) > 1000L) {
    TIMEMACHINE_1000ms();
    TIMEMACHINE_prevMicros_1000ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_250ms() {
  SPORT_getData();
}

void  TIMEMACHINE_1000ms() {
  //SPORT_debug();
  //SYS_debug();
}


void SYS_debug() {
  Serial.println();
  Serial.println();
  Serial.println("----------------SYS-------------------");
  Serial.print("SYS_GPS_HOME_lat ="); Serial.println(SYS_GPS_HOME_lat, DEC);
  Serial.print("SYS_GPS_HOME_long ="); Serial.println(SYS_GPS_HOME_long, DEC);
  Serial.print("SYS_GPS_NOW_lat ="); Serial.println(SYS_GPS_NOW_lat, DEC);
  Serial.print("SYS_GPS_NOW_long ="); Serial.println(SYS_GPS_NOW_long, DEC);
  Serial.print("SYS_GPS_HOME_dist ="); Serial.println(SYS_GPS_HOME_dist, DEC);
  Serial.print("SYS_GPS_HOME_azimuth ="); Serial.println(SYS_GPS_HOME_azimuth, DEC);
  Serial.print("SYS_GPS_NOW_course_over_ground ="); Serial.println(SYS_GPS_NOW_course_over_ground, DEC);
  Serial.print("SYS_GPS_NOW_speed ="); Serial.println(SYS_GPS_NOW_speed, DEC);
  Serial.print("SYS_GPS_NOW_altitude ="); Serial.println(SYS_GPS_NOW_altitude, DEC);
  Serial.print("SYS_RSSI ="); Serial.println(SYS_RSSI, DEC);
  Serial.print("SYS_ACC_V ="); Serial.println(SYS_ACC_V, DEC);
  Serial.println();
  Serial.println();
}
