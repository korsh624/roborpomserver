#include <Ethernet.h>
#include <SPI.h>
#include <EthernetUdp.h>
#include <EEPROM.h>

#define UDP_PORT 8888

IPAddress MyIP(192, 168, 33, 211);
IPAddress MANIPULATOR(192, 168, 33, 12);
IPAddress CAMERA(192, 168, 33, 13);
IPAddress TERMINAL(192, 168, 33, 14);
IPAddress CONVEYOR(192, 168, 33, 15);
IPAddress IR(192, 168, 33, 16);
IPAddress server(192, 168, 33, 226);
IPAddress myDns(192, 168, 33, 1);
EthernetClient client;
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement
EthernetUDP udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
//byte mac[6];

byte detailZ = 50;
byte manipulatorStatus = 1;
byte irStatus = 0;
byte irStatusMemo = 0;
byte onConveyor = 0;

void sendTerminal(byte r = 0, byte b = 0, byte g = 0, byte y = 0, byte row = 0, String msg = "") {
  if (r > 1) r = 1; if (g > 1) g = 1; if (b > 1) b = 1; if (y > 1) y = 1; if (row > 3) row = 3;
  String o = "r:" + (String)r + ":" + (String)b + ":" + (String)g + ":" + (String)y + ":" + (String)row + ":" + msg + "#";
  sendUdp(TERMINAL, o);
}

void getNewDetail() {
  moveManipulator(180, 0, 100, 0);
  moveManipulator(140, -200, 60, 1);  //0
  moveManipulator(140, -200, detailZ, 1);
  detailZ -= 7;
  moveManipulator(140, -200, 100, 1);
  moveManipulator(180, 0, 100, 1);
  moveManipulator(180, 0, 8, 0);
  moveManipulator(180, 0, 6, 0);
  moveManipulator(180, 0, 100, 0);
}

void processUdp() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Serial.print("From ");
    // IPAddress remote = udp.remoteIP();
    // for (int i = 0; i < 4; i++) {
    //   Serial.print(remote[i], DEC);
    //   if (i < 3) {
    //     Serial.print(".");
    //   }
    // }
    // Serial.print(", port ");
    // Serial.println(udp.remotePort());
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    // Serial.println("Contents:");
    // Serial.println(packetBuffer);
    if (packetBuffer[0] == 'M') {
      Serial.print("MANIPULATOR STATUS: ");
      byte counter = 0;
      byte ind = 0;
      for (int i = 0; i < 7; i++) {
        if (packetBuffer[i] == ':') {
          counter++;
          continue;
        }
        if (packetBuffer[i] != ':' && counter < 2) {
          continue;
        } else {
          ind = i;
          break;
        }
        if (counter > 2) break;
      }
      Serial.println("STATUS: " + (String)packetBuffer[ind]);
      manipulatorStatus = packetBuffer[ind] == '0' ? 0 : 1;
      return;
    }
    irStatusMemo = irStatus;
    if (packetBuffer[0] == 'I') {
      Serial.print("IR");
      irStatus = packetBuffer[2] == '1' ? 1 : 0;
      Serial.print(" STATUS: ");
      Serial.print(irStatus);
      Serial.println();
    }
  }
}

void requestIR() {
  sendUdp(IR, "i:r#");
}

void moveConveyor(int speed) {
  String o = "s:" + (String)speed + "#";
  sendUdp(CONVEYOR, o);
}

void moveManipulator(int x, int y, int z, int g) {
  String o = "g:" + (String)x + ":" + (String)y + ":0:" + (String)z + ":" + (String)g + "#";
  sendUdp(MANIPULATOR, "r#");
  sendUdp(MANIPULATOR, o);
  manipulatorStatus = 1;
  unsigned long timeout = millis() + 5000;
  do {
    processUdp();
    if (manipulatorStatus == 1) {
      break;
    }
    delay(10);
  } while (manipulatorStatus == 1 || millis() < timeout);
  sendUdp(MANIPULATOR, "s#");
}

void sendUdp(IPAddress adr, String msg) {
  char out[msg.length() + 1];
  msg.toCharArray(out, msg.length() + 1);
  udp.beginPacket(adr, UDP_PORT);
  udp.write(out);
  udp.endPacket();
  Serial.println(out);
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Ethernet.begin(mac, MyIP,myDns);
  udp.begin(UDP_PORT);
  Serial.println("----------------------");
  Serial.println("UDP connection is at: ");
  Serial.println(Ethernet.localIP());
  Serial.println("----------------------");
  if (client.connect(server, 5000)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET  /hardinfo?station=12 HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  beginMicros = micros();
//
//  sendTerminal(1, 0, 1, 0, 0, "COUNT:");
//  sendTerminal(1, 0, 1, 0, 1, "0");
//  getNewDetail();
//  moveConveyor(100);
//  do {
//    requestIR();
//    processUdp();
//  } while (irStatus != 1);
//  moveConveyor(0);
//  sendTerminal(1, 0, 1, 0, 1, "1");
//  getNewDetail();
//  moveConveyor(100);
//  do {
//    requestIR();
//    processUdp();
//  } while (irStatus != 0);
//  moveConveyor(100);
//  do {
//    requestIR();
//    processUdp();
//  } while (irStatus != 1);
//  sendTerminal(1, 0, 1, 0, 1, "2");
//  moveConveyor(0);
//  getNewDetail();
}

void loop() {
  processUdp();
}
