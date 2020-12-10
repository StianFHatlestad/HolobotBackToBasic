#include <Arduino.h>
//#include <Servo.h>
#include <VarSpeedServo.h> 
#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <AFMotor.h>

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long startMillisMotor;
unsigned long currentMillis;
const unsigned long period = 5000;  //the value is a number of milliseconds
const unsigned long periodClosed = 5300;

VarSpeedServo upDownServo;    // create servo object to control a servo 
VarSpeedServo forkServo;    // create servo object to control a servo 

// twelve servo objects can be created on most boards
int pos = 90;    // variable to store the servo position

unsigned long key_value = 0;

const int RECV_PIN = 2; // variable to store IR-Reciever position
//const int pwmRightMotor = 3;
//const int leftMotorDir = 4;
//const int rightMotorDir = 7;
const int servoMG955 = 9;
const int servoSG90 = 10;
//const int pwmLeftMotor = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

AF_DCMotor motor1(1,MOTOR12_64KHZ);
AF_DCMotor motor2(2,MOTOR12_64KHZ);

byte blackBox[8] = 
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte topLeftEye[8] = 
{
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte bottomLeftEye[8] = 
{
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111,
  B00011,
};

byte topRightEye[8] = 
{
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte bottomRightEye[8] = 
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
};

byte happyLeftEye[8] = 
{
  B11111,
  B11100,
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
};

byte happyRightEye[8] = 
{
  B11111,
  B00111,
  B00011,
  B00001,
  B00000,
  B00000,
  B00000,
};

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article

void setup() 
{
 
  Serial.begin (9600);
/* 
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
  */

  irrecv.enableIRIn();
  irrecv.blink13(true);
  upDownServo.attach(servoMG955);  // attaches the servo on pin 9 to the servo object
  forkServo.attach(servoSG90);

  irrecv.enableIRIn();
  irrecv.blink13(true);

  // Set off LCD module
  lcd.begin (16,2); // 16 x 2 LCD module
  lcd.createChar(0, blackBox);
  lcd.createChar(1, topLeftEye);
  lcd.createChar(2, bottomLeftEye);
  lcd.createChar(3, topRightEye);
  lcd.createChar(4, bottomRightEye);
  lcd.createChar(5, happyLeftEye);
  lcd.createChar(6, happyRightEye);
  lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
  lcd.setBacklight(HIGH);
  setHappyEye();

  //init on the servo
  upDownServo.write(pos);
  forkServo.write(pos);

  motor1.setSpeed(250);
  motor2.setSpeed(250);

  startMillis = millis();  //initial start time
}

void setEyes()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.write(byte(1));
  lcd.setCursor(3,0);
  lcd.write(byte(0));
  lcd.setCursor(4,0);
  lcd.write(byte(3));
  lcd.setCursor(11,0);
  lcd.write(byte(1));
  lcd.setCursor(12,0);
  lcd.write(byte(0));
  lcd.setCursor(13,0);
  lcd.write(byte(3));
  lcd.setCursor(2,1);
  lcd.write(byte(2));
  lcd.setCursor(3,1);
  lcd.write(byte(0));
  lcd.setCursor(4,1);
  lcd.write(byte(4));
  lcd.setCursor(11,1);
  lcd.write(byte(2));
  lcd.setCursor(12,1);
  lcd.write(byte(0));
  lcd.setCursor(13,1);
  lcd.write(byte(4));
}

void setHappyEye()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.write(byte(1));
  lcd.setCursor(3,0);
  lcd.write(byte(0));
  lcd.setCursor(4,0);
  lcd.write(byte(3));
  lcd.setCursor(11,0);
  lcd.write(byte(1));
  lcd.setCursor(12,0);
  lcd.write(byte(0));
  lcd.setCursor(13,0);
  lcd.write(byte(3));
  lcd.setCursor(2,1);
  lcd.write(byte(5));
  lcd.setCursor(4,1);
  lcd.write(byte(6));
  lcd.setCursor(11,1);
  lcd.write(byte(5));
  lcd.setCursor(13,1);
  lcd.write(byte(6));
}

void loop() 

{
  
  if (irrecv.decode(&results))
  {
    Serial.print("IR");
    if (results.value == 0XFFFFFFFF)
    results.value = key_value;
    uint8_t i;
    switch(results.value)
    {
      case 0xFF18E7: //Keypad button "2" // IR forward button pressed
      Serial.print("Forward");
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      startMillisMotor = currentMillis;
      break;
      case 0xFF4AB5: //keypad button "8" // IR backward button pressed
      Serial.print("Backwards");
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      startMillisMotor = currentMillis;
      break;
      case 0xFF10EF: //keypad button "4"  IR Left button pressed
      Serial.print("Left");
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      startMillisMotor = currentMillis;
      break;
      case 0xFF5AA5: //keypad button "6" IR RIGHT button pressed
      Serial.print("Right");
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      startMillisMotor = currentMillis;
      break;
      case 0xFFE01F: //keypad button "vol -" IR drop arm to 90 degrees
      /*
      upDownServo.write(90); //90 min strait, 180 max up 
      forkServo.write(0); //0 min down, 90 max strait
      */
      Serial.print("Down");
      upDownServo.write(90, 30, false);        // move to 180 degrees, use a speed of 30, wait until move is complete
      forkServo.write(90, 30, true);        // move to 0 degrees, use a speed of 30, wait until move is complete
      delay(2000);
      break;
      case 0xFFA857: //keypad button "vol +" IR lift arm to 180 degrees
      /*
      upDownServo.write(180);
      forkServo.write(90);
      */
      Serial.print("Up");
      upDownServo.write(180, 30, false);        // move to 180 degrees, use a speed of 30, wait until move is complete
      forkServo.write(180, 30, true);        // move to 0 degrees, use a speed of 30, wait until move is complete
      delay(2000);
      break;
    }
      irrecv.resume();
  }
  
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    lcd.clear();
    if (currentMillis - startMillis >= periodClosed)
    {
      setHappyEye();
      startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
    }
  }
  if(currentMillis - startMillisMotor >= period)
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
}