#include "DxlMaster.h"

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <EEPROM.h>

#define DXL_BAUDRATE 57600
#define DXL_ID 0x0A
#define DXL_REG 27
#define UDP_PORT 8888

IPAddress MyIP(192, 168, 42, 16);

EthernetUDP udp;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
byte mac[6];

byte serialBuffer[15];

DynamixelDevice irDevice((byte)DXL_ID);

void setup() {
  DxlMaster.begin(DXL_BAUDRATE);
  irDevice.init();
  Serial.begin(115200);
  //Считываем данные из EEPROM и представляем их как IP адреса
  //IP адрес модуля
  // for (int addr = 0; addr < 4; addr++) {
  //   MyIP[addr] = EEPROM.read(addr);
  // }
  mac[0] = MyIP[0];
  mac[1] = MyIP[1];
  mac[2] = MyIP[2];
  mac[3] = MyIP[3];
  mac[4] = MyIP[2];
  mac[5] = MyIP[3];
  Serial.begin(115200);
  Ethernet.begin(mac, MyIP);
  udp.begin(UDP_PORT);
  Serial.println("----------------------");
  Serial.println("UDP connection is at: ");
  Serial.println(Ethernet.localIP());
  Serial.println("----------------------");
}

void processUdp(){
int packetSize = udp.parsePacket();
  if (packetSize) {
    Serial.print("From ");
    IPAddress remote = udp.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(udp.remotePort());
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    if(
        packetBuffer[0] == 'i' &&
        packetBuffer[1] == ':' &&
        packetBuffer[2] == 'r' &&
        packetBuffer[3] == '#'
      ) {
        uint8_t irData = 0;
        irDevice.read(DXL_REG, irData);
        //Serial.print("Sending: ");
        String o = "I:" + (String)irData + "#";
        char oo[o.length() + 1];
        o.toCharArray(oo, o.length() + 1);
        udp.beginPacket(remote, UDP_PORT);
        udp.write(oo);
        udp.endPacket();        
    }
  }  
}

// void changeIp(){
//   Serial.println("---------------------------");
//   Serial.println("Type new IP:");
//   Serial.println("            XXX.XXX.XXX.XXX");
//   Serial.println("---------------------------");
//   while(!Serial.available()){}
//   while(Serial.available()){
//     serialBuffer[serialIn++] = Serial.read();
//   }
//   for(int i = 0; i < serialIn; i++){
//     if((serialIn < 15)||(i != 3 && i != 7 && i != 11 && (char)serialBuffer[0] < '0' && (char)serialBuffer[0] > '9')) {
//       Serial.println("IP not set");
//       return;
//     }
//   }
// }

void loop() {
  // if(Serial.available()){
  //   delay(50);
  //   byte serialBufferCounter = 0;
  //   while(Serial.available()){
  //     serialBuffer[serialBufferCounter++] = (byte)Serial.read();
  //   }
  //   String inMsg = "";
  //   for(int i = 0; i < serialBufferCounter; i++) {
  //     inMsg += (String)(char)serialBuffer[i];
  //   }
  //   inMsg.trim();
  //   if(inMsg == "CHANGE"){
  //     changeIp();
  //   }
  // }
  processUdp();
}