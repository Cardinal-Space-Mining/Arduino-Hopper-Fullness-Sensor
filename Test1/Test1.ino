float cutoff = 30;
int pin1 = 2; //red
int pin2 = 3; //blue

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop(){
  ReadBar(pin1, pin2);
  delay(2000);
  }

const float R0 = 100;
void ReadBar(p1,p2){
  pinMode(p1, OUTPUT);
  digitalWrite(p1,HIGH);
  
  float res0 = analogRead(A5);
  float res1 = analogRead(A4);
  float res2 = analogRead(A3);
  float res3 = analogRead(A2);
  float res4 = analogRead(A1);
  float res5 = analogRead(A0);
  digitalWrite(p1,LOW);
  pinMode(p1, INPUT);

  pinMode(p2, OUTPUT);
  digitalWrite(p2,HIGH);
  float res6 = analogRead(A5);
  float res7 = analogRead(A4);
  float res8 = analogRead(A3);
  float res9 = analogRead(A2);
  float res10 = analogRead(A1);
  float res11 = analogRead(A0);
  digitalWrite(p2,LOW);
  pinMode(p2, INPUT); 
  
  Print(res0);
  Print(res1);
  Print(res2);
  Print(res3);
  Print(res4);
  Print(res5);
  Print(res6);
  Print(res7);
  Print(res8);
  Print(res9);
  Print(res10);
  Print(res11);
  Serial.println("");
  }

void Print(float var){Serial.print(var);  Serial.print(" ");}
