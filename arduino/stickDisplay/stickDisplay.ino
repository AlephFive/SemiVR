//this program is for the arduino uno

#include <Adafruit_NeoPixel.h>


#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

String incomingString = "SXXXXXXXXSYYYYYYYYSZZZZZZZZSXXXXXXXXSYYYYYYYYSZZZZZZZZE";
//display change string format: Command + xxx + yyy + rgbhex + W value??

int ledIndex;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRBW + NEO_KHZ800);

void setup() {
  // begin serial to mega
   Serial.begin(9600);
  // begin strip settings
   strip.begin();
   strip.setPixelColor(2, 0, 0, 0, 255);
   strip.show();
   delay(1000);
   strip.clear();
   strip.show();
   
}

void loop() {
  // read serial buffer
  if (Serial.available() > 0) {
      incomingString = Serial.readStringUntil('E');
      
      //for debug purposes
      //Serial.print(incomingString + '\n');

      
      // update display
      if (incomingString.charAt(0) == 'R'){
        strip.show();
      }
      else if (incomingString.charAt(0) == 'T'){
        strip.setPixelColor(143, 0, 100, 0, 0);
        strip.show();
      }
      else if (incomingString.charAt(0) == 'B'){
        strip.setPixelColor(0, 0, 100, 0, 0);
        strip.show();
      }

      
      // if not
      else{
        ledIndex = incomingString.toInt();
        strip.setPixelColor(ledIndex, 0, 0, 0, 100);
      }
      incomingString = "";
  }
}

