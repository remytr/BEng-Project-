#include <AccelStepper.h>
 
long receivedMMdistance = 0; //distance in mm from the computer ie number of steps
long receivedDelay = 0; //delay between two steps, received from the computer ie speed
long receivedAcceleration = 0; //acceleration value from computer ie acceleration
char receivedCommand; //character for commands, character and two numbers
/* s = Start (CCW) // needs steps and speed values, starts the motor
 * o = open (CCW) // needs steps and speed values, clockwise
 * c = close (CW) //needs steps and speed values, anticlockwise
 * a = set acceleration // needs acceleration value , just updates the value of acceleration
 * n = stop right now! // just the 'n' is needed, stops the motor ASAP
 */
 
bool newData, runallowed = false; // booleans for new data from serial, and runallowed flag, newData acts as a switch. runAllowed 
 
 
//no of motors| step pin | DIR pin.
// with the CNC shield, I am only using one A4988 chip on the X stepper motor location. X.STEP is pin 2, and X.DIR is on pin 5.
AccelStepper stepper(1, 2, 5);
 
 
void setup()
{
  Serial.begin(9600); //define baud rate
  Serial.println("Initiate Stepper Motor"); //print a message
 
  //setting up some default values for maximum speed and maximum acceleration
  stepper.setMaxSpeed(2000); //SPEED = Steps / second, 2000 steps per second, if it is set up in 400 microsteps , 5 revolution will take a second
 
  stepper.disableOutputs(); //disable outputs, so the motor is not getting warm (no current)
 
 
}
 
void loop()
{
 
  checkSerial(); //check serial port for new commands
 
  continuousRun2(); //method to handle the motor
 
}
 
 
void continuousRun2() //method for the motor
{
  if (runallowed == true)
  {
    if (abs(stepper.currentPosition()) < receivedMMdistance) //abs() is needed because of the '<' 
    {
      stepper.enableOutputs(); //enable pins
      stepper.run(); //step the motor (this will step the motor by 1 step at each loop)
    }
    else //program enters this part if the required distance is completed
    {
     
      runallowed = false; //disable running -> the program will not try to enter this if-else anymore
      stepper.disableOutputs(); // disable power
      Serial.print("POS: ");
      Serial.println(stepper.currentPosition()); // print pos -> this will show you the latest relative number of steps
      stepper.setCurrentPosition(0); //reset the position to zero
      Serial.print("POS: ");
      Serial.println(stepper.currentPosition()); // print pos -> this will show you the latest relative number of steps; we check here if it is zero for real
    }
 
 
  }
  else //program enters this part if the runallowed is FALSE, we do not do anything
  {
    return;
 
  }
}
 
void checkSerial() //method for receiving the commands, checks the serial port whether there are comments.
{  
  //switch-case would also work, and maybe more elegant
 
  if (Serial.available() > 0) //if something comes
  {
    receivedCommand = Serial.read(); // this will read the command character
    newData = true; //this creates a flag
  }
 
  if (newData == true) //if we received something (see above)
  {
    //START - MEASURE
    if (receivedCommand == 's') //this is the measure part
    {
      //example s 2000 500 - 2000 steps (5 revolution with 400 step/rev microstepping) and 500 steps/s speed
      runallowed = true; //allow running
     
 
      receivedMMdistance = Serial.parseFloat(); //value for the steps
      receivedDelay = Serial.parseFloat(); //value for the speed
 
      Serial.print(receivedMMdistance); //print the values for checking if Arduino received the numbers
      Serial.print(receivedDelay);
      Serial.println("Measure "); //print the action
      stepper.setMaxSpeed(receivedDelay); //set speed
      stepper.move(receivedMMdistance); //set distance
 
    }
    //START - OPEN
    if (receivedCommand == 'o') //OPENING
    {
      //example o 2000 500 - 2000 steps (5 revolution with 400 step/rev microstepping) and 500 steps/s speed
      runallowed = true; //allow running
     
 
 
      receivedMMdistance = Serial.parseFloat(); //value for the steps
      receivedDelay = Serial.parseFloat(); //value for the speed
 
      Serial.print(receivedMMdistance); //print the values for checking
      Serial.print(receivedDelay);
      Serial.println("OPEN "); //print the action
      stepper.setMaxSpeed(receivedDelay); //set speed
      stepper.move(receivedMMdistance); //set distance
 
    }
 
    //START - CLOSE
    if (receivedCommand == 'c') //CLOSING - Rotates the motor in the opposite direction as opening
    {
      //example c 2000 500 - 2000 steps (5 revolution with 400 step/rev microstepping) and 500 steps/s speed; will rotate in the other direction
      runallowed = true; //allow running
     
 
 
      receivedMMdistance = Serial.parseFloat(); //value for the steps
      receivedDelay = Serial.parseFloat(); //value for the speed
 
      Serial.print(receivedMMdistance);  //print the values for checking
      Serial.print(receivedDelay);
      Serial.println("CLOSE "); //print action
      stepper.setMaxSpeed(receivedDelay); //set speed
      stepper.move(-1 * receivedMMdistance); ////set distance - negative value flips the direction
 
    }
 
    //STOP - STOP
    if (receivedCommand == 'n') //immediately stops the motor
    {
      runallowed = false; //disable running
       
      stepper.setCurrentPosition(0); // reset position
      Serial.println("STOP "); //print action
      stepper.stop(); //stop motor
      stepper.disableOutputs(); //disable power
 
    }
 
    //SET ACCELERATION
    if (receivedCommand == 'a') //Setting up a new acceleration value
    {
      runallowed = false; //we still keep running disabled, since we just update a variable
     
      receivedAcceleration = Serial.parseFloat(); //receive the acceleration from serial
 
      stepper.setAcceleration(receivedAcceleration); //update the value of the variable
 
      Serial.println("Acceleration Updated "); //confirm update by message
 
    }
 
  }
  //after we went through the above tasks, newData becomes false again, so we are ready to receive new commands again.
  newData = false;
 
 
}
