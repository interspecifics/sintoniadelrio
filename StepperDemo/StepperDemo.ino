/******************************************************************************

[HIGH/LOW functionality ]
______________________________
[MS1] - [MS2] - [RESOLUTION]
[ L ] - [ L ] - [FULL STEP ]
[ H ] - [ L ] - [HALF STEP ]
[ L ] - [ H ] - [QUARTER STEP]
[ H ] - [ H ] - [EIGHT STEP]

******************************************************************************/
//Librerias
#include <AccelStepper.h>

//Declare pin functions 
#define stp 2 // Logic Input. transition from LOW to HIGH will trigger the motor to step forward one step
#define dir 3 // Logic Input. This pin determines the direction of motor rotation
#define MS1 7 // Logic Input. HIGH/LOW functionality
#define MS2 4 // Logic Input. HIGH/LOW functionality
#define EN  5 // Enables the FET functionality within the motor driver. Set to LOW to enable FETs allowing motor control


//Declare variables for functions
char user_input;
int x;
int y;
int state;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Iniciar control del motor");
  Serial.println();
  //Print function list for user selection
  Serial.println("ingresa el numero en la terminal para controlar tu motor:");
  Serial.println("1. Giro el motor en micropasos.");
  Serial.println("2. Reversa en micropasos.");
  Serial.println("3. Girar a 1/8 de micropasos.");
  Serial.println("4. Paso completo hacia adelante y reversa.")
  Serial.println();
}

//Main loop
void loop() {
  while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
      if (user_input =='1')
      {
         StepForwardDefault();
      }
      else if(user_input =='2')
      {
        ReverseStepDefault();
      }
      else if(user_input =='3')
      {
        SmallStepMode();
      }
      else if(user_input =='4')
      {
        ForwardBackwardStep();
      }
      else
      {
        Serial.println("Ingresa una nueva orden");
      }
      resetEDPins();
  }
}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(EN, HIGH);
}

//Default microstep mode function
void StepForwardDefault()
{
  Serial.println(">> [El motor se mueve hacia adelante]");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println(" _ Prueba una nueva opcion _");
  Serial.println();
}

//Reverse default microstep mode function
void ReverseStepDefault()
{
  Serial.println(">> [El motor gira en reversa]");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  for(x= 1; x<1000; x++)  //Loop the stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("_ Prueba una nueva opcion _");
  Serial.println();
}

// 1/8th microstep foward mode function
void SmallStepMode()
{
  Serial.println("Stepping at 1/8th microstep mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2, HIGH);
  for(x= 1; x<1000; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

//Forward/reverse stepping function
void ForwardBackwardStep()
{
  Serial.println("Alternate between stepping forward and reverse.");
  for(x= 1; x<5; x++)  //Loop the forward stepping enough times for motion to be visible
  {
    //Read direction pin state and change it
    state=digitalRead(dir);
    if(state == HIGH)
    {
      digitalWrite(dir, LOW); // adelante      dir.runSpeed();

    }
    else if(state ==LOW)
    {
      digitalWrite(dir,HIGH); // atras

    }

    for(y=1; y<1000; y++)
    {
      digitalWrite(stp,HIGH); //Trigger one step
      delay(1);
      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
      delay(1);
    }
  }
  Serial.println("Enter new option:");
  Serial.println();
}
