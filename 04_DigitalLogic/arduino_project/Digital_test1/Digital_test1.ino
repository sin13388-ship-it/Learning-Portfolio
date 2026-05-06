
int count=0;
int led_pins[8]={2,3,4,5,6,7,8,9};
int pin=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("test 1");

  byte value_1, led_control;

//  value_1=57;
//  Serial.print("57 in binary = ");
//  Serial.println(value_1,BIN);
//  Serial.print("57 in HEX = ");
//  Serial.println(value_1,HEX);

  led_control=B00000000;
  
  led_control|=(1<<7);
  Serial.print("led_control = ");
  Serial.println(led_control,BIN);

  led_control|=(1<<5);
  Serial.print("led_control = ");
  Serial.println(led_control,BIN);

  int i=0;
  for(i=0; i<8;i++){
    pinMode(led_pins[i], OUTPUT);  
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i=0; i<8; i++){    
    pin |=(1<<i);
    updatesLED();
    delay(1000); 
  }
   for(int i=0; i<8; i++){    
    pin &=~(1<<i);
    updatesLED();
    delay(1000); 
  }
}
void updatesLED(){
  int i=0;
  for(i=0; i<8; i++)
  {
    digitalWrite(led_pins[i], (pin >>i)&0x01);     
  }
}
