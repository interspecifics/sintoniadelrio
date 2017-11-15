int waterSensor = 0;

int Distance = 0;  // Grabar el numero de pasos que hemos dado
int Distance2 = 0;
int Distance3 = 0;
int waterValue = 0;
int waterMin = 0;
int waterMax = 700; 
int x;
int y;
unsigned long lastReadWrite;
  


// Define our maximum and minimum speed in steps per second (scale pot to these)
#define RPMS 400.0
#define STEP_PIN                2
#define DIRECTION_PIN           3
#define ENABLE_PIN              5

#define aSTEP_PIN               11
#define aDIRECTION_PIN          6
#define aENABLE_PIN             10

#define bSTEP_PIN               12
#define bDIRECTION_PIN          23
#define bENABLE_PIN             21


#define STEPS_PER_REV         200
#define MICROSTEPS_PER_STEP     8
#define MICROSECONDS_PER_MICROSTEP   (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(RPMS / 60))
#define READPERIOD             1



uint32_t LastStepTime = 0;
uint32_t CurrentTime = 0;

long randNumber;
const int randMin = 0;
const int randMax = 300;


void setup() { 

  pinMode(STEP_PIN, OUTPUT);    
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(aSTEP_PIN, OUTPUT);    
  pinMode(aDIRECTION_PIN, OUTPUT);
  pinMode(bSTEP_PIN, OUTPUT);    
  pinMode(bDIRECTION_PIN, OUTPUT);
  lastReadWrite = millis();  
  Serial.begin(9600);
}

void loop() {

  waterValue = analogRead(waterSensor);

  waterValue = map(waterValue, waterMin, waterMax, 0, 8);
  Serial.print(waterValue, DEC);         
  Serial.print("\t A:"); 

  digitalWrite(ENABLE_PIN, LOW); //Pull enable pin low to allow motor control
  digitalWrite(aENABLE_PIN, LOW);
  digitalWrite(bENABLE_PIN, LOW);

    CurrentTime = micros();
  
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
      
  LastStepTime = CurrentTime;
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);

  digitalWrite(aSTEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
  digitalWrite(aSTEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);

  digitalWrite(bSTEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
  digitalWrite(bSTEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
  
  Distance = Distance + 1;   // record this step
  Distance2 = Distance2 + 1;   // record this step
  Distance3 = Distance3 + 1; 

 
  // Revisar si estamos al final de la secuencia de pasos
  if (Distance == 1000)
  {
 // We are! Reverse direction (invert DIR signal)
    if (digitalRead(DIRECTION_PIN) == LOW)
    {
      digitalWrite(DIRECTION_PIN, HIGH);
    }
    else
    {
      digitalWrite(DIRECTION_PIN, LOW);
    }
    // Reset our distance back to zero since we're
    // starting a new move
    Distance = 0;
    // Now pause for half a second
    delay(100);
}

 if (Distance2 == 800)
  {
 // We are! Reverse direction (invert DIR signal)
    if (digitalRead(aDIRECTION_PIN) == LOW)
    {
      digitalWrite(aDIRECTION_PIN, HIGH);
    }
    else
    {
      digitalWrite(aDIRECTION_PIN, LOW);
    }
    // Reset our distance back to zero since we're
    // starting a new move
    Distance2 = 0;
    // Now pause for half a second
    delay(100);
}

 if (Distance3 == 700)
  {
 // We are! Reverse direction (invert DIR signal)
    if (digitalRead(bDIRECTION_PIN) == LOW)
    {
      digitalWrite(bDIRECTION_PIN, HIGH);
    }
    else
    {
      digitalWrite(bDIRECTION_PIN, LOW);
    }
    // Reset our distance back to zero since we're
    // starting a new move
    Distance3 = 0;
    // Now pause for half a second
    delay(100);
}

    }
  
}





