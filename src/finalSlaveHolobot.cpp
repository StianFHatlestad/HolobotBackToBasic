//== SLAVE CODE ==
#include <Adafruit_TiCoServo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Adafruit_TiCoServo myServoLift;
Adafruit_TiCoServo myServoTilt;

int yLeftpotValue = 0;

int state = 140;
int state2 = 140;
int state4 = 140;
int state5 = 140;
int servoInc1 = 1500;
int servoInc2 = 1750;

int dir_a = 2;  //direction control for motor outputs 1 and 2
int dir_b = 8;  //direction control for motor outputs 3 and 4 
int pwm_a = 3;  //PWM control for motor outputs 1 and 2
int pwm_b = 9;  //PWM control for motor outputs 3 and 4  

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 5000;  //the value is a number of milliseconds
const unsigned long periodClosed = 5300; // eyes closed period

//Setting the custom char bytes 
byte blackBox[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte topLeftEye[8] = {
  B00011,
  B00111,
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte bottomLeftEye[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111,
  B00011,
};

byte topRightEye[8] = {
  B11000,
  B11100,
  B11110,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte bottomRightEye[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100,
  B11000,
};

byte happyLeftEye[8] = {
  B11111,
  B11100,
  B11000,
  B10000,
  B00000,
  B00000,
  B00000,
};

byte happyRightEye[8] = {
  B11111,
  B00111,
  B00011,
  B00001,
  B00000,
  B00000,
  B00000,
};

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article


void setup() {
  myServoLift.attach(12, 1000, 2000);
  myServoTilt.attach(11, 1500, 2000);

  Serial1.begin(38400); // Default communication rate of the Bluetooth module
  
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  pinMode( 19, INPUT_PULLUP ); //for use of Serial1 you need to sett pin 19 to pullup

  lcd.begin (16,2); // 16 x 2 LCD module
  lcd.createChar(0, blackBox);// creating custom char
  lcd.createChar(1, topLeftEye); 
  lcd.createChar(2, bottomLeftEye);
  lcd.createChar(3, topRightEye);
  lcd.createChar(4, bottomRightEye);
  lcd.createChar(5, happyLeftEye);
  lcd.createChar(6, happyRightEye);
  lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
  lcd.setBacklight(HIGH);
  setHappyEye(); //initial start of the LCD eyes

  startMillis = millis();  //initial start time
}

//This function sets the LCD eyes 
void setHappyEye(){
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

void loop() {
 if(Serial1.available() > 0){ // Checks whether data is comming from the serial port1
    if (Serial1.read() == 'X'){
      state = Serial1.read(); // Reads the data from the serial port
      state = state + 3; // + 3 added to remove stutter
    }
    if (Serial1.read() == 'Y'){
      state2 = Serial1.read(); // Reads the data from the serial port
      state2 = state2 + 3; // + 3 added to remove stutter
    }
    if (Serial1.read() == 'C'){
      state4 = Serial1.read(); // Reads the data from the serial port
      state4 = state4 + 3; // + 3 added to remove stutter
    }
    if (Serial1.read() == 'V'){
      state5 = Serial1.read(); // Reads the data from the serial port
      state5 = state5 + 3; // + 3 added to remove stutter
    }  
 }
 
 // Controles for the left motor or motor A based on the joystick Y value on the left joystick
 if(state2 < 100 && state2 > 2){
   digitalWrite(dir_a, LOW);//Backwards for A 
   analogWrite(pwm_a, 255); //Max speed
 }

 if((state2 > 100) && (state2 < 180)){
  analogWrite(pwm_a, 0); 
 }
 
 if(state2 > 180){
   digitalWrite(dir_a, HIGH); //Forward for A 
   analogWrite(pwm_a, 255); //Max speed
 }
 
 // Controles for the right motor or motor b based on the joystick Y value on the right joystick
  if(state5 < 90 && state5 > 2){
   digitalWrite(dir_b, LOW);//Backwards for B
   analogWrite(pwm_b, 255); //Max speed
 }

 if((state5 > 100) && (state5 < 180)){
  analogWrite(pwm_b, 0); 
 }
 
 if(state5 > 180){
   digitalWrite(dir_b, HIGH); //Forward for B
   analogWrite(pwm_b, 255); //Max speed
 }
 
 //Reads the X value from the right joystick and canges the value of Servo 1 and 2 bassed on the direction. 
 //>2 is added to decrease stutter.  
 if(state4 < 90 && state4 > 2){
   if(servoInc1 >= 1000){
   servoInc1 = servoInc1 - 20;
   if(servoInc2 >= 1500){
   servoInc2 = servoInc2 - 20; 
   }
   }
 }
 
 if(state4 > 180){
   if(servoInc1 <= 2000){
   servoInc1 = servoInc1 + 20;
   if(servoInc2 <= 2000){
   servoInc2 = servoInc2 + 20; 
   }
   } 
 }

//Reads the X value from the slave and increase ServoInc2 bassed on the direction
 if(state < 90 && state > 2){
   if(servoInc2 >= 1500){
   servoInc2 = servoInc2 - 20; 
   }
 }
 
 if(state > 180){
   if(servoInc2 <= 2000){
   servoInc2 = servoInc2 + 20; 
   }
 } 
 
 //Write to the servoes Servi
 myServoLift.write(servoInc1);
 myServoTilt.write(servoInc2);
 
currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period){  //test whether the period has elapsed
  
    lcd.clear();
    if (currentMillis - startMillis >= periodClosed){
      setHappyEye(); //Set the eyes
      startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
    }
  }
 
 delay(10); //Delay to sync the Arduinoes bether

}