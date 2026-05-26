/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  The circuit:
  - Use the onboard LED.
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://docs.arduino.cc/hardware/

  created 2005
  by David A. Mellis
  modified 8 Feb 2010
  by Paul Stoffregen
  modified 11 Nov 2013
  by Scott Fitzgerald
  modified 9 Jan 2017
  by Arturo Guadalupi

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay/
*/
void ledUpdates(int state);
void ledForward();
void ledBackward();
const int pins[8]={2,3,4,5,6,7,8,9};

void setup() {
  // set the digital pin as output:
  
   Serial.begin(115200);
  for(int i=0;i<8;i++){
    pinMode(pins[i], OUTPUT); //using pin2~pin9 as the led array output
    digitalWrite(pins[i], HIGH);
  }  
  
}

void ledUpdates(int state){
  byte pinState=(byte) ~(1<<state);
  for(int i=0; i<8; i++){    
    // Serial.print(pinState);
    // Serial.print(" ,");
    // Serial.println(((pinState>>i) & 0x01));
    digitalWrite(pins[i], ((pinState>>i) & 0x01));   
  }  
}

void ledForward(){
  byte ledState=0;
  for(ledState=0;ledState<8;ledState++){
    ledUpdates(ledState);
    delay(50); 
  }
}
void ledBackward(){
    byte ledState=0;
  for(ledState=0;ledState<7;ledState++){
    ledUpdates(6-ledState);
    delay(50); 
  }
}


void loop() {
    
    ledForward();
    ledBackward();

}


