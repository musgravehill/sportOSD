

//#define DEBUG true

#define PIN_SPORT_IN  FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_5

#define DECIMAL '.' 
#define USE_VSYNC   // Removes sparklies as updates screen during blanking time period. 
#define MAX7456ENABLE    PORTD&=B10111111;
#define MAX7456DISABLE   PORTD|=B01000000;
#define MAX7456SETHARDWAREPORTS  DDRB|=B00101100;DDRB&=B11101111;DDRD|=B01000000;DDRD&=B11111011;
#define MAX7456HWRESET   PORTB&=B11111011;delay(100);PORTB|=B00000100;
