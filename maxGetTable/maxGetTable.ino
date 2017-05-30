#include "Arduino.h"
#include <SPI.h>  //<> => standart location
#include "max7456/max7456.h" //"" => local location
#include "max7456/max7456.cpp"
#include "max7456/max7456registers.h"

Max7456 osd;
void setup()
{
  charact currentChar;
  char number[]="000";
  SPI.begin();
  Serial.begin(9600);
  osd.init(6);
  osd.activateOSD(false); // Deactivate osd display.
  for(int i = 0 ; i <= 0xff;i++)
  {
    Serial.println();
    Serial.print("inserting ");
    dtostrf(i,3,0,number);
    Serial.print(number);
    Serial.print(" / 255 -> "); 
    osd.getCharacter(currentChar,i&0xF0, i&0xF0);
    Serial.print(*currentChar);
  }
}


void loop()
{

}
