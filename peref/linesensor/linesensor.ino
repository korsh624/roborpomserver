#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>
int a;
DynamixelDevice linesensor(10);
void setup() {
  DxlMaster.begin(57600);
  Serial.begin(57600);
  linesensor.init();
  
}

void loop() {
  linesensor.read(27,a);
  Serial.println(a);
}
