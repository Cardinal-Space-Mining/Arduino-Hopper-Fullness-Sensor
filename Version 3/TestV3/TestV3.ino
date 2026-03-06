#include "c1.h"

const long int R2 = 10000; //R2 
const long int cutoff = 3000;

const byte analogInput = A0;
const int Sig[] = {2,3,4,5};

void setup(){
  Serial.begin(9600);

  pinMode(A0, INPUT); pinMode(A1, INPUT); pinMode(A2, INPUT); //one for each of the bars 
  for(int i=0; i<4; i++){pinMode(2+i, OUTPUT); Serial.println(2+i);}
  pinMode(A0, INPUT);
}



double CalcRes(byte pin){
    int VD = analogRead(pin);
    double VA = (VD*5)/1023.0;
    double res = ((5 * R2)/VA)-R2;
    return res;
}

void ReadBar(){
  for (byte i = 0; i <= 15; i++){ 
      bool S3 = (i&0b1000) == 0b1000; 
      bool S2 = (i&0b0100) == 0b0100; 
      bool S1 = (i&0b0010) == 0b0010; 
      bool S0 = (i&0b0001) == 0b0001; 
       
      digitalWrite(5, S3); 
      digitalWrite(4, S2); 
      digitalWrite(3, S1); 
      digitalWrite(2, S0); 
   
   	  delay(2);

  }	  
  Serial.println();
}

  
void loop(){
	ReadBar();
  
  delay(4000);
}
