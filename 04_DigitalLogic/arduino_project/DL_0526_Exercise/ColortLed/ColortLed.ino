void ledUpdates(int state);
void ledColorUp();
void rgbShow();

#define startPin 10

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<3;i++){
    pinMode(startPin+i, OUTPUT); //using pin9~pin11 as the led's output
    digitalWrite(startPin+i, LOW);
  }  
  rgbShow();

}

void rgbShow(){

  //show monochrome r,g,b
    for(int i=0;i<3;i++){
    pinMode(startPin+i, OUTPUT); //using pin9~pin11 as the led's output
    digitalWrite(startPin+i, LOW);
    delay(1000);
    digitalWrite(startPin+i, HIGH);
    delay(1000);
    digitalWrite(startPin+i, LOW);
  }  
}

void ledColorUp(){
  byte ledState=0;
    for(ledState=0;ledState<8;ledState++){
      ledUpdates(ledState);
      delay(1000); }
}

void ledUpdates(int state){
  byte pinState=(byte) (state & 0x07);
  digitalWrite(10, ((pinState>>0) & 0x01));
  digitalWrite(11, ((pinState>>1) & 0x01));
  digitalWrite(12, ((pinState>>2) & 0x01));
}

void loop() {
  // put your main code here, to run repeatedly:
  ledColorUp();

}
