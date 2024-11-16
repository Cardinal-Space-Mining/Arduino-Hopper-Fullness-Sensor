void setup() {
  Serial.begin(9600);
}

const float R0 = 100;
const float R1 = 101;
const float R2 = 99;
const float R3 = 98;
const float R4 = 102;
const float R5 = 103;

void loop(){
  ReadBar(2,3);
  delay(5000);
  }

float ReadBar(int p1, int p2){ // 2, 3 
  float cutoff = 80;
  
  pinMode(p2, OUTPUT);
  digitalWrite(p2,HIGH);
  float res0 = Resistance(analogRead(A0), R0);
  float res1 = Resistance(analogRead(A1), R1);                  
  float res2 = Resistance(analogRead(A2), R2);                  
  float res3 = Resistance(analogRead(A3), R3);
  float res4 = Resistance(analogRead(A4), R4);
  float res5 = Resistance(analogRead(A5), R5);                                    
  digitalWrite(p2,LOW);
  pinMode(p2, INPUT);
                              
  pinMode(p1, OUTPUT);
  digitalWrite(p1,HIGH);
  float res6 = Resistance(analogRead(A0), R0);
  float res7 = Resistance(analogRead(A1), R1);                  
  float res8 = Resistance(analogRead(A2), R2);                  
  float res9 = Resistance(analogRead(A3), R3);
  float res10 = Resistance(analogRead(A4), R4);
  float res11 = Resistance(analogRead(A5), R5);                                    
  digitalWrite(p1,LOW);
  pinMode(p1, INPUT);                        

  int bin0 = res0<cutoff;
  int bin1 = res1<cutoff;
  int bin2 = res2<cutoff;  
  int bin3 = res3<cutoff;
  int bin4 = res4<cutoff;
  int bin5 = res5<cutoff;
  int bin6 = res6<cutoff;
  int bin7 = res7<cutoff;
  int bin8 = res8<cutoff;
  int bin9 = res9<cutoff;
  int bin10 = res10<cutoff;
  int bin11 = res11<cutoff;
  
  int sum = bin0+bin1+bin2+bin3+bin4+bin5+
    bin6+bin7+bin8+bin9+bin10+bin11;
  
  float percent = sum/12.0;
  
  Serial.print("R0: "); Serial.print(res0); 
    Serial.print(" B0:"); Serial.println(bin0);
  Serial.print("R1: "); Serial.print(res1);
    Serial.print(" B1:"); Serial.println(bin1);
  Serial.print("R2: "); Serial.print(res2);
    Serial.print(" B2:"); Serial.println(bin2);
  Serial.print("R3: "); Serial.print(res3);
    Serial.print(" B3:"); Serial.println(bin3);
  Serial.print("R4: "); Serial.print(res4); 
    Serial.print(" B4:"); Serial.println(bin4);
  Serial.print("R5: "); Serial.print(res5);  
    Serial.print(" B5:"); Serial.println(bin5);
  Serial.print("R6: "); Serial.print(res6); 
    Serial.print(" B6:"); Serial.println(bin6);
  Serial.print("R7: "); Serial.print(res7);
    Serial.print(" B7:"); Serial.println(bin7);
  Serial.print("R8: "); Serial.print(res8);
    Serial.print(" B8:"); Serial.println(bin8);
  Serial.print("R9: "); Serial.print(res9); 
    Serial.print(" B9:"); Serial.println(bin9);
  Serial.print("R10: "); Serial.print(res10); 
    Serial.print(" B10:"); Serial.println(bin10);
  Serial.print("R11: "); Serial.print(res11); 
    Serial.print(" B11:"); Serial.println(bin11);
  
  Serial.print("Percent: "); Serial.println(percent);
  
  Serial.println("----------------------------");                                                                    
    
  
  return 0.83;                       
  }
/*
//float RC = 1000;
float Resistance(int Voltage, float ResistorConst){
  float v1 = Voltage * (5.0 / 1023.0)+0.01;
  return ((5.0*ResistorConst)/v1)-ResistorConst;}
*/

float Resistance(int Voltage, float ResistorConst){
  //float v1 = Voltage * (5.0 / 1023.0);
  return Voltage;}
