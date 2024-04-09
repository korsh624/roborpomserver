#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>
int a;
DynamixelDevice but(3);
void setup() {
  DxlMaster.begin(57600);
  Serial.begin(57600);
  but.init();
  
}

void loop() {
  but.read(27,a);
  Serial.println(a);
}
