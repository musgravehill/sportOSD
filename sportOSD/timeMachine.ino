void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_333ms) > 333L) {
    TIMEMACHINE_333ms();
    TIMEMACHINE_prevMicros_333ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_1000ms) > 1000L) {
    TIMEMACHINE_1000ms();
    TIMEMACHINE_prevMicros_1000ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_333ms() {
  SPORT_getData();
#ifdef GPS_MOCK
  SYS_GPS_MOCK_counter++;
#endif
}

void  TIMEMACHINE_1000ms() {
  GPS_update_home_distance_and_home_azimuth();
  GPS_HOME_arrow_degree_calc();
#ifdef GPS_MOCK
  GPS_mock();
#endif
#ifdef DEBUG
  SPORT_debug();
  SYS_debug();
#endif
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
  Serial.print("SYS_GPS_NOW_cog ="); Serial.println(SYS_GPS_NOW_cog, DEC);
  Serial.print("SYS_GPS_NOW_speed ="); Serial.println(SYS_GPS_NOW_speed, DEC);
  Serial.print("SYS_GPS_NOW_altitude ="); Serial.println(SYS_GPS_NOW_altitude, DEC);
  Serial.print("SYS_RSSI ="); Serial.println(SYS_RSSI, DEC);
  Serial.print("SYS_MAIN_V ="); Serial.println(SYS_MAIN_V, DEC);
  Serial.println();
  Serial.println();
}

