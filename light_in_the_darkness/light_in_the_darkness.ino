#define LED_PIN 13
#define LDR_PIN A0

void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  int lightness = analogRead(LDR_PIN);
  int threshold = 800;

  boolean tooDark = (lightness < threshold);
  //tooDark = false;

  if (tooDark){
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
