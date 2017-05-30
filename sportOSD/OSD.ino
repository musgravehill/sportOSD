
void OSD_render() {
  OSD_homeFixed();



  
  MAX7456_DrawScreen();
}

void OSD_homeFixed() {
  if (!SYS_GPS_isHomeFixed) {
    MAX7456_WriteString("GPS HOME", getPosition(OSD_POS_ALERT_GPS_NOT));
  }
  displayAmperage();
}

/*
  int16_t SYS_GPS_HOME_dist = 0; //in metr
  int16_t SYS_GPS_HOME_azimuth = 0; //0..360 degree ARROW TO HOME
  int16_t SYS_GPS_NOW_course_over_ground = 0; //0..360 degree 0=North
  int16_t SYS_GPS_NOW_speed = 0;
  int16_t SYS_GPS_NOW_altitude = 0;
  byte SYS_RSSI = 0;
  float SYS_ACC_V = 0.0f;
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

