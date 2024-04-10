


#include <Ethernet.h>
#include <EthernetUdp.h>
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 42, 17);
#define lamp_ip "192.168.42.16"
#define manip_ip "192.168.42.12"
#define conveer_ip "192.168.42.15"
unsigned int localPort = 8888;      // local port to listen on

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged";        // a string to send back
EthernetUDP Udp;
bool flag = false;
void setup() {
  Ethernet.init(10);  // Most Arduino shields
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start UDP
  Udp.begin(localPort);
}
void moveManipulator(int x, int y, int z, int a, int g)
{
  char buffer[50];

  sprintf(buffer, "g:%d:%d:%d:%d:%d#", x, y, a, z, g);
  Udp.beginPacket(manip_ip, 8888);
  Udp.write(buffer);
  Udp.endPacket();
  memset(buffer, 0, sizeof(buffer));
}
void setConveer(int speed) {
  char buffer[50];
  sprintf(buffer, "s:%d#", speed);
  Udp.beginPacket(conveer_ip, 8888);
  Udp.write(buffer);
  Udp.endPacket();
  memset(buffer, 0, sizeof(buffer));
  delay(100);
}
void loop() {
//
//  setlamp("l:0:0:1:0#");
//  moveManipulator(150, 80, 140, 0, 0);
//  delay(2000);
//  moveManipulator(163, -140, 140, 0, 0);
//  delay(2000);
//  moveManipulator(163, -140, -10, 0, 0);
//  delay(100);
//  moveManipulator(163, -140, -10, 0, 1);
//  delay(2000);
//  moveManipulator(163, -140, 140, 0, 1);
//  delay(2000);
//  moveManipulator(160, 80, 5, 0, 1);
//  delay(100);
//  moveManipulator(160, 80, 5, 0, 0);
//  delay(2000);
//  moveManipulator(150, 80, 140, 0, 0);
//  delay(2000);
//  setConveer(200);
//  delay(2000);
//  setConveer(0);
//  delay(1000);
//  setlamp("l:0:0:0:1#");//r,b,g,y
//  setlampRGBY(1, 0, 0, 0);
//  delay(500);
//  setlampRGBY(0, 1, 0, 0);
//  delay(500);
//  setlampRGBY(0, 0, 1, 0);
//  delay(500);
//  setlampRGBY(0, 0, 0, 1);
//  delay(500);
}
void setlamp(String message ) {
  Udp.beginPacket("192.168.42.16", 8888);
  char Buf[50];
  message.toCharArray(Buf, 50);
  Udp.write(Buf);
  Udp.endPacket();
  delay(100);
}
void setlampRGBY(bool r, bool y, bool g, bool b) {
  char buffer[50];
  sprintf(buffer, "l:%d:%d:%d:%d#", r, b, g, y);
  Udp.beginPacket(lamp_ip, 8888);
  Udp.write(buffer);
  Udp.endPacket();
  memset(buffer, 0, sizeof(buffer));
  delay(100);
}
