/*
  LED ticker

  從 PIN2~PIN9 依序點亮，點滅
  |I/O Logic|LED state|  
  Low : ON
  HIGH : OFF

  The circuit:
  - 5V --> R(570 ohm) --> LED --> Arduino I/O

*/
void ledUpdates(int state);
void ledForward();
void ledBackward();
const int pins[8]={2,3,4,5,6,7,8,9};
int isFirstRun;

void setup() {
  //Serial.begin(115200);
  // set the digital pin as output: 
  for(int i=0;i<8;i++){
    pinMode(pins[i], OUTPUT); //using pin2~pin9 as the led array output
    digitalWrite(pins[i], HIGH);
  }  
  isFirstRun=1;
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
    if(!!isFirstRun){
      for(ledState=0;ledState<8;ledState++){
      ledUpdates(ledState);
      delay(100); 
    }
    }
    else{
      for(ledState=1;ledState<8;ledState++){
      ledUpdates(ledState);
      delay(100); 
      }
    }
}
void ledBackward(){
    byte ledState=0;
  for(ledState=0;ledState<7;ledState++){
    ledUpdates(6-ledState);

    delay(100); 

    
  }
}

void ledHop(byte pinState){
  ledUpdates(pinState ^ 0xFF);  
}

void loop() {   
    
    ledForward();
    ledBackward();
    if(!!isFirstRun) isFirstRun=0;

}


