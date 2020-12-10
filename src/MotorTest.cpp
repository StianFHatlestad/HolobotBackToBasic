/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
/*
#include "Arduino.h"

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(1000);
}

*/

#include <ArduinoBLE.h>
#include "ble/BLE.h"

BLEService batteryService("1101");
BLEUnsignedCharCharacteristic batteryLevelChar("2101", BLERead | BLENotify);
int oldBatteryLevel;

void setup() {
Serial.begin(9600);
while (!Serial);

pinMode(LED_BUILTIN, OUTPUT);
if (!BLE.begin())
{
Serial.println("starting BLE failed!");
while (1);
}

BLE.setLocalName("BatteryMonitor");
BLE.setAdvertisedService(batteryService);
batteryService.addCharacteristic(batteryLevelChar);
BLE.addService(batteryService);

BLE.advertise();
Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() 
{
BLEDevice central = BLE.central();

if (central) 
{
Serial.print("Connected to central: ");
Serial.println(central.address());
digitalWrite(LED_BUILTIN, HIGH);

while (central.connected()) {

      int battery = analogRead(A0);
      int batteryLevel = map(battery, 0, 1023, 0, 100);
      Serial.print("Battery Level % is now: ");
      Serial.println(batteryLevel);
      batteryLevelChar.writeValue(batteryLevel);
      delay(200);

}
}
digitalWrite(LED_BUILTIN, LOW);
Serial.print("Disconnected from central: ");
Serial.println(central.address());
}