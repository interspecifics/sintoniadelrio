/*
 - Lee el sensor de lluvia para enviar una señal digital
cuando una gota de agua cae sobre el sensor
 - El interuptor activa un selector de valores analogos
 - Los valores activan un estado
 - cada estado tiene un número de pasos asignado para el motor
 - Logica de de ritmos para los motores
 - Cada sensor controla una caracteristica - Velocidad, resolucion de pasos, secuencia
 - Pasos sobre 1/2, 1/4, 1/8


 -----------------------------
 DRIVER SETUP x TEENSY:

 --- DRIVER 1:
 STEP = 2
 DIR = 3
 MS1 = 7
 MS2 = 4
 ENABLE = 5

 --- DRIVER 2
 STEP = 11
 DIR = 6
 MS1 = 8
 MS2 = 9
 ENABLE = 10

 --- DRIVER 3

 STEP = 12
 DIR = 23
 MS1 = 19
 MS2 = 22
 ENABLE = 21

 -----------------------------


 */





int Distance = 0;  // Grabar el numero de pasos que hemos dado

#define RPMS 200.0
#define STEP_PIN                2
#define DIRECTION_PIN           3
#define GO_PIN                  10

#define STEPS_PER_REV         200
#define MICROSTEPS_PER_STEP     8
#define MICROSECONDS_PER_MICROSTEP   (1000000/(STEPS_PER_REV * MICROSTEPS_PER_STEP)/(RPMS / 60))

long randNumber;
const int randMin = 0;
const int randMax = 300;



uint32_t LastStepTime = 0;
uint32_t CurrentTime = 0;

void setup(){
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIRECTION_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIRECTION_PIN, LOW);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  secuence(analogRead(1));
}

void loop() {

 int scale = map(randNumber, randMin, randMax, 0, 3);

  // print a random number from 0 to 299
  randNumber = random(300);
  //Serial.println("Triger:" randNumber);

switch (scale) {

// ------------------ Numero de pasos por ciclo 2000
    case 0:
CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
  LastStepTime = CurrentTime;
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
  Distance = Distance + 1;   // record this step

  // Revisar si estamos al final de la secuencia de pasos
  if (Distance == 2000)
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
      Serial.println("Comp: 1 2000 pasos");
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);

      break;


 //---------------------------Numero de pasos por ciclo 200
    case 1:

     CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
  LastStepTime = CurrentTime;
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
  Distance = Distance + 1;   // record this step

  // Revisar si estamos al final de la secuencia de pasos
  if (Distance == 200)
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

      Serial.println("Comp: 2 200 pasos");
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);

      break;

   //---------------------------Numero de pasos por ciclo  500
    case 2:

 CurrentTime = micros();
    if ((CurrentTime - LastStepTime) > MICROSECONDS_PER_MICROSTEP)
    {
  LastStepTime = CurrentTime;
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
  Distance = Distance + 1;   // record this step

  // Revisar si estamos al final de la secuencia de pasos
  if (Distance == 500)
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

      Serial.println("500");
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);

      break;

    //---------------------------numero de pasos por ciclo  1000

    case 3:


      Serial.println("1000");
      delayMicroseconds((MICROSECONDS_PER_MICROSTEP * 0.5)/2);
      break;
  }
  delay(1);        // delay in between reads for stability
}
