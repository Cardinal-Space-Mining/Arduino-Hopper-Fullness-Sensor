int pin = 2;

void setup()
{  
  Serial.begin(9600);
  pinMode(pin,OUTPUT);
}

long int x =0;
void loop()
{
  //Serial << "Current millis: " << millis() << endl;
  Serial.print("Test: ");   Serial.println(x); 
  //delay(1000);
  x+=1;

digitalWrite(pin, HIGH);
delay(500);
digitalWrite(pin, LOW);
delay(500);

}
