#include "c1.h"

const long int R2 = 10000; //R2 
#define cutoff 3000

const byte analogInput = A0;
const int Sig[] = {2,3,4,5};

void setup(){
  Serial.begin(9600);

  pinMode(A0, INPUT); pinMode(A1, INPUT); pinMode(A2, INPUT); //one for each of the bars 
  for(int i=0; i<4; i++){pinMode(2+i, OUTPUT);}
  pinMode(A0, INPUT);
}

void PrintBarRes(int NumOfBars, Bars Bar1, Bars Bar2, Bars Bar3){ //false for res Bool for bool; 
  for(int i=0;i<16;i++){
    if (NumOfBars >=1){Serial.print(Bar1.ResVals[i]); Serial.print(" \t");}
    if (NumOfBars >=2){Serial.print(Bar2.ResVals[i]); Serial.print(" \t");}
    if (NumOfBars >=3){Serial.print(Bar3.ResVals[i]); Serial.print(" \t");}
    Serial.println();
  }
  Serial.println();
}

Bars CalcBools(Bars Bar){
  for(int i=0;i<16;i++){
    Bar.BoolVals[i] = (Bar.ResVals[i]>cutoff);
  }
  return Bar;
}

void PrintBarBool(int NumOfBars, Bars Bar1, Bars Bar2, Bars Bar3){ //false for res Bool for bool; 
  for(int i=0;i<16;i++){
    if (NumOfBars >=1){Serial.print(Bar1.BoolVals[i]); Serial.print("\t\t");}
    if (NumOfBars >=2){Serial.print(Bar2.BoolVals[i]); Serial.print("\t\t");}
    if (NumOfBars >=3){Serial.print(Bar3.BoolVals[i]); Serial.print("\t\t");}
    Serial.println();
  }
  Serial.println();
}

double CalcRes(byte pin){
    int VD = analogRead(pin);
    double VA = (VD*5)/1023.0;
    double res = ((5 * R2)/VA)-R2-1500;
    return res;
}

void ReadBar(){
  struct Bars Bar1;
  struct Bars Bar2;
  struct Bars Bar3;
  
  for (byte i = 0; i <= 15; i++){ 
      bool S3 = (i&0b1000) == 0b1000; 
      bool S2 = (i&0b0100) == 0b0100; 
      bool S1 = (i&0b0010) == 0b0010; 
      bool S0 = (i&0b0001) == 0b0001; 
       
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
      delay(2);
  }	  
  PrintBarRes(1, Bar1, Bar2, Bar3);
  Bar1 = CalcBools(Bar1);
  Bar2 = CalcBools(Bar2);
  Bar3 = CalcBools(Bar3);
  PrintBarBool(1, Bar1, Bar2, Bar3);
}
  
void loop(){
	ReadBar();
  
  delay(4000);
}
