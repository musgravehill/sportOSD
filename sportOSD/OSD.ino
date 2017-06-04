
void OSD_render() {
  OSD_homeFixed();
  OSD_PARAMS();
  OSD_GPS();
  MAX7456_DrawScreen();
}

void OSD_PARAMS() {
  //main volt
  memset(screenBuffer, 0, sizeof(screenBuffer));
  ItoaUnPadded(SYS_MAIN_V * 100, screenBuffer, 6, 4); // 12.59
  screenBuffer[0] = SYM_MAIN_BATT;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_MAIN_V));
  //video volt
  memset(screenBuffer, 0, sizeof(screenBuffer));
  ItoaUnPadded(SYS_VID_V * 100, screenBuffer, 6, 4); // 12.59
  screenBuffer[0] = SYM_VID_BAT;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_VID_V));

  //RSSI
  memset(screenBuffer, 0, sizeof(screenBuffer));
  ItoaUnPadded(SYS_RSSI, screenBuffer , 4, 4);
  screenBuffer[3] = SYM_RSSI;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_RSSI));
  //SPEED
  memset(screenBuffer, 0, sizeof(screenBuffer));
  ItoaUnPadded(SYS_GPS_NOW_speed, screenBuffer , 3, 3);
  screenBuffer[2] = SYM_MS;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_SPEED));
}

void OSD_GPS() {
  int8_t pos_tmp;
  // ARROW to home
  memset(screenBuffer, 0, sizeof(screenBuffer));
  pos_tmp = (GPS_HOME_arrow_degree - 11) / 22;
  pos_tmp = (pos_tmp < 0 || pos_tmp > 15) ? 0 : pos_tmp;
  screenBuffer[0] = ARROW_SYMBOLS[pos_tmp];
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HOME_AZIMUTH));
  //dist to home
  memset(screenBuffer, 0, sizeof(screenBuffer));
  ItoaUnPadded(SYS_GPS_HOME_dist, screenBuffer , 5, 5);
  screenBuffer[4] = SYM_M;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HOME_DIST));
  //alt
  memset(screenBuffer, 0, sizeof(screenBuffer));
  ItoaUnPadded((SYS_GPS_NOW_altitude- SYS_GPS_HOME_altitude), screenBuffer , 5, 5);
  screenBuffer[4] = SYM_ALT;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_ALT));
  //heading compass center cursor
  memset(screenBuffer, 0, sizeof(screenBuffer));
  screenBuffer[0] = 0x76;
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HEADING_CURSOR));
  //compass
  pos_tmp = (SYS_GPS_NOW_cog - 11) / 22; //16 positions, 360\16 = 22 degree for each position
  pos_tmp = (pos_tmp < 0 || pos_tmp > 15) ? 0 : pos_tmp;
  int8_t arr_LR;
  for (int8_t i = -4; i <= 4; i++) {
    arr_LR = pos_tmp + i;
    if (arr_LR < 0) {
      arr_LR = 16 + arr_LR;
    }
    else if (arr_LR > 15) {
      arr_LR = arr_LR - 16;
    }
    screenBuffer[(i + 4)] = HEADING_SYMBOLS[arr_LR];
  }
  MAX7456_WriteString(screenBuffer, getPosition(OSD_POS_HEADING_COMPASS));

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

