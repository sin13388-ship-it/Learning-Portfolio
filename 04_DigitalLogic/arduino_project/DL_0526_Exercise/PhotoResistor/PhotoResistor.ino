/*
  Analog input, serial output

  Reads an analog input pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 2.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground

*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // print the results to the Serial Monitor:
  Serial.print("sensor (dec)= ");
  Serial.println(sensorValue);
  Serial.print("sensor (vol) = ");
  Serial.println((float)sensorValue/1024 *5);

  if(sensorValue>750){
    digitalWrite(2,HIGH);
    delay(500);

  }else{
    digitalWrite(2,LOW);
    delay(500);
  }

  // converter to settle after the last reading:
  delay(2000);
}
