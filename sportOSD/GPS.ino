
//get gps_home first N times.
void GPS_home_position_fix() {
  if (!SYS_GPS_isHomeFixed && SYS_GPS_NOW_lat > 0 && SYS_GPS_NOW_long > 0) {
    SYS_GPS_countPositionSuccess++;
    SYS_GPS_HOME_lat = SYS_GPS_HOME_lat * 0.5f +  SYS_GPS_NOW_lat * 0.5f;
    SYS_GPS_HOME_long = SYS_GPS_HOME_long * 0.5f + SYS_GPS_NOW_long * 0.5f;
    SYS_GPS_HOME_altitude = SYS_GPS_HOME_altitude * 0.5f + SYS_GPS_NOW_altitude * 0.5f;
    if (SYS_GPS_countPositionSuccess > 32) {
      SYS_GPS_isHomeFixed = true;
    }
  }
}

void GPS_HOME_arrow_degree_calc() {
  GPS_HOME_arrow_degree = SYS_GPS_HOME_azimuth - SYS_GPS_NOW_cog;
  GPS_HOME_arrow_degree = (GPS_HOME_arrow_degree < 0) ? GPS_HOME_arrow_degree + 360 : GPS_HOME_arrow_degree;
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

  double dlon = radians(SYS_GPS_HOME_long - SYS_GPS_NOW_long);
  double a1 = sin(dlon) * cos(SYS_GPS_HOME_lat_rad);
  double a2 = sin(SYS_GPS_NOW_lat_rad) * cos(SYS_GPS_HOME_lat_rad) * cos(dlon);
  a2 = cos(SYS_GPS_NOW_lat_rad) * sin(SYS_GPS_HOME_lat_rad) - a2;
  a2 = atan2(a1, a2);
  if (a2 < 0.0)
  {
    a2 += TWO_PI;
  }
  SYS_GPS_HOME_azimuth = degrees(a2);
  SYS_GPS_HOME_azimuth = (SYS_GPS_HOME_azimuth < 0) ? 0 : SYS_GPS_HOME_azimuth;
  SYS_GPS_HOME_azimuth = (SYS_GPS_HOME_azimuth >= 360) ? 0 : SYS_GPS_HOME_azimuth;
}

#ifdef GPS_MOCK
void GPS_mock() {
  /*
    home 57.720138, 39.734516
    top (go to N) 348m 57.723255, 39.735084
    left (go to W) 25m 57.720069, 39.734000
    bottom (go to S) 43m 57.719726, 39.734472
    right (go to E) 600m 57.720548, 39.744558

    GPS MOCK N
    SYS_GPS_HOME_dist =348
    SYS_GPS_HOME_azimuth =185
    SYS_GPS_NOW_cog =0

    GPS MOCK W
    SYS_GPS_HOME_dist =31
    SYS_GPS_HOME_azimuth =75
    SYS_GPS_NOW_cog =0

    GPS MOCK S
    SYS_GPS_HOME_dist =45
    SYS_GPS_HOME_azimuth =3
    SYS_GPS_NOW_cog =0

    GPS MOCK E
    SYS_GPS_HOME_dist =45
    SYS_GPS_HOME_azimuth =3
    SYS_GPS_NOW_cog =0
  */
  SYS_MAIN_V = 10.567888;
  SYS_VID_V = 4.37;
  SYS_RSSI = 120;
  SYS_GPS_NOW_speed = 18;
  SYS_GPS_HOME_dist = 9999;
  SYS_GPS_NOW_altitude = 1200;

  SYS_GPS_HOME_lat = 57.720138;
  SYS_GPS_HOME_long = 39.734516;
  SYS_GPS_NOW_cog = random(0, 360);
  SYS_GPS_isHomeFixed = true;

  if (SYS_GPS_MOCK_counter < 64) {
    Serial.println(F("GPS MOCK N"));
    SYS_GPS_NOW_lat = 57.723255; //fly to N
    SYS_GPS_NOW_long =  39.735084;
  }
  else if (SYS_GPS_MOCK_counter > 64 && SYS_GPS_MOCK_counter < 128) {
    Serial.println(F("GPS MOCK W"));
    SYS_GPS_NOW_lat = 57.720069;
    SYS_GPS_NOW_long =  39.734000; //fly to W
  }
  else if (SYS_GPS_MOCK_counter > 128 && SYS_GPS_MOCK_counter < 192) {
    Serial.println(F("GPS MOCK S"));
    SYS_GPS_NOW_lat = 57.719726;  //to S
    SYS_GPS_NOW_long =  39.734472;
  }
  else {
    Serial.println(F("GPS MOCK E"));
    SYS_GPS_NOW_lat = 57.720548;//to E
    SYS_GPS_NOW_long =  39.744558;
  }
  Serial.print(F("SYS_GPS_HOME_dist=")); Serial.println(SYS_GPS_HOME_dist, DEC);
  Serial.print(F("SYS_GPS_HOME_azimuth=")); Serial.println(SYS_GPS_HOME_azimuth, DEC);
  Serial.print(F("SYS_GPS_NOW_cog=")); Serial.println(SYS_GPS_NOW_cog, DEC);
  Serial.print(F("GPS_HOME_arrow_degree=")); Serial.println(GPS_HOME_arrow_degree, DEC);
  Serial.println();
}
#endif
