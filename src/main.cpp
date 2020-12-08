#include <Arduino.h>
#include <Servo.h>
#include <IRremote.h>

Servo rightServo;  // create servo object to control a servo
Servo leftServo;
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position

const int RECV_PIN = 12; // variable to store IR-Reciever position
IRrecv irrecv(RECV_PIN);
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
  Serial.begin(9600);
  rightServo.attach(servoMG955);  // attaches the servo on pin 9 to the servo object
  leftServo.attach(servoSG90);

   pinMode(pwmRightMotor,OUTPUT); //we have to set PWM pin as output
   pinMode(pwmLeftMotor,OUTPUT); 
   pinMode(rightMotorDir,OUTPUT);//Logic pins are also set as output
   pinMode(leftMotorDir, OUTPUT);
   irrecv.enableIRIn();
   irrecv.blink13(true);
}

void moveFarward()
{

}

void loop() 

{
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
  /*
   while(! Serial)
   Serial.println("Speed 0 to 255");
   
   if (Serial.available()) 
   {
      int speed = Serial.parseInt();
      if (speed >= 0 && speed <= 255) 
      {
         analogWrite(pwm, speed);
      }
   }
   //For Clock wise motion , in_1 = High , in_2 = Low
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,LOW) ;
   //analogWrite(pwm,255) ;
*/
   /* setting pwm of the motor to 255 we can change the speed of rotation
   by changing pwm input but we are only using arduino so we are using highest
   value to driver the motor */
   //Clockwise for 3 secs
 /* 
   delay(3000) ;
   
   //For brake
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,HIGH) ;
   delay(1000) ;
   
   //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,HIGH) ;
   delay(3000) ;

   //For brake
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,HIGH) ;
   delay(1000) ;


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