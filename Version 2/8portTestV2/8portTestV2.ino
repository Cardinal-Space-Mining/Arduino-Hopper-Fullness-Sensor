void setup() {
  Serial.begin(9600);
}

void loop() {
  ReadBar(1);
  ReadBar(2);
  ReadBar(3);
  ReadBar(4);
  ReadBar(5);
  ReadBar(6); 
  ReadBar(7); 
  ReadBar(8); 

  Serial.println("");
  delay(10000);
}

int arr[12];
void ReadBar(int PortNum){ 
  byte port[2][4];
  if(PortNum == 1){byte port[2][4] = {{2,3,4,0},    {A0,A1,A2,A3}};} //port1
  if(PortNum == 2){byte port[2][4] = {{5,6,7,0},    {A0,A1,A2,A3}};} //port2
  if(PortNum == 3){byte port[2][4] = {{8,9,10,0},   {A0,A1,A2,A3}};} //port3
  if(PortNum == 4){byte port[2][4] = {{11,12,13,0}, {A0,A1,A2,A3}};} //port4

  if(PortNum == 5){byte port[2][4] = {{2,3,4,0},    {A4,A5,A6,A7}};} //port5
  if(PortNum == 6){byte port[2][4] = {{5,6,7,0},    {A4,A5,A6,A7}};} //port6
  if(PortNum == 7){byte port[2][4] = {{8,9,10,0},   {A4,A5,A6,A7}};} //port7
  if(PortNum == 8){byte port[2][4] = {{11,12,13,0}, {A4,A5,A6,A7}};} //port8

  for(int i=0;i<3;i++){
    pinMode(port[0][i], OUTPUT); digitalWrite(port[0][i], HIGH);
    for(int j=0;j<4;j++){arr[4*i+j] = analogRead(port[1][j]);}
    digitalWrite(port[0][i], LOW); pinMode(port[0][i], INPUT);
  }
  
  PrintArr(arr, PortNum);
  Serial.println("");
}

void PrintArr(int arr[12], int PortNum) {
  Serial.print("Port num: "); Serial.print(PortNum); Serial.print(" ");
  for (int i = 0; i < 12; i++) {
    Serial.print(arr[i]); Serial.print(" ");
  }
}
