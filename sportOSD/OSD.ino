
void OSD_render() {
  OSD_homeFixed();
  OSD_PARAMS();
  OSD_GPS();
  MAX7456_DrawScreen();
}

void OSD_PARAMS() {
  //acc volt
  ItoaUnPadded(SYS_ACC_V * 100, screenBuffer, 5, 3); // 12.59
  screenBuffer[5] = SYM_VOLT;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_ACC_V));
  //SYM_MAIN_BATT
  //SYM_VID_BAT

  //RSSI
  ItoaUnPadded(SYS_RSSI, screenBuffer , 4, 4);
  screenBuffer[3] = SYM_RSSI;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_RSSI));
  //SPEED
  ItoaUnPadded(SYS_GPS_NOW_speed, screenBuffer , 3, 3);
  screenBuffer[2] = SYM_MS;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_SPEED));
}

void OSD_GPS() {
  // ARROW to home
  byte home_arrow_pos = (GPS_HOME_arrow_degree - 11) / 22;
  home_arrow_pos = (home_arrow_pos < 0 || home_arrow_pos > 15) ? 0 : home_arrow_pos;
  memset(screenBuffer, 0, sizeof(screenBuffer));
  screenBuffer[0] = ARROW_SYMBOLS[home_arrow_pos];
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HOME_AZIMUTH));
  //dist to home
  ItoaUnPadded(SYS_GPS_HOME_dist, screenBuffer , 5, 5);
  screenBuffer[4] = SYM_M;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HOME_DIST));
  //alt
  ItoaUnPadded(SYS_GPS_NOW_altitude, screenBuffer , 5, 5);
  screenBuffer[4] = SYM_ALT;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_ALT));
  //heading compass
  memset(screenBuffer, 0, sizeof(screenBuffer));
  screenBuffer[0] = 0x76;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HEADING_CURSOR));

  /*
    OSD_POS_HEADING_BLOCK
    SYM_HEADING_N
    SYM_HEADING_S
    SYM_HEADING_E
    SYM_HEADING_W
    SYM_HEADING_DIVIDED_LINE
    SYM_HEADING_LINE
  */
}

void OSD_homeFixed() {
  if (!SYS_GPS_isHomeFixed) {
    MAX7456_WriteString("GPS HOME WAIT...", getPosition(OSD_POS_ALERT_GPS_NOT));
  }
}

/*
  int16_t SYS_GPS_HOME_dist = 0; //in metr
  int16_t SYS_GPS_HOME_azimuth = 0; //0..360 degree ARROW TO HOME
  int16_t SYS_GPS_NOW_cog = 0; //0..360 degree 0=North
  int16_t SYS_GPS_NOW_speed = 0;
  int16_t SYS_GPS_NOW_altitude = 0;

*/





//=============================HELPERS====================================================================================
uint16_t getPosition(uint16_t pos) {
  return pos & POS_MASK;
}

char *ItoaPadded(int val, char *str, uint8_t bytes, uint8_t decimalpos)  {
  // Val to convert
  // Return String
  // Length
  // Decimal position
  uint8_t neg = 0;
  if (val < 0) {
    neg = 1;
    val = -val;
  }

  str[bytes] = 0;
  for (;;) {
    if (bytes == decimalpos) {
      str[--bytes] = DECIMAL;
      decimalpos = 0;
    }
    str[--bytes] = '0' + (val % 10);
    val = val / 10;
    if (bytes == 0 || (decimalpos == 0 && val == 0))
      break;
  }

  if (neg && bytes > 0)
    str[--bytes] = '-';

  while (bytes != 0)
    str[--bytes] = ' ';
  return str;
}

char *ItoaUnPadded(int val, char *str, uint8_t bytes, uint8_t decimalpos)  {
  // Val to convert
  // Return String
  // Length
  // Decimal position
  uint8_t neg = 0;
  if (val < 0) {
    neg = 1;
    val = -val;
  }

  str[bytes] = 0;
  for (;;) {
    if (bytes == decimalpos) {
      str[--bytes] = DECIMAL;
      decimalpos = 0;
    }
    str[--bytes] = '0' + (val % 10);
    val = val / 10;
    if (bytes == 0 || (decimalpos == 0 && val == 0))
      break;
  }

  if (neg && bytes > 0)
    str[--bytes] = '-';

  while (bytes != 0)
    str[--bytes] = ' ';
  return str;
}

