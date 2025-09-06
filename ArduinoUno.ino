/*
It's a simple way to calibrate ATtiny25/45/85's OSCCAL, only need an 
Arduino Uno/Nano and etc. ..a breadboard and some wires. Then on your 
serial monitor you wil get a list of OSCCAL and frequency.
Detail: https://github.com/bonarm/Simple-ATtiny25-45-85-Internal-RC-Oscillator-Calibration-Tunning

This sketch is for Arduino Uno/Nano etc., as master.
*/

#include <Wire.h>
#include <FreqCount.h>
 
void setup()
{
  Wire.begin(); 
  FreqCount.begin(200);
  Serial.begin(115200); 
}
 
void loop()
{
  Serial.println("Request ATtiny ...");
  Wire.requestFrom(4, 1); // request 1 byte from slave device address 4
 
  while(Wire.available()) // slave may send less than requested
  {
    int i = Wire.read(); // receive a byte as character
    Serial.print("\r\nOSCCAL = ");  Serial.println(i); 
  }
    if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    Serial.print("f = "); Serial.print(count*5); Serial.println("Hz");
  }
  delay(250);
}
