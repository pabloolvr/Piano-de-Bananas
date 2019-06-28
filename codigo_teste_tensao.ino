int leituraA5 = 0;

void setup()
{
  pinMode(A5, INPUT);
  Serial.begin(9600);

}

void loop()
{
  leituraA5 = analogRead(A5);
  Serial.print("Leitura pino A5: ");
  Serial.println(leituraA5);
  Serial.print("Equivalente em volts: ");
  Serial.println(map(leituraA5, 0, 1023, 0, 5));
  Serial.println("----------------------");
  delay(500); // Wait for 500 millisecond(s)
}
