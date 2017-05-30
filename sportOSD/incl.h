#include <SPI.h>  //<> => standart location

#include "defs.h"

#include "FrSkySportTelemetry/FrSkySportSensor.h"
#include "FrSkySportTelemetry/FrSkySportSensorXjt.h"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.h"
#include "FrSkySportTelemetry/FrSkySportDecoder.h"

#include "FrSkySportTelemetry/FrSkySportSensor.cpp"
#include "FrSkySportTelemetry/FrSkySportSensorXjt.cpp"
#include "FrSkySportTelemetry/FrSkySportSingleWireSerial.cpp"
#include "FrSkySportTelemetry/FrSkySportDecoder.cpp"
#include <SoftwareSerial.h>

#include <avr/pgmspace.h>
#undef PROGMEM
#define PROGMEM __attribute__(( section(".progmem.data") ))
//#include <EEPROM.h>
#include <util/atomic.h> // For ATOMIC_BLOCK

#include "symbols.h"
#include "GlobalVariables.h"
#include "math.h"
