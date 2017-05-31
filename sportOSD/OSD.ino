
void OSD_render() {
  OSD_homeFixed();
  OSD_PARAMS();
  OSD_GPS();

  MAX7456_DrawScreen();
}

void OSD_PARAMS() {
  //acc volt
  SYS_ACC_V = 10.567888;
  ItoaPadded(SYS_ACC_V * 10, screenBuffer, 4, 3);   // 99.9
  screenBuffer[4] = SYM_VOLT;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_ACC_V));

  //RSSI
  SYS_RSSI = 120;
  ItoaUnPadded(SYS_RSSI, screenBuffer , 4, 4);
  screenBuffer[3] = SYM_RSSI;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_RSSI));

  //SPEED
  SYS_GPS_NOW_speed = 18;
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



uint16_t getPosition(uint16_t pos) {
  return pos & POS_MASK;
}

void displayAmperage(void)
{
  uint16_t amperage = 8;
  ItoaPadded(amperage, screenBuffer, 5, 4);     // 999.9 ampere max!
  screenBuffer[5] = SYM_AMP;
  screenBuffer[6] = SYM_ARROW_SOUTH;
  MAX7456_WriteString(screenBuffer, getPosition(LINE02));
}


void displayWatt(void) {
  uint16_t WhrPosition = 90;
  uint16_t watts = 123;
  ItoaPadded(watts, screenBuffer + 1 , 5, 5);
  screenBuffer[0] = SYM_BLANK;
  screenBuffer[5] = SYM_WATT;
  screenBuffer[6] = 0;
  MAX7456_WriteString(screenBuffer, WhrPosition);
}

//=============================HELPERS====================================================================================

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

