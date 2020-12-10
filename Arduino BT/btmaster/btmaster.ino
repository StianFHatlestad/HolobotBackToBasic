/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == MASTER CODE ==
 */
#define joy1X A0
#define joy1Y A1
#define joy2X A2
#define joy2Y A3
#define ledPin 13



int x1Value, y1Value, x2Value, y2Value;
//#define ledPin 9
//int state = 0;
//int potValue = 0;
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() {
  x1Value = analogRead(joy1X);
  y1Value = analogRead(joy1Y);
  x2Value = analogRead(joy2X);
  y2Value = analogRead(joy2Y);


 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }
 // Controlling the LED
 Serial.print(state);
 if (state == '1') {
  digitalWrite(ledPin, HIGH); // LED ON
  state = 0;
 }
 else if (state == '0') {
  digitalWrite(ledPin, LOW); // LED ON
  state = 0; }
  
  //print the values with to plot or view
  Serial.write(x1Value);
  Serial.write(y1Value);
  Serial.write(x2Value);
  Serial.write(y2Value);
  Serial.print(x1Value);
  Serial.print("\t");
 Serial.println(y1Value);
  
  /*
 if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }
 // Controlling the LED
 if (state == '1') {
  digitalWrite(ledPin, HIGH); // LED ON
  state = 0;
 }
 else if (state == '0') {
  digitalWrite(ledPin, LOW); // LED ON
  state = 0;
 }
 // Reading the potentiometer
 potValue = analogRead(A0);
 int potValueMapped = map(potValue, 0, 1023, 0, 255);
 Serial.write(potValueMapped); // Sends potValue to servo motor
 delay(10);
 */
}
