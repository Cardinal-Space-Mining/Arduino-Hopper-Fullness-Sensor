#include "c1.h"

const long int R2 = 10000; //R2
#define cutoff 5000 //3000

const byte analogInput = A0;
const int Sig[] = {2, 3, 4, 5};

//currently Bar3 is the lower 1
//currenty Bar2 is the mid
//curretly Bar1 is the higher one 

//These number are the max and the min % for each bar
int High[] = {40, 100};
int Mid[]  = {30, 90};
int Low[]  = {20, 80};

int BarHigh[16] = {};
int BarMid[16]  = {};
int BarLow[16]  = {};

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT); pinMode(A1, INPUT); pinMode(A2, INPUT); //one for each of the bars
  for (int i = 0; i < 4; i++) {
    pinMode(2 + i, OUTPUT);
  }
  pinMode(A0, INPUT);
  for (int i = 0; i < 16; i++) {
    BarHigh[i] = ((((High[1] - High[0]) / 15)* i + High[0]));
    BarMid[i]  = ((((Mid[1] - Mid[0])  / 15) * i + Mid[0]));
    BarLow[i]  = ((((Low[1] - Low[0])  / 15) * i + Low[0]));
  }
}

void PrintBarRes(int NumOfBars, const Bars& Bar1, const Bars& Bar2, const Bars& Bar3) { //false for res Bool for bool;
  for (int i = 0; i < 16; i++) {
    if (NumOfBars >= 1) {
      Serial.print(Bar1.ResVals[i]);
      Serial.print(" \t");
    }
    if (NumOfBars >= 2) {
      Serial.print(Bar2.ResVals[i]);
      Serial.print(" \t");
    }
    if (NumOfBars >= 3) {
      Serial.print(Bar3.ResVals[i]);
      Serial.print(" \t");
    }
    Serial.println();
  }
  Serial.println();
}

Bars CalcBools(Bars Bar) {
  int maxHeight = -1;
  for (int i = 0; i < 16; i++) { Bar.BoolVals[i] = (Bar.ResVals[i] > cutoff);}
  for (int i = 15; i >=0; i--){
    if (Bar.ResVals[i] > cutoff) {
      maxHeight = 15-i;
    }
  }
  Bar.MaxHeight = maxHeight;
  return Bar;
}

void PrintBarBool(int NumOfBars, const Bars& Bar1, const Bars& Bar2, const Bars& Bar3) { //false for res Bool for bool;
  for (int i = 0; i < 16; i++) {
    if (NumOfBars >= 1) {
      Serial.print(Bar1.BoolVals[i]);
      Serial.print("\t\t");
    }
    if (NumOfBars >= 2) {
      Serial.print(Bar2.BoolVals[i]);
      Serial.print("\t\t");
    }
    if (NumOfBars >= 3) {
      Serial.print(Bar3.BoolVals[i]);
      Serial.print("\t\t");
    }
    Serial.println();
  }
  Serial.println();
}

double CalcRes(byte pin) {
  int VD = analogRead(pin);
  double VA = (VD * 5) / 1023.0;
  double res = ((5 * R2) / VA) - R2 - 1500;
  return res;
}

float CalcFinalVal(const Bars& Bar1, const Bars& Bar2, const Bars& Bar3) {
  float Bar1Val = 0;
  float Bar2Val = 0;
  float Bar3Val = 0;
  float AvgFull = 0;

  if (Bar1.MaxHeight >= 0) {Bar1Val = BarHigh[Bar1.MaxHeight];}
  if (Bar2.MaxHeight >= 0) {Bar2Val = BarMid [Bar2.MaxHeight];}
  if (Bar3.MaxHeight >= 0) {Bar3Val = BarLow [Bar3.MaxHeight];}

  if (Bar1.MaxHeight == 15 && Bar2.MaxHeight == 15 && Bar2.MaxHeight == 15){
    AvgFull=100;
    }
  else if (Bar1.MaxHeight < 15 && Bar2.MaxHeight == 15 && Bar2.MaxHeight == 15){
    AvgFull=Bar1Val;
    }
   else if (Bar1.MaxHeight < 15 && Bar2.MaxHeight < 15 && Bar2.MaxHeight == 15){
    AvgFull=(Bar1Val+ Bar2Val)/2;
    }
  else {AvgFull = (Bar1Val + Bar2Val + Bar3Val) / 3;}

  if(false){
    Serial.print("Bar 1: ");     Serial.print(Bar1.MaxHeight); Serial.print(" "); Serial.println(Bar1Val);
    Serial.print("Bar 2: ");     Serial.print(Bar2.MaxHeight); Serial.print(" "); Serial.println(Bar2Val);
    Serial.print("Bar 3: ");     Serial.print(Bar3.MaxHeight); Serial.print(" "); Serial.println(Bar3Val);
    Serial.print("Final Full:"); Serial.println(AvgFull);
    }
  return AvgFull;
}

void ReadBar() {
  struct Bars Bar1;
  struct Bars Bar2;
  struct Bars Bar3;

  for (byte i = 0; i <= 15; i++) {
    bool S3 = (i & 0b1000) == 0b1000;
    bool S2 = (i & 0b0100) == 0b0100;
    bool S1 = (i & 0b0010) == 0b0010;
    bool S0 = (i & 0b0001) == 0b0001;

    digitalWrite(5, S3);
    digitalWrite(4, S2);
    digitalWrite(3, S1);
    digitalWrite(2, S0);

    delay(10);
    Bar1.ResVals[i] = CalcRes(A0);
    delay(2);
    Bar2.ResVals[i] = CalcRes(A1);
    delay(2);
    Bar3.ResVals[i] = CalcRes(A2);
  }

  //PrintBarRes(1, Bar2, Bar2, Bar3);
  Bar1 = CalcBools(Bar1);
  Bar2 = CalcBools(Bar2);
  Bar3 = CalcBools(Bar3);
  //PrintBarBool(1, Bar2, Bar2, Bar3);
  //Serial.println(Bar2.MaxHeight);

  Bar1.MaxHeight = 1;
  Bar2.MaxHeight = 2;
  Bar3.MaxHeight = 3;

  float FinalFull = CalcFinalVal(Bar1, Bar2, Bar3);
  Serial.print("Fs: "); Serial.println(FinalFull/100); 
}

void loop() {
  ReadBar();

  //delay(2000);
}
