#include "DxlMaster.h"

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <EEPROM.h>

#define DXL_BAUDRATE 1000000
#define DXL_ID 1
#define DXL_REG 27
#define UDP_PORT 8888

IPAddress MyIP(192, 168, 42, 17); //core

EthernetUDP Udp;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
byte mac[6];

byte serialBuffer[15];

//DynamixelMotor motor((byte)DXL_ID);

void setup() {
  //DxlMaster.begin(DXL_BAUDRATE);
  //motor.init();
  //motor.wheelMode();
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
  Udp.begin(UDP_PORT);
  Serial.println("----------------------");
  Serial.println("UDP connection is at: ");
  Serial.println(Ethernet.localIP());
  // Serial.println("Type 1 to change localIP");  
  Serial.println("----------------------");
}
/*
int16_t parseSpeed(){
  int16_t result;
  String str = "";
  
  for(int i = 2; i < 6; i++){   // c:200:10:15#
    if(packetBuffer[i] > '0' || packetBuffer[i] < '9' || packetBuffer[i] == '-'){ //из строки берем направление вращения и по цифре составляем скорость
      str += (String)packetBuffer[i];
      result = str.toInt();      
    } else {
      return result;      
    }
  }
  return result;
}
*/
void processUdp(){
int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) Serial.print("."); 
      }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    int len = strlen(packetBuffer);
   // Serial.println(len);

    String str = "";
    for(int i = 2; i < len; i++){   // c:200:10:15#
      
     if(packetBuffer[i] == ':' || packetBuffer[i] == '#' ){
       
      int result = str.toInt();
      Serial.println(result);
      
      Udp.beginPacket("192.168.42.254", 49409);
      Udp.write("hello");
        Udp.endPacket();
      str = "";
      
     }
     else if(packetBuffer[i] > '0' || packetBuffer[i] < '9'){ //из строки берем направление вращения и по цифре составляем скорость
      str += (String)packetBuffer[i];
      }  
  
}  //int result = str.toInt();
   //Serial.println(str);
   // Serial.println(result);
  }}

void loop() {

  processUdp();
}
