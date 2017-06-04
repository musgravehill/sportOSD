void TIMEMACHINE_every_loop() {
  sport_decoder.decode(); //DECODE ON EVERY LOOP
}

void TIMEMACHINE_process() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_211ms) > 211L) {
    TIMEMACHINE_211ms();
    TIMEMACHINE_prevMicros_211ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_373ms) > 373L) {
    TIMEMACHINE_373ms();
    TIMEMACHINE_prevMicros_373ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_2203ms) > 2203L) {
    TIMEMACHINE_2203ms();
    TIMEMACHINE_prevMicros_2203ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_211ms() {
  SPORT_getData();
  GPS_update_home_distance_and_home_azimuth();
  GPS_HOME_arrow_degree_calc();
}

void TIMEMACHINE_373ms() {
  OSD_render();
#ifdef GPS_MOCK
  SYS_GPS_MOCK_counter++;
#endif
}

void  TIMEMACHINE_2203ms() {
#ifdef GPS_MOCK
  GPS_mock();
#endif
#ifdef DEBUG
  SYS_debug();
#endif
}

#ifdef DEBUG
void SYS_debug() {
  Serial.print(F("SYS_GPS_HOME_lat =")); Serial.println(SYS_GPS_HOME_lat, DEC);
  Serial.print(F("SYS_GPS_HOME_long =")); Serial.println(SYS_GPS_HOME_long, DEC);
  Serial.print(F("SYS_GPS_NOW_lat =")); Serial.println(SYS_GPS_NOW_lat, DEC);
  Serial.print(F("SYS_GPS_NOW_long =")); Serial.println(SYS_GPS_NOW_long, DEC);
  Serial.print(F("SYS_GPS_HOME_dist =")); Serial.println(SYS_GPS_HOME_dist, DEC);
  Serial.print(F("SYS_GPS_HOME_azimuth =")); Serial.println(SYS_GPS_HOME_azimuth, DEC);
  Serial.print(F("SYS_GPS_NOW_cog =")); Serial.println(SYS_GPS_NOW_cog, DEC);
  Serial.print(F("SYS_GPS_NOW_speed =")); Serial.println(SYS_GPS_NOW_speed, DEC);
  Serial.print(F("SYS_GPS_NOW_altitude =")); Serial.println(SYS_GPS_NOW_altitude, DEC);
  Serial.print(F("SYS_RSSI =")); Serial.println(SYS_RSSI, DEC);
  Serial.print(F("SYS_MAIN_V =")); Serial.println(SYS_MAIN_V, DEC);
  Serial.println();
  Serial.println();
}
#endif

