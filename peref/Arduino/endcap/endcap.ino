#include <DxlMaster.h>
#include <Dynamixel.h>
#include <DynamixelConsole.h>
#include <DynamixelDevice.h>
#include <DynamixelInterface.h>
#include <DynamixelInterfaceArduinoImpl.h>
#include <DynamixelMotor.h>
int a;
DynamixelDevice endcap(23);
void setup() {
  DxlMaster.begin(57600);
  Serial.begin(57600);
  endcap.init();
  
}

void loop() {
  endcap.read(27,a);
  Serial.println(a);
}
