#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

int width = 4;
int height = 4;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(width, height, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };


String incomingString = "X000000rrrgggbbbW";
//display change string format: Command + xxx + yyy + rgbhex + W value??

int x    = matrix.width();
int xC = 0;
int yC = 0;
// is there special data type for hex?

int W = 0;
String rgbHexStr = "";
int rgbHex = 0x00FF51; 
int r = 0;
int g = 0;
int b = 0;


void setup() {
  // begin serial
   Serial.begin(19200);
  // begin matrix settings
   matrix.begin();
   matrix.setTextWrap(false);
   matrix.setBrightness(40);
   matrix.setTextColor(colors[0]);
   matrix.setCursor(0, 0);
   
  // show startup image
   matrix.drawRect(0, 0, 3, 3, 0xFFDC00);
   matrix.show();
   delay(5000);
   
   matrix.fillScreen(0);
   matrix.show();
   
}

void loop() {
  // read serial buffer
  if (Serial.available() > 0) {
      //incomingByte = Serial.read();
      incomingString = Serial.readStringUntil('@');
      //Serial.print(incomingString);

      // if display needs changing
      //if (incomingString.charAt(0) == 'D'){
        //assign each part of string in order to convert to int
        //stuff incorrect here
        //xC = incomingString.substring(1,3).toInt();
        //yC = incomingString.substring(4,6).toInt();
        //rgbHex = incomingString.substring(7,7).toInt();
        //W = incomingString.substring(14,1).toInt();
        
        
        //updDisp();
        //incomingString = "";
      //}

      // update display
      if (incomingString.charAt(0) == 'R'){
        matrix.show();
        incomingString = "";
      }
      else if (incomingString.charAt(0) == 'A'){
        matrix.fillScreen(matrix.Color(255, 255, 255));
        matrix.show();
      }

      else if (incomingString.charAt(0) == 'T'){
        xC = incomingString.substring(1,4).toInt();
        
        yC = incomingString.substring(4,7).toInt();

        r = incomingString.substring(7,10).toInt();
        g = incomingString.substring(10,13).toInt();
        b = incomingString.substring(13,16).toInt();
        //rgbHexStr = "0x" + incomingString.substring(7,13);
        //const char str[6] = rgbHexStr.toCharArray();
        //rgbHex = strtoul(str[], 0, 16);
        
        
        incomingString = "";
        updDisp();
      }

      else if (incomingString.charAt(0) == 'C'){
        matrix.fillScreen(0);
        matrix.show();
      }

      // if not
      else{
        Serial.print("error");
      }
  }

}

void updDisp(){
  //not sure if direct hex works
  if(xC > width-1 || yC > height-1){
    matrix.fillScreen(matrix.Color(255, 0, 0));
    matrix.show();
  }
  else{
    matrix.drawPixel(xC, yC, matrix.Color(r, g, b));
  }
}

void updDispTest(){
  if(xC > width-1 || yC > height-1){
    matrix.fillScreen(matrix.Color(255, 0, 0));
    matrix.show();
  }
  else{
    matrix.drawPixel(xC, yC, rgbHex);
  }
}
