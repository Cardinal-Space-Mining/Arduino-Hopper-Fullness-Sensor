const long int R2 = 5000; //R2 
const long int cutoff = 3000;

const byte analogInput = A0;
const int Sig[] = {2,3,4,5};

void setup(){
  Serial.begin(9600);

  pinMode(A0, INPUT); pinMode(A1, INPUT); pinMode(A2, INPUT); //one for each of the bars 
  for(int i=0; i<4; i++){pinMode(2+i, OUTPUT); Serial.println(2+i);}
  pinMode(A0, INPUT);
}

void printbar(double Bars[4][16]){
  Serial.println("Bar0  \t\tBar1  \t\tBar2");
  for(int i=0;i<16;i++){
     Serial.print(Bars[0][i]); 	Serial.print("  \t");
     Serial.print(Bars[1][i]); 	Serial.print("  \t");
     Serial.println(Bars[2][i]);
  }  Serial.println(); 
}

void printbarBool(bool Bars[4][16]){
  Serial.println("Bar0\tBar1\tBar2\tBar3");
  for(int i=0;i<16;i++){
     Serial.print(Bars[0][i]); 	Serial.print("\t");
     Serial.print(Bars[1][i]); 	Serial.print("\t");
     Serial.print(Bars[2][i]); 	Serial.print("\t");
     Serial.println(Bars[3][i]);   
  }  Serial.println(); 
}

void BartoBool(double Bars[4][16]){
	bool BarsBool[4][16];
  	for(int x=0;x<4;x++){
      for(int y=0;y<16;y++){
      	BarsBool[x][y] = Bars[x][y]>cutoff;
      }}
printbarBool(BarsBool);
}

double CalcRes(byte pin){
    int VD = analogRead(pin);
    double VA = (VD*5)/1023.0;
    double res = ((5 * R2)/VA)-R2;
    return res;
}

void ReadBar(){
  double Bars[4][16];
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
      
      Bars[3][i] = CalcRes(A3);
      Bars[2][i] = CalcRes(A2);
      Bars[1][i] = CalcRes(A1);
      Bars[0][i] = CalcRes(A0);
  }	  
  
  printbar(Bars);
  //BartoBool(Bars);
}
  
void loop(){
	ReadBar();
  
  delay(4000);
}
