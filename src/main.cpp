#include <Arduino.h>
#include <Servo.h>
#include <IRremote.h>

Servo upDownServo;  // create servo object to control a servo
Servo forkServo;
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

const int RECV_PIN = 12; // variable to store IR-Reciever position
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
/*
const int pwm = 2 ; //initializing pin 2 as pwm
const int in_1 = 8 ;
const int in_2 = 9 ;
//For providing logic to L298 IC to choose the direction of the DC motor
*/

const int rightMotorDir = 2;
const int pwmRightMotor = 3;
const int servoMG955 = 6;
const int leftMotorDir = 8;
const int pwmLeftMotor = 9;
const int servoSG90 = 11;
//Digital pin 12 is taken

void setup() 
{
  irrecv.enableIRIn();
  irrecv.blink13(true);
  upDownServo.attach(servoMG955);  // attaches the servo on pin 9 to the servo object
  forkServo.attach(servoSG90);

  pinMode(pwmRightMotor,OUTPUT); //we have to set PWM pin as output
  pinMode(pwmLeftMotor,OUTPUT); 
  pinMode(rightMotorDir,OUTPUT);//Logic pins are also set as output
  pinMode(leftMotorDir, OUTPUT);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  runMotor("init",pwmLeftMotor,leftMotorDir);//init on the motors
  runMotor("init",pwmRightMotor,rightMotorDir);

  upDownServo.write(pos); //init on the servo
  forkServo.write(pos);

}

void runMotor(String mode, int pwm, int dir)
{
  if (mode.equals("init"))
  {
    analogWrite(pwm, 255); delay(2000);
    analogWrite(pwm, 0); delay(1000); 
  }
  else
  {
    delay(2000);

    for (int i = 0; i < 3; i++)
    {
      // we do serial runs of minimum speed (63 = 25%), half speed (127 = 50%) and full speed (255 = 100%)
      analogWrite(pwm, pow(2,i+6)-1);
      delay(1500);
      analogWrite(pwm, 0);
      delay(1000);
    }
  }
  
}

void loop() 

{
  if (irrecv.decode(&results))
  {
    if (results.value == 0XFFFFFFFF)
    results.value = key_value;

     switch(results.value){
          case 0xFF18E7: //Keypad button "2" // IR forward button pressed
          digitalWrite(leftMotorDir, HIGH);
          digitalWrite(rightMotorDir, HIGH);
          runMotor("run",pwmLeftMotor,leftMotorDir);
          runMotor("run",pwmRightMotor,rightMotorDir);
          }
      irrecv.resume();
  }

  // IR forward button pressed
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, HIGH);
  runMotor("run",pwmLeftMotor,leftMotorDir);
  runMotor("run",pwmRightMotor,rightMotorDir);

  // IR backwards button pressed
  digitalWrite(leftMotorDir, LOW);
  digitalWrite(rightMotorDir, LOW);
  runMotor("run",pwmLeftMotor,leftMotorDir);
  runMotor("run",pwmRightMotor,rightMotorDir);

  // IR right button pressed
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, LOW);
  runMotor("run",pwmLeftMotor,leftMotorDir);
  runMotor("run",pwmRightMotor,rightMotorDir);

  // IR left button pressed
  digitalWrite(leftMotorDir, LOW);
  digitalWrite(rightMotorDir, HIGH);
  runMotor("run",pwmLeftMotor,leftMotorDir);
  runMotor("run",pwmRightMotor,rightMotorDir);

  // IR lift box button
  upDownServo.write(90);
  delay(2000);
  // IR place box button
  upDownServo.write(0);
  delay(2000);


  /*
  for (pos = 0; pos <= 180; pos += 1)
  { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) 
  { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
}