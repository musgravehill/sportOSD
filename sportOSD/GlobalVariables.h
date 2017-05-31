
//#define DEBUG true
#define GPS_MOCK true

#define PIN_SPORT_IN  FrSkySportSingleWireSerial::SOFT_SERIAL_PIN_3 //where PAL jumper

#ifdef GPS_MOCK
byte SYS_GPS_MOCK_counter = 0;
#endif

#define DECIMAL '.'

#define USE_VSYNC   // Removes sparklies as updates screen during blanking time period. 
#define MAX7456ENABLE    PORTD&=B10111111;
#define MAX7456DISABLE   PORTD|=B01000000;
#define MAX7456SETHARDWAREPORTS  DDRB|=B00101100;DDRB&=B11101111;DDRD|=B01000000;DDRD&=B11111011;
#define MAX7456HWRESET   PORTB&=B11111011;delay(100);PORTB|=B00000100;

char screen[480];          // Main screen ram for MAX7456
char screenBuffer[20];     // MAX7456

#define bitISSET(bits, off) (bits[(off)/8] & (1 << ((off) % 8)))
#define bitISCLR(bits, off) (!bitISSET(bits, off))
#define bitCLR(bits, off) { bits[(off)/8] &= ~(1 << ((off) % 8)); }
#define bitSET(bits, off) { bits[(off)/8] |= ~(1 << ((off) % 8)); }

#define POS_MASK        0x01FF
#define PAL_MASK        0x0003
#define PAL_SHFT             9
#define DISPLAY_MASK    0xC000
#define DISPLAY_ALWAYS  0xC000
#define DISPLAY_NEVER   0x0000
#define DISPLAY_COND    0x4000
#define DISPLAY_MIN_OFF     0x8000

#define POS(pos, pal_off, disp)  (((pos)&POS_MASK)|((pal_off)<<PAL_SHFT)|(disp))
#if defined SHIFTDOWN
#define TOPSHIFT        LINE
#else
#define TOPSHIFT        0
#endif



uint8_t fontMode = 0;
uint8_t fontData[54];



