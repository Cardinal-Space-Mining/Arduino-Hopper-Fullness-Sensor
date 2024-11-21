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

int arr[12];
const float R0 = 100;
void ReadBar(int p1,int p2){
  pinMode(p1, OUTPUT);
  digitalWrite(p1,HIGH);
  
  arr[0] = analogRead(A5);
  arr[1] = analogRead(A4);
  arr[2] = analogRead(A3);
  arr[3] = analogRead(A2);
  arr[4] = analogRead(A1);
  arr[5] = analogRead(A0);
  digitalWrite(p1,LOW);
  pinMode(p1, INPUT);

  pinMode(p2, OUTPUT);
  digitalWrite(p2,HIGH);
  arr[6] = analogRead(A5);
  arr[7] = analogRead(A4);
  arr[8] = analogRead(A3);
  arr[9] = analogRead(A2);
  arr[10] = analogRead(A1);
  arr[11] = analogRead(A0);
  digitalWrite(p2,LOW);
  pinMode(p2, INPUT); 

  PrintArr(arr);
  
  Serial.println("");
  }

void PrintArr(int arr[12]){for(int i =0; i<12;i++){Serial.print(arr[i]);Serial.print(" ");}}
//void Print(int var){Serial.print(var);  Serial.print(" ");}
