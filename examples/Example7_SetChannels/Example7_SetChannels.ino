/*
  Setting Thermocouple Channel with the MCP9600 Thermocouple Amplifier
  By: Sarah Elma
  Date: Feb 14, 2026

  The MCP9604 is identical to the other MCP960X variants but supports up to 4 input channels.
  I've made minor modifications to the sparkfun library to allow the thermocouple channel to be
  selected. Since a single ADC is used for all channels, you need to select the channel each time
  before reading.

  Serial.print it out at 115200 baud to serial monitor.
*/


#include <SparkFun_MCP9600.h>
MCP9600 tempSensor;
Thermocouple_Type type = TYPE_T; //the type of thermocouple to change to!

void setup(){
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(100000);
    tempSensor.begin();       // Uses the default address (0x60) for SparkFun Thermocouple Amplifier
    //tempSensor.begin(0x66); // Default address (0x66) for SparkX Thermocouple Amplifier

    //check that the sensor is connected
    if(tempSensor.isConnected()){
        Serial.println("Device will acknowledge!");
    }
    else {
        Serial.println("Device did not acknowledge! Freezing.");
        while(1); //hang forever
    }

    //check that the Device ID is correct
    if(tempSensor.checkDeviceID()){
        Serial.println("Device ID is correct!");        
    }
    else {
        Serial.println("Device ID is not correct! Freezing.");
        while(1);
    }

    //change the thermocouple type being used
    Serial.println("Setting Thermocouple Type!");
    tempSensor.setThermocoupleType(type);

    //make sure the type was set correctly!
    if(tempSensor.getThermocoupleType() == type){
        Serial.println("Thermocouple Type set sucessfully!");
    }

    else{
        Serial.println("Setting Thermocouple Type failed!");
    }
}

void loop(){ //print the thermocouple, ambient and delta temperatures every 200ms
    if(tempSensor.available()){
        for (int i = 0; i < 4; i++){
          tempSensor.setChannel(static_cast<Channel_Select>(i));
          Serial.print("Channel ");
          Serial.print(i+1);
          Serial.print(" -- Thermocouple: ");
          Serial.print(tempSensor.getThermocoupleTemp());
          Serial.print(" °C   Ambient: ");
          Serial.print(tempSensor.getAmbientTemp());
          Serial.print(" °C   Temperature Delta: ");
          Serial.print(tempSensor.getTempDelta());
          Serial.print(" °C");
          Serial.println();
          delay(5);
        }
        Serial.println();
        delay(20);        
    }
}