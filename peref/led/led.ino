#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>
int a;
DynamixelDevice led(21);
void setup() {
  DxlMaster.begin(57600);
  Serial.begin(57600);
  led.init();
  
}

void loop() {
  led.write(26,255);
  led.write(27,255);
  led.write(28,255);
  Serial.println(a);
}
