void TIMEMACHINE_process() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_1ms) > 1L) {
    TIMEMACHINE_1ms();
    TIMEMACHINE_prevMicros_1ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_1ms() {
  SPORT_telemetry_send();
}
