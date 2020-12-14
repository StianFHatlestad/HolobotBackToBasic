// MASTER CODE 

int xLeftpotValue = 0;
int yLeftpotValue = 0;

int xRightpotValue = 0;
int yRightpotValue = 0;
 
void setup() {
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}

void loop() {
 // Reading the potentiometer
  xLeftpotValue = analogRead(A0);
  yLeftpotValue = analogRead(A1);
  xRightpotValue = analogRead(A2);
  yRightpotValue = analogRead(A3);
 
  //Mapping ov the values gained from the Joystics. 0, 1023 is the normal joystic inputt from each diraction 
  int xLeftpotValueMapped = map(xLeftpotValue, 0, 1023, 0, 255);
  int yLeftpotValueMapped = map(yLeftpotValue, 0, 1023, 0, 255);
  int xRightpotValueMapped =map (xRightpotValue, 0, 1023, 0, 255);
  int yRightpotValueMapped =map (yRightpotValue, 0, 1023, 0, 255);
  
  //Writes to the slave over serial. X, Y, C, V are sendt over for reffrence to the slave.
  Serial.write("X");
  Serial.write(xLeftpotValueMapped); // Sends potValue to servo motor
  Serial.write("Y");
  Serial.write(yLeftpotValueMapped); // Sends potValue to servo motor
  Serial.write("C");
  Serial.write(xRightpotValueMapped); // Sends potValue to servo motor
  Serial.write("V");
  Serial.write(yRightpotValueMapped); // Sends potValue to servo motor

  delay(10); //Delay to sync the Arduinoes bether
}