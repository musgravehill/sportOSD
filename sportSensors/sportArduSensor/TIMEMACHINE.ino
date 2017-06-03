void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_111ms) > 111L) {
    TIMEMACHINE_111ms();
    TIMEMACHINE_prevMicros_111ms = TIMEMACHINE_currMillis;
  }
}


void TIMEMACHINE_111ms() {
  
}
