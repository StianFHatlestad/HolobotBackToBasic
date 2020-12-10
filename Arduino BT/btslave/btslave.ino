/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == SLAVE CODE ==
 */
 
#include <Servo.h>
#define button 8
Servo myServo;
int state = 0;
int buttonState = 0;
void setup() {
  pinMode(button, INPUT);
  myServo.attach(9);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() {
 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }
 // Controlling the servo motor
// myServo.write(state);
Serial.print(state);
//Serial.print(debug);
Serial.print("debug \n");
 delay(1000);
 
 // Reading the button

/*buttonState = digitalRead(button);
 if (buttonState == HIGH) {
   Serial.write('1'); // Sends '1' to the master to turn on LED
 }
 else {
   Serial.write('0');
 }*/  
}
