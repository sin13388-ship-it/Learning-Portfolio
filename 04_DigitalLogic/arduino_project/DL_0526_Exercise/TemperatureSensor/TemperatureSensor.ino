void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A1,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int tempValue;
  float temp;
  tempValue=analogRead(A1);
  Serial.print("tempValue ");
  Serial.println(tempValue);
  temp=((tempValue*4.9)-500)/10.0;
  Serial.print("temp ");
  Serial.println(temp);

  delay(2000);

}
