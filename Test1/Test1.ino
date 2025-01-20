int cutoffNumber = 90;
int pin1 = 3; //red
int pin2 = 2; //blue

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT); pinMode(3,OUTPUT);
}

void loop(){
  ReadBar(pin1, pin2);
  delay(2000);
  }

int arr[12]; byte aPins[6] = {A5,A4,A3,A2,A1,A0}; 
void ReadBar(int p1,int p2){
  int dPins[2] = {p1,p2};
  for(int p=0; p<2;p++){
    pinMode(dPins[p], OUTPUT); digitalWrite(dPins[p],HIGH);
    for(int i=0; i<6;i++){arr[i+6*p] = analogRead(aPins[i]);}
    digitalWrite(dPins[p],LOW);pinMode(dPins[p], INPUT);
  }
  
  PrintArr(arr); 
  Serial.print("open:");
  Serial.print(cuttoff(arr));
  Serial.println("");
  }

int cuttoff(int arr[]){
  int out = 0;
  for(int i=0;i<12;i++){
    if(arr[i]>cutoffNumber){out++;}}
  return out;
  }

void PrintArr(int arr[12]){for(int i =0; i<12;i++){
  Serial.print(arr[i]);Serial.print(" ");}}
