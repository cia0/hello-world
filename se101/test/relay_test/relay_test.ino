int relay = 8;

void setup() {
  pinMode(relay,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(relay, LOW);
  Serial.println("ON");
  delay(750);
  digitalWrite(relay, HIGH);
  Serial.println("OFF");
  delay(1500);
  
  
}
