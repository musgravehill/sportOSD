#include "Arduino.h"
#include <SPI.h>  //<> => standart location
#include "max7456/max7456.h" //"" => local location
#include "max7456/max7456.cpp"
#include "max7456/max7456registers.h"

Max7456 osd;
unsigned long counter = 0;
byte tab[] = {0xC8, 0xC9};

void setup()
{
  SPI.begin();

  osd.init(6);
  osd.setDisplayOffsets(60, 18);
  osd.setBlinkParams(_8fields, _BT_BT);

  osd.activateOSD();


  int posX = 1; int posY = 1;
  for (int i = 0 ; i <= 0xff; i++)  {
    osd.printMax7456Char(i, posX, posY, true);
    posX++;
    if (posX > 20) {
      posX = 1;
      posY++;
    }
  }

  //osd.printMax7456Char(0x01,0,1);
  //osd.print("GPS process Hello world :)",1,3);
  //osd.print("Current Arduino time :",1,4);

  //osd.printMax7456Char(0xD1,9,6,true);
  //osd.print("00'00\"",10,6);
  //osd.printMax7456Chars(tab,2,12,7);


  //base time = 160ms,time on = time off.
}


void loop()
{


  counter = millis()/1000;

  //osd.print(int(counter/60),10,6,2,0,false,true);
  //osd.print(int(counter%60),13,6,2,0,false,true);

  delay(100);
}
