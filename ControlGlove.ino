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
ADS1015 Sensors[] = {lsSensor, rsSensor, tSensor};
int nOfs = 3; //number of sensors

void setup() {

  Wire.begin();
  Serial.begin(115200); //when changed for bluetooth set at 38400
  
  if(Sensors[0].begin(Wire, 100000, ADS1015_ADDRESS_GND) == false){
    Serial.print("!"); //notifies cp error with module
    while(1); //loop to stop program
  }//end of lsSensor start up
  else{
    Serial.print("#"); //notifies cp know this module is responding
  }//end of else module is working
  
  if(Sensors[1].begin(Wire, 100000, ADS1015_ADDRESS_SDA) == false){
    Serial.print("!"); //notifies cp error with module
    while(1); //loop to stop program
  }//end of rsSensor start up
  else{
    Serial.print("#"); //notifies cp know this module is responding
  }//end of else module is working

  if(Sensors[2].begin(Wire, 100000, ADS1015_ADDRESS_SCL) == false){
    Serial.print("!"); //notifies cp error with module
    while(1); //loop to stop program
  }//end of tSensor start up
  else{
    Serial.print("#"); //notifies cp know this module is responding
  }//end of else module is working

  calibrateSensors();
  //checkCalibration();
  
  Serial.print("#"); //notifies cp calibration is complete and program is ready for transmition
}//end of set up

void loop() {
  // put your main code here, to run repeatedly:
  
}

void calibrateSensors(){
  uint8_t incoming = 0; // variable for data coming through serial
  
  for(int i = 0; i < nOfs; i++){
    Serial.print("?"); //notifies cp waiting for input to end calibration of module 1

    do{
      Sensors[i].calibrate();

      if(Serial.available()){
        incoming = Serial.read();
      }
    }while(incoming != '#');
    incoming = 0;
  }
}

void checkCalibration(){
  //Print calibration data
  Serial.println();
  for (int s = 0; s < nOfs; s++){
    Serial.print("Module ");
    Serial.println(s+1);
    for (int f = 0; f < 2; f++){
      Serial.print("Finger ");
      Serial.print(f+1);
      Serial.print(": ");
      for (int hiLo = 0; hiLo < 2; hiLo++){
        switch (hiLo){
          case 0:
            Serial.print("Low: ");
            Serial.print(Sensors[s].getCalibration(f, hiLo));
            break;
          case 1:
            Serial.print(" High: ");
            Serial.print(Sensors[s].getCalibration(f, hiLo));
            break;
        }//end of switch
      }//end of high low for loop
      Serial.println();
    }//end of channel for loop
  }//end of sensor for loop
}//end of check calibration
