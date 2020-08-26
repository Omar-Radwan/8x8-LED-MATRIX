#include <SoftwareSerial.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

SoftwareSerial mySerial(5, 6); //(RXArduino=TxBluetooth), (TXArduino=RXBluetooth)

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 10

#define CLK_PIN   4
#define DATA_PIN  2
#define CS_PIN    3

// code variables

boolean staticWord = true;
char  message [100] = "TEXT!!";
int messageEnd =0;
String data = "";
int mode = 0 ; // type 0 append, type 1 clear and write new
boolean invertState = false;

uint8_t scrollSpeed = 40;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_RIGHT;
uint16_t scrollPause = 10; // in milliseconds

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


void setup(void)
{
 
  P.begin();
  P.setIntensity(0);
  mySerial.begin(9600);
  Serial.begin(9600);
    P.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    while (message[messageEnd]!='\0'){
       messageEnd++;
    }
  Serial.print(messageEnd);
}


void loop(void)
{
  if (!staticWord){
        if (P.displayAnimate())
  {
    P.displayReset();
  }
  }
  else {
    P.print(message);
  }
        bluetoothRead();
}


void bluetoothRead() {
  char x ;
  if (mySerial.available()) {
    x = mySerial.read();
    if (x == '/') {
      parseCommand();
    }
    else {
      parseString(x);
    }
  }


}

void parseCommand() {
  Serial.print("command start"); // debug

  String command = "" ;

  while (mySerial.available()) {
    char x = mySerial.read();
    command += x;
  }

  if (command.equals("clear")) {
     message[0] = '\0';
     messageEnd = 0 ; 
    
    P.displayClear();
    P.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);

    Serial.print("clear command"); // debug
  }

  else if (command.equals("mode_append")) {
    mode = 0;
  }

  else if (command.equals("mode_clear")) {
    mode = 1 ;
  }

  else if (command.equals("invert")) {
    invertState = !invertState;
    P.setInvert(invertState);
  }

  else if (command.equals("scroll")) {
    staticWord = false;
    scrollAlign = PA_LEFT;
  
     P.displayClear();
    P.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    
  }
  else if (command.equals("hold")){
        staticWord = true;
      scrollAlign = PA_RIGHT;
      P.displayClear();
      P.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  }

  else if (command.equals("si")){
     if (scrollSpeed<=21){
      scrollSpeed = 1;
     }
     else {
           scrollSpeed-=20;
     }

     P.setSpeed(scrollSpeed);
     Serial.print(scrollSpeed);
  }
    else if (command.equals("sd")){
     if (scrollSpeed>210){
      scrollSpeed = 210;
     }
     scrollSpeed+=20;
     P.setSpeed(scrollSpeed);
  }

  else if (command.equals("left")){
      scrollEffect = PA_SCROLL_LEFT;
          P.displayClear();
      P.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  }

    else if (command.equals("right")){
        scrollEffect = PA_SCROLL_RIGHT;
          P.displayClear();
      P.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  }

}

void parseString(char firstChar) {
  String tmp = "";
  tmp += firstChar;

  while (mySerial.available() > 0) {
    char x = mySerial.read();
    tmp += x;
  }

  if (mode == 0) {
    int i = 0;
    while (messageEnd<99&&i<tmp.length()){
            message[messageEnd++] = tmp.charAt(i++);
    }
    message[messageEnd] = '\0';
  }

  else if (mode == 1) {
    int i  = messageEnd = 0;

    while (messageEnd<99&&i<tmp.length()){
            message[messageEnd++] = tmp.charAt(i++);
    }
    message[messageEnd] = '\0';
  }
}
