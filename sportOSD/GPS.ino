


void GPS_distance_and_azimuth() {
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

void GPS_test() {
  SYS_GPS_NOW_lat = 57.444444;
  SYS_GPS_NOW_long = 39.444444;
  GPS_distance_and_azimuth();
  Serial.println("");
  Serial.print("SYS_GPS_HOME_dist=");
  Serial.println(SYS_GPS_HOME_dist, DEC);
  Serial.print("SYS_GPS_HOME_bearingt=");
  Serial.println(SYS_GPS_HOME_azimuth, DEC);
}
