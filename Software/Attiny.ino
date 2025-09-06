/*
It's a simple way to calibrate ATtiny25/45/85's OSCCAL, only need an 
Arduino Uno/Nano and etc. ..a breadboard and some wires. Then on your 
serial monitor you wil get a list of OSCCAL and frequency.
Detail: https://github.com/bonarm/Simple-ATtiny25-45-85-Internal-RC-Oscillator-Calibration-Tunning

This sketch is for Attiny25/45/85.
*/


#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS 0x4 // Address of the slave

int b, i;

void setup() {
  DDRB |= 1<<4;             // PB4 Output(for PWM waveform)
  DDRB &= ~(1<<3);          // set PB3(pin2) to input
  PORTB |= 1<<3         ;   // enable PCB3 internal PULL-UP

  TCNT1 = 0;
  TCCR1 = 0;
  TCCR1 |= 1<<CTC1;       // Timer 1 CTC mode
  GTCCR |= 1<<PSR1;       // reset the prescaler
  GTCCR |= 1<<COM1B1;     // PB4 Output PWM
  TCCR1 |= (1<<CS10);     // CK/1
  OCR1C = 9;              // 1MHz/(1+9) = 100KHz
  OCR1B = 8; 
  
  b = PINB & 0b00001000;  // Optional. If PB3 connected to GND, OSCCAL will start from 0
  if(b==0)  i=0;
  else i=50;              // Otherwise, it starts from 50.


  TinyWireS.begin(I2C_SLAVE_ADDRESS); // join i2c network
  TinyWireS.onRequest(requestEvent);
}

void loop() {
  b = PINB & 0b00001000;    // To check PB3's status
  TinyWireS_stop_check();
}


void requestEvent()
{
    TinyWireS.send(i);
    OSCCAL = i;
    if(i>=125) {
      if(b==0)  i=0;
      else i=50;
    }
    i++;
}
