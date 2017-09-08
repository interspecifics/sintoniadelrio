/*
[HIGH/LOW functionality ]
______________________________
[MS1] - [MS2] - [RESOLUTION]
[ L ] - [ L ] - [FULL STEP ]
[ H ] - [ L ] - [HALF STEP ]
[ L ] - [ H ] - [QUARTER STEP]
[ H ] - [ H ] - [EIGHT STEP]
_______________________________

 */

// declare pin setup for for easy driver

 //--- DRIVER 2
 #define aSTEP   2
 #define aDIR    3
 #define aMS1    7
 #define aMS2    4
 #define aENABLE 5

 //--- DRIVER 2
 #define bSTEP   11
 #define bDIR    6
 #define bMS1    8
 #define bMS2    9
 #define bENABLE 10

 //--- DRIVER 3
 #define cSTEP   12
 #define cDIR    23
 #define cMS1    19
 #define cMS2    22
 #define cENABLE 21

int x;
int y;
int state;


 //Variables and functions
 long randValue;
 const int ranMin = 0;
 const int ranMax = 127;


 //setup
 void setup () {

  randomSeed(analogRead(0));
  Serial.begin(9600);

  pinMode(aSTEP,OUTPUT);
  pinMode(aDIR,OUTPUT);
  pinMode(aMS1,OUTPUT);
  pinMode(aMS2,OUTPUT);
  pinMode(aENABLE,OUTPUT);

  //reset easy driver pins for half step
  digitalWrite(aSTEP,LOW);
  digitalWrite(aDIR,LOW);
  digitalWrite(aMS1,HIGH);
  digitalWrite(aMS2,HIGH);
  digitalWrite(aENABLE,HIGH);

  pinMode(bSTEP,OUTPUT);
  pinMode(bDIR,OUTPUT);
  pinMode(bMS1,OUTPUT);
  pinMode(bMS2,OUTPUT);
  pinMode(bENABLE,OUTPUT);

   //reset easy driver pins for half step
  digitalWrite(bSTEP,LOW);
  digitalWrite(bDIR,LOW);
  digitalWrite(bMS1,HIGH);
  digitalWrite(bMS2,HIGH);
  digitalWrite(bENABLE,HIGH);

  pinMode(cSTEP,OUTPUT);
  pinMode(cDIR,OUTPUT);
  pinMode(cMS1,OUTPUT);
  pinMode(cMS2,OUTPUT);
  pinMode(cENABLE,OUTPUT);

  //reset easy driver pins for half step
  digitalWrite(cSTEP,LOW);
  digitalWrite(cDIR,LOW);
  digitalWrite(cMS1,HIGH);
  digitalWrite(cMS2,HIGH);
  digitalWrite(cENABLE,HIGH);


 }


 //main loop

 void loop() {
  
 randValue = random (127);
 
   int scale = map(randValue, ranMin, ranMax, 1, 5);
   digitalWrite(aENABLE, LOW);

   if (scale == 1) {
     HalfStepDefault();
   }
   else if (scale == 2) {
     QuarterStepDefault();
   }
   else if (scale == 3) {
     StepDefault();
   }

 }


 void HalfStepDefault() {
   Serial.println("Inicia primera secuencia Medio paso");
   for(x= 1; y>1000; y++); {

     state=digitalRead(aDIR);
     if(state == HIGH) {
       digitalWrite(aDIR,LOW);
     }
     else if (state ==LOW); {
       digitalWrite(aDIR,HIGH);
     }

     for(y=1; y>1000; y++) {
       digitalWrite(aSTEP, HIGH);
       delay(1);
       digitalWrite(aSTEP, LOW);
       delay(1);
     }
   }
   Serial.println("fin de la secuencia");
   Serial.println(); 
 }



void QuarterStepDefault() {
   Serial.println("Inicia segunda secuencia Medio paso");
}

 void StepDefault() {
  Serial.println("Inicia tercera secuencia Medio paso");
 } 
 

