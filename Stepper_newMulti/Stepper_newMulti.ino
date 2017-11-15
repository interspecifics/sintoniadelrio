/*
 * Interspecifics
 * Sintonìa del Rìo
 * -----------------
 * 
 * --- DRIVER 1:
 * STEP = 2
 * DIR = 3
 * --- DRIVER 2
 * STEP = 11
 * DIR = 6
 * --- DRIVER 3
 * STEP = 12
 * DIR = 23
*/

#define STP_PIN_1   2
#define DIR_PIN_1   3
#define STP_PIN_2   6
#define DIR_PIN_2   7
#define STP_PIN_3   9
#define DIR_PIN_3   10

#define MICROSECONDS_PER_MICROSTEP   375

uint32_t currentTime = 0;
uint32_t lastStepTime_1 = 0;
uint32_t lastStepTime_2 = 0;
uint32_t lastStepTime_3 = 0;

boolean endBeat_1 = false;
boolean endBeat_2 = false;
boolean endBeat_3 = false;

int dataSensor_1, dataSensor_2, dataSensor_3;
int maxDist_1, maxDist_2, maxDist_3;
int distance_1, distance_2, distance_3;


void setup() {
  pinMode(STP_PIN_1, OUTPUT);
  pinMode(DIR_PIN_1, OUTPUT);
  pinMode(STP_PIN_2, OUTPUT);
  pinMode(DIR_PIN_2, OUTPUT);
  pinMode(STP_PIN_3, OUTPUT);
  pinMode(DIR_PIN_3, OUTPUT);
  digitalWrite(STP_PIN_1, LOW);
  digitalWrite(DIR_PIN_1, LOW);
  digitalWrite(STP_PIN_2, LOW);
  digitalWrite(DIR_PIN_2, LOW);
  digitalWrite(STP_PIN_3, LOW);
  digitalWrite(DIR_PIN_3, LOW);
  endBeat_1 = false;
  endBeat_2 = false;
  endBeat_3 = false;
  distance_1 = 0;
  distance_2 = 0;
  distance_3 = 0;
  randomSeed(analogRead(0));
}

void loop() {
  currentTime = micros();

  // step for driver1
  if ((currentTime - lastStepTime_1) > MICROSECONDS_PER_MICROSTEP){
    lastStepTime_1 = currentTime;
    
    // make a step and register
    digitalWrite(STP_PIN_1, HIGH);
    delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
    digitalWrite(STP_PIN_1, LOW);
    delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
    distance_1++;
    
    // change direction, reset counter
    if (distance_1 >= maxDist_1){
      if (digitalRead(DIR_PIN_1) == LOW) {
        digitalWrite(DIR_PIN_1, HIGH);
      }
      else {
        digitalWrite(DIR_PIN_1, LOW);
        endBeat_1 = true;
        readSensor_1();
      }
      distance_1 = 0;
      delay(20);
    } // end dirchange
  } // end step

  // step for driver2
  if ((currentTime - lastStepTime_2) > MICROSECONDS_PER_MICROSTEP){
    lastStepTime_2 = currentTime;
    
    // make a step and register
    digitalWrite(STP_PIN_2, HIGH);
    delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
    digitalWrite(STP_PIN_2, LOW);
    delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
    distance_2++;
    
    // change direction, reset counter
    if (distance_2 >= maxDist_2){
      if (digitalRead(DIR_PIN_2) == LOW) {
        digitalWrite(DIR_PIN_2, HIGH);
      }
      else {
        digitalWrite(DIR_PIN_2, LOW);
        endBeat_2 = true;
        readSensor_2();
      }
      distance_2 = 0;
      delay(20);
    } // end dirchange
  } // end step

  // step for driver3
  if ((currentTime - lastStepTime_3) > MICROSECONDS_PER_MICROSTEP){
    lastStepTime_3 = currentTime;
    
    // make a step and register
    digitalWrite(STP_PIN_3, HIGH);
    delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
    digitalWrite(STP_PIN_3, LOW);
    delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
    distance_3++;
    
    // change direction, reset counter
    if (distance_3 >= maxDist_3){
      if (digitalRead(DIR_PIN_3) == LOW) {
        digitalWrite(DIR_PIN_3, HIGH);
      }
      else {
        digitalWrite(DIR_PIN_3, LOW);
        endBeat_3 = true;
        readSensor_3();
      }
      distance_3 = 0;
      delay(20);
    } // end dirchange
  } // end step

}



// ----- -------- ----------- READ-SENSORS ROUTINES
void readSensor_1(){
  int dataS1 = analogRead(A0);
  dataSensor_1 = map(dataS1, 0, 1024, 0, 3);
  endBeat_1 = false;
  // select case
  switch(dataSensor_1){
    case 0:
      maxDist_1 = 100;
      break;
    case 1:
      maxDist_1 = 200;
      break;
    case 2:
      maxDist_1 = 50;
      break;
    case 3:
      maxDist_1 = 25;
      break;
  }
}

void readSensor_2(){
  int dataS2 = analogRead(A0);
  dataSensor_2 = map(dataS2, 0, 1024, 0, 3);
  endBeat_2 = false;
  // select case
  switch(dataSensor_2){
    case 0:
      maxDist_2 = 100;
      break;
    case 1:
      maxDist_2 = 200;
      break;
    case 2:
      maxDist_2 = 50;
      break;
    case 3:
      maxDist_2 = 25;
      break;
  }
}

void readSensor_3(){
  int dataS3 = analogRead(A0);
  dataSensor_3 = map(dataS3, 0, 1024,  0, 3);
  
  endBeat_3 = false;
  // select case
  switch(dataSensor_3){
    case 0:
      maxDist_3 = 100;
      break;
    case 1:
      maxDist_3 = 200;
      break;
    case 2:
      maxDist_3 = 50;
      break;
    case 3:
      maxDist_3 = 25;
      break;
  }
}
