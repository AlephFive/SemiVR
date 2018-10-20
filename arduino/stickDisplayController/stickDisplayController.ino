//this program is for the arduino mega
#include <Adafruit_NeoPixel.h>


#define PIN 6

int MAXBRIGHTNESS = 50;
String fromComputer = "X000000rrrgggbbbW";
String fromPOS1 = "";
String fromPOS2 = "";
String indexStr = "";
String percentStr = "";
int sepIndex = 0;

String POS = "";
bool POS1Available = false;
bool POS2Available = false;

bool clearstrip = false;


//neopixel related
int ledIndex;
int ledPercent;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(144, PIN, NEO_GRBW + NEO_KHZ800);


void setup() {
  //begin serial to computer
  Serial.begin(9600);
  //begin serial to top Position sensor 
  Serial1.begin(9600);
  //begin serial to bottom Position sensor 
  Serial2.begin(9600);
  //begin serial to stickDisplay
  //Serial3.begin(9600);
  Serial.setTimeout(10);
  Serial1.setTimeout(10);
  Serial2.setTimeout(10);
  //strip init
   strip.begin();
   strip.setPixelColor(2, 0, 0, 0, 255);
   strip.show();
   delay(1000);
   strip.clear();
   strip.show();
  
}

void loop() {
  //signal from computer
  if (Serial.available() > 0) {
      fromComputer = Serial.readStringUntil('E');
      //forward to arduino uno
      //Serial.println(fromComputer);
      /*
      Serial3.print(fromComputer + "E");
      fromComputer = "";
      */
      if (fromComputer.charAt(0) == 'R'){
        strip.show();
        clearstrip = true;
        //Serial.println("refresh");
      }
      else if(fromComputer == "\n"){
        //ignore newlinechar
      }
      else{
        if(clearstrip){
          clearstrip = false;
          strip.clear();
          //Serial.println("clearing strip");
        }
        
        sepIndex = fromComputer.indexOf('P');
        //Serial.println("SepIndex" + sepIndex);
        indexStr = fromComputer.substring(0, sepIndex);
        //Serial.println("ledindexstr" + indexStr);
        percentStr = fromComputer.substring(sepIndex + 1);
       // Serial.println("percentstr" + percentStr);
        
        ledIndex = indexStr.toInt();
        //Serial.print("ledindexINT");
        //Serial.println(ledIndex);
        ledPercent = percentStr.toInt();
        //Serial.print("ledpercentINT");
        //Serial.println(ledPercent);
        

        int rounded = round((ledPercent*MAXBRIGHTNESS)/100);
        //Serial.print("rounded");
        //Serial.println(rounded);
        
        strip.setPixelColor(ledIndex, 0, 0, 0, rounded);
      }
      fromComputer = "";
  }

  
  //signal from top POS 
  if (Serial1.available() > 0) {
      //read string
      fromPOS1 = Serial1.readStringUntil('E');
      
      if(fromPOS1.charAt(0) == 'F'){
        POS1Available = false;
        //strip.setPixelColor(143, 20, 0, 0, 0);
      }
      else if(fromPOS1.charAt(0) == 'X'){
        //strip.setPixelColor(143, 0, 20, 0, 0);
        POS1Available = true;
      }
  }

  if(Serial2.available() > 0) {
      fromPOS2 = Serial1.readStringUntil('E');
        
      if(fromPOS2.charAt(0) == 'F'){
        POS2Available = false;
        //strip.setPixelColor(0, 20, 0, 0, 0);
      }
      else if(fromPOS2.charAt(0) == 'X'){
        //strip.setPixelColor(0, 0, 20, 0, 0);
        POS2Available = true;
      }
  }

  //If both are available
  if(POS2Available && POS1Available){
      Serial.print(fromPOS1 + "D" + fromPOS2 + "E");
      POS2Available = false;
      POS1Available = false;
  }
  
}


