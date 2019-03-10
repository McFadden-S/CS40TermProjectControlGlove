/*
 * Purpose: Program for recieving sensor data from control glove for CS40 Term Project and sending 
 * it to communication program (cp) on computer written in java
 * By: Shae McFadden
 * Symbols: ! = error, # = continue, ? = wants response
 */

#include <SparkFun_ADS1015_Arduino_Library.h>
#include <Wire.h>

ADS1015 lsSensor; //sensor for left two fingers, Finger 2 Pinkie, Finger 1 Index
ADS1015 rsSensor; //sensor for right two fingers. Finger 2 Middle, Finger 1 Pointer
ADS1015 tSensor; //sensor fo thumb. Finger 1 Thumb 

void setup() {

  Wire.begin();
  Serial.begin(115200); //when changed for bluetooth set at 38400
  uint8_t incoming; // variable for data coming through serial
  
  if(lsSensor.begin(Wire, 100000, ADS1015_ADDRESS_GND) == false){
    Serial.print("!"); //notifies cp error with module
    while(1); //loop to stop program
  }//end of lsSensor start up
  else{
    Seral.print("#"); //notifies cp know this module is responding
  }//end of else module is working
  
  if(rsSensor.begin(Wire, 100000, ADS1015_ADDRESS_SDA) == false){
    Serial.print("!"); //notifies cp error with module
    while(1); //loop to stop program
  }//end of rsSensor start up
  else{
    Seral.print("#"); //notifies cp know this module is responding
  }//end of else module is working

  if(tSensor.begin(Wire, 100000, ADS1015_ADDRESS_SCL) == false){
    Serial.print("!"); //notifies cp error with module
    while(1); //loop to stop program
  }//end of tSensor start up
  else{
    Seral.print("#"); //notifies cp know this module is responding
  }//end of else module is working

  Serial.print("?"); //notifies cp waiting for input to end calibration

  do{
    lsSensor.calibrate();
    rsSensor.calibrate();
    tSensor.calibrate();

    if(Serial.availabe()){
      incoming = Serial.read();
    }
  }while(incoming != '#');

  Serial.print("#"); //notifies cp calibration is complete and program is ready for transmition
}//end of set up

void loop() {
  // put your main code here, to run repeatedly:

}
