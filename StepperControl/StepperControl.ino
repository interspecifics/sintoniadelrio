int Distance = 0;  // Grabar el numero de pasos que hemos dado

// Define our maximum and minimum speed in steps per second (scale pot to these)
#define RPMS 100.0
#define STEP_PIN                2
#define DIRECTION_PIN           3
#define GO_PIN                  10

#define STEPS_PER_REV         200
#define MICROSTEPS_PER_STEP     8
#define MICROSECONDS_PER_MICROSTEP   (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(RPMS / 60))


uint32_t LastStepTime = 0;
uint32_t CurrentTime = 0;


void setup() {               
  pinMode(STEP_PIN, OUTPUT);    
  pinMode(DIRECTION_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIRECTION_PIN, LOW);
}

void loop() {
   if (digitalRead(GO_PIN) == LOW)
  {
    CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
  LastStepTime = CurrentTime;
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);       
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.9)/2);
  Distance = Distance + 1;   // record this step
 
  // Revisar si estamos al final de la secuencia de pasos
  if (Distance == 100)
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
    delay(500);

   
  }
}
}
}
