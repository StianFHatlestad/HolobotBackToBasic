#include <Arduino.h>
#include <Servo.h>
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article

void setup() 
{
  Serial.begin (9600);
 
  // Leonardo: wait for serial port to connect
  while (!Serial) 
    {
    }
 
  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  
  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
      } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
/*
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

  // Set off LCD module
   lcd.begin (16,2); // 16 x 2 LCD module
   lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
   lcd.setBacklight(HIGH);
   lcd.print("Hello, World!");
   lcd.setCursor(0,1);
   lcd.print("Good Day");   

  runMotor("init",pwmLeftMotor,leftMotorDir);//init on the motors
  runMotor("init",pwmRightMotor,rightMotorDir);

  upDownServo.write(pos); //init on the servo
  forkServo.write(pos);
*/
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
  /*
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
          break;
          case 0xFF4AB5: //keypad button "8" // IR backward button pressed
          digitalWrite(leftMotorDir, LOW);
          digitalWrite(rightMotorDir, LOW);
          runMotor("run",pwmLeftMotor,leftMotorDir);
          runMotor("run",pwmRightMotor,rightMotorDir);
          break;
          case 0xFF10EF: //keypad button "4"  IR Left button pressed
          digitalWrite(leftMotorDir, LOW);
          digitalWrite(rightMotorDir, HIGH);
          runMotor("run",pwmLeftMotor,leftMotorDir);
          runMotor("run",pwmRightMotor,rightMotorDir);
          break;
          case 0xFF5AA5: //keypad button "6" IR RIGHT button pressed
          digitalWrite(leftMotorDir, HIGH);
          digitalWrite(rightMotorDir, LOW);
          runMotor("run",pwmLeftMotor,leftMotorDir);
          runMotor("run",pwmRightMotor,rightMotorDir);
          break;
          case 0xFFE01F: //keypad button "vol -" IR drop arm to 0 degrees
          upDownServo.write(0);
          forkServo.write(60);
          delay(2000);
          break;
          case 0xFFA857: //keypad button "vol +" IR lift arm to 60 degrees
          upDownServo.write(60);
          forkServo.write(0);
          delay(2000);
          break;
          }
      irrecv.resume();
  }
  */
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