
#define pinoRele 2

void setup() {
  Serial.begin(9600);
  pinMode(pinoRele,OUTPUT);
}

void loop() {
  digitalWrite(pinoRele,HIGH);
  delay(1500);
  digitalWrite(pinoRele,LOW);
  delay(1500);
}
