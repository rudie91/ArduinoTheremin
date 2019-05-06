//VL53L0X distance sensor(laser) library 
//  credit:
// "pololu/vl53l0x-arduino." Internet: https://github.com/pololu/vl53l0x-arduino
// Jun. 27, 2017 [Dec. 2, 2017].
//Modified by: Yoon mo Yang
#include <Wire.h>
#include <VL53L0X.h>
//Initialize VL53L0X (library for VL53L0X) variable as laser_sesor
VL53L0X laser_sensor;
//Long_Range mode
#define LONG_RANGE

//Ultrasonic sound sensor library: HC-SR04
//credit:
//T. Eckel. “NewPing Library for Arduino.” Internet: https://playground.arduino.cc/Code/NewPing, 
//Jul. 30, 2016 [Dec. 2, 2017].
//Modified by: Yoon mo Yang
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 60 //Maximum distance : 60cm 
//Initialize NewPing (library for HC-SR04) variable as ultrasonic
NewPing ultrasonic(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//Variables for HC-SR04
long distance,temp;

void setup() 
{
  Serial.begin(9600);
  
  // VL53L0X part 
  // wait until serial port opens for Arduino
  Wire.begin();
  //initialize the sensor
  laser_sensor.init();
  laser_sensor.setTimeout(500);
  //Change the signal rate, pulse preiod range to use Long-Range mode
  #if defined LONG_RANGE
    laser_sensor.setSignalRateLimit(0.1);
    laser_sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
    laser_sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  #endif
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  laser_sensor.startContinuous();
  
}

void loop() 
{
  //HC-SR04 data reading
  delay(50); // Wait 50ms between pings (about 20 pings/sec).
  distance = ultrasonic.ping_cm();//read the distance
  //Seems like Hc-Sr04's maximum distance is not 400cm but around 60cm.
  if(distance >=60 || distance <= 0)
  //print out the previous value if the distance gets beyond the maximum distance
    Serial.println(temp+3000);  
  else{
    Serial.println(distance+3000);
    temp = distance;
  }

  //VL53L0X data reading
  Serial.println(laser_sensor.readRangeContinuousMillimeters());
  if (laser_sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
}
