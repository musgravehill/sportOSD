
//get gps 500 times. If 500 times is NOTNULL, then save home position && set SYS_GPS_isHomeFixed = true
void GPS_home_position_fix() {
  if (!SYS_GPS_isHomeFixed && SYS_GPS_NOW_lat > 0 && SYS_GPS_NOW_long > 0) {
    SYS_GPS_countPositionSuccess++;
    if (SYS_GPS_countPositionSuccess > 500) {
      SYS_GPS_HOME_lat =  SYS_GPS_NOW_lat;
      SYS_GPS_HOME_long = SYS_GPS_NOW_long;
      SYS_GPS_isHomeFixed = true;
    }
  }
}

void GPS_update_home_distance_and_home_azimuth() {
  // returns distance in meters between two positions, both specified
  // as signed decimal-degrees latitude and longitude. Uses great-circle
  // distance computation for hypothetical sphere of radius 6372795 meters.
  // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
  // Courtesy of Maarten Lamers
  double SYS_GPS_HOME_lat_rad = radians(SYS_GPS_HOME_lat);
  double SYS_GPS_NOW_lat_rad = radians(SYS_GPS_NOW_lat);
  double delta = radians(SYS_GPS_HOME_long - SYS_GPS_NOW_long);
  double sdlong = sin(delta);
  double cdlong = cos(delta);
  double sSYS_GPS_HOME_lat = sin(SYS_GPS_HOME_lat_rad);
  double cSYS_GPS_HOME_lat = cos(SYS_GPS_HOME_lat_rad);
  double sSYS_GPS_NOW_lat = sin(SYS_GPS_NOW_lat_rad);
  double cSYS_GPS_NOW_lat = cos(SYS_GPS_NOW_lat_rad);
  delta = (cSYS_GPS_HOME_lat * sSYS_GPS_NOW_lat) - (sSYS_GPS_HOME_lat * cSYS_GPS_NOW_lat * cdlong);
  delta = sq(delta);
  delta += sq(cSYS_GPS_NOW_lat * sdlong);
  delta = sqrt(delta);
  double denom = (sSYS_GPS_HOME_lat * sSYS_GPS_NOW_lat) + (cSYS_GPS_HOME_lat * cSYS_GPS_NOW_lat * cdlong);
  delta = atan2(delta, denom);
  SYS_GPS_HOME_dist = delta * 6372795;

  double dlon = radians(SYS_GPS_NOW_long - SYS_GPS_HOME_long);
  double a1 = sin(dlon) * cos(SYS_GPS_NOW_lat_rad);
  double a2 = sin(SYS_GPS_HOME_lat_rad) * cos(SYS_GPS_NOW_lat_rad) * cos(dlon);
  a2 = cos(SYS_GPS_HOME_lat_rad) * sin(SYS_GPS_NOW_lat_rad) - a2;
  a2 = atan2(a1, a2);
  if (a2 < 0.0)
  {
    a2 += TWO_PI;
  }
  SYS_GPS_HOME_azimuth = degrees(a2);
}

#ifdef GPS_MOCK
void GPS_mock() {
  /*
    home 57.720138, 39.734516
    top (go to N) 348m 57.723255, 39.735084
    left (go to W) 25m 57.720069, 39.734000
    bottom (go to S) 43m 57.719726, 39.734472
    right (go to E) 600m 57.720548, 39.744558

  */
  SYS_GPS_HOME_lat = 57.720138;
  SYS_GPS_HOME_long = 39.734516;
  SYS_GPS_isHomeFixed = true;

  Serial.println(F("GPS_mock() is ACTIVE"));

  if (SYS_GPS_MOCK_counter < 64) {
    Serial.println(F("fly to N"));
    SYS_GPS_NOW_lat = 57.723255; //fly to N
    SYS_GPS_NOW_long =  39.735084;
  }
  else if (SYS_GPS_MOCK_counter > 64 && SYS_GPS_MOCK_counter < 128) {
    Serial.println(F("fly to W"));
    SYS_GPS_NOW_lat = 57.720069;
    SYS_GPS_NOW_long =  39.734000; //fly to W
  }
  else if (SYS_GPS_MOCK_counter > 128 && SYS_GPS_MOCK_counter < 192) {
    Serial.println(F("fly to S"));
    SYS_GPS_NOW_lat = 57.719726;  //to S
    SYS_GPS_NOW_long =  39.734472;
  }
  else {
    Serial.println(F("fly to E"));
    SYS_GPS_NOW_lat = 57.720548;//to E
    SYS_GPS_NOW_long =  39.744558;
  }
  Serial.println(SYS_GPS_MOCK_counter, DEC);
  Serial.print(F("SYS_GPS_HOME_dist =")); Serial.println(SYS_GPS_HOME_dist, DEC);
  Serial.print(F("SYS_GPS_HOME_azimuth =")); Serial.println(SYS_GPS_HOME_azimuth, DEC);
  Serial.print(F("SYS_GPS_NOW_course_over_ground =")); Serial.println(SYS_GPS_NOW_course_over_ground, DEC);
}
#endif
