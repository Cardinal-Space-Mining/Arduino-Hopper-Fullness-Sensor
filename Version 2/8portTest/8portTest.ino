int cutoffNumber = 90;
int pin1 = 3; //red
int pin2 = 2; //blue

void setup() {
  Serial.begin(9600);
}

void loop() {
  ReadBar(pin1, pin2);
  delay(2000);
}

int arr[12];

  //port 4 
  //int dPins[] = {11,12,13};
  //byte aPins[] = {A0,A1,A2,A3};

void ReadBar(int p1, int p2) {
  
  //port 1 
  int dPins[] = {2,3,4};
  byte aPins[] = {A0,A1,A2,A3};
  
  for(int i=0;i<3;i++){
    pinMode(dPins[i], OUTPUT); digitalWrite(dPins[i], HIGH);
    for(int j=0;j<4;j++){arr[4*i+j] = analogRead(aPins[j]);}
    digitalWrite(dPins[i], LOW); pinMode(dPins[i], INPUT);
  }
  
  //printing Section
  PrintArr(arr);
  Serial.print("open:");
  Serial.print(cuttoff(arr));
  Serial.println("");
}

int cuttoff(int arr[]) {
  int out = 0;
  for (int i = 0; i < 12; i++) {
    if (arr[i] > cutoffNumber) {
      out++;
    }
  }
  return out;
}

void PrintArr(int arr[12]) {
  for (int i = 0; i < 12; i++) {
    Serial.print(1000 - arr[i]); Serial.print(" ");
  }
}


/*
 * pinMode(dPins[0], OUTPUT); digitalWrite(dPins[0], HIGH);
  arr[0] = analogRead(aPins[0]);
  arr[1] = analogRead(aPins[1]);
  arr[2] = analogRead(aPins[2]);
  arr[3] = analogRead(aPins[3]);
  digitalWrite(dPins[0], LOW); pinMode(dPins[0], INPUT);

  pinMode(dPins[1], OUTPUT); digitalWrite(dPins[1], HIGH);
  arr[4] = analogRead(aPins[0]);
  arr[5] = analogRead(aPins[1]);
  arr[6] = analogRead(aPins[2]);
  arr[7] = analogRead(aPins[3]);
  digitalWrite(dPins[1], LOW); pinMode(dPins[1], INPUT);

  pinMode(dPins[2], OUTPUT); digitalWrite(dPins[2], HIGH);
  arr[8] = analogRead(aPins[0]);
  arr[9] = analogRead(aPins[1]);
  arr[10] = analogRead(aPins[2]);
  arr[11] = analogRead(aPins[3]);
  digitalWrite(dPins[2], LOW); pinMode(dPins[2], INPUT);
*/
