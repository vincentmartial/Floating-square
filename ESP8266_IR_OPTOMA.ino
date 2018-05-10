

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_LED1 14  // D5
#define IR_LED2 12 // D6
#define IR_LED3 13 // D7

IRsend irsend1(IR_LED1);  // Set the GPIO to be used to sending the message.
IRsend irsend2(IR_LED2);
IRsend irsend3(IR_LED3);

//// IR OPTOMA ML750e codes
unsigned long power = 0x10C8E817; //1
unsigned long source = 0x10C89867;
unsigned long menu = 0x10C88877; // 2
unsigned long enter = 0x10C8C837; // 3
unsigned long gauche = 0x10C8708F; // 4
unsigned long droite = 0x10C8F00F; // 5
unsigned long haut = 0x10C8B04F; // 6
unsigned long bas = 0x10C808F7; // 7
unsigned long sonplus = 0x10C89C63;
unsigned long sonmoins = 0x10C8CC33;
unsigned long arret = 0x10C8AC53;
unsigned long arriere = 0x10C82CD3; // 8
unsigned long avance = 0x10C86C93; // 9
unsigned long keystoneplus = 0x10C81CE3; //10
unsigned long keystonemoins = 0x10C8EC13; // 11
unsigned long eco = 0x10C828D7;
unsigned long hide = 0x10C842BD; // 12
//// IR

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

char ssid[] = "SFR_B4C8";          // your network SSID (name)
char pass[] = "enorksenez3vesterish";                    // your network password

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;
//const IPAddress outIp(10,40,10,105);        // remote IP (not needed for receive)
//const unsigned int outPort = 9999;          // remote port (not needed for receive)
const unsigned int localPort = 8888;        // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;


void setup() {
  irsend1.begin();
  irsend2.begin();
  irsend3.begin();
  
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

   // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());

}

void teleco(OSCMessage &msg) {
  int teleco = msg.getInt(0);
  int code = msg.getInt(1);
  
  Serial.print("/telecommande: ");
  Serial.println(teleco);
  Serial.print("/code: ");
  Serial.println(code);

if (teleco == 1) {

  switch (code) {
    case 1:
      irsend1.sendNEC(power, 32);
      break;
    case 2:
      irsend1.sendNEC(menu, 32);
      break;
    case 3:
      irsend1.sendNEC(enter, 32);
      break;
    case 4:
      irsend1.sendNEC(gauche, 32);
      break;
    case 5:
      irsend1.sendNEC(droite, 32);
      break;
    case 6:
      irsend1.sendNEC(haut, 32);
      break;
    case 7:
      irsend1.sendNEC(bas, 32);
      break;
    case 8:
      irsend1.sendNEC(arriere, 32);
      break;
    case 9:
      irsend1.sendNEC(avance, 32);
      break;
    case 10:
      irsend1.sendNEC(keystoneplus, 32);
      break;
    case 11:
      irsend1.sendNEC(keystonemoins, 32);
      break;
    case 12:
      irsend1.sendNEC(hide, 32);
      break;

    default:
      // statements
      break;
  }
}

else if (teleco == 2) {

  switch (code) {
    case 1:
      irsend2.sendNEC(power, 32);
      break;
    case 2:
      irsend2.sendNEC(menu, 32);
      break;
    case 3:
      irsend2.sendNEC(enter, 32);
      break;
    case 4:
      irsend2.sendNEC(gauche, 32);
      break;
    case 5:
      irsend2.sendNEC(droite, 32);
      break;
    case 6:
      irsend2.sendNEC(haut, 32);
      break;
    case 7:
      irsend2.sendNEC(bas, 32);
      break;
    case 8:
      irsend2.sendNEC(arriere, 32);
      break;
    case 9:
      irsend2.sendNEC(avance, 32);
      break;
    case 10:
      irsend2.sendNEC(keystoneplus, 32);
      break;
    case 11:
      irsend2.sendNEC(keystonemoins, 32);
      break;
    case 12:
      irsend2.sendNEC(hide, 32);
      break;

    default:
      // statements
      break;
  }
}

 else if (teleco == 3) {

  switch (code) {
    case 1:
      irsend3.sendNEC(power, 32);
      break;
    case 2:
      irsend3.sendNEC(menu, 32);
      break;
    case 3:
      irsend3.sendNEC(enter, 32);
      break;
    case 4:
      irsend3.sendNEC(gauche, 32);
      break;
    case 5:
      irsend3.sendNEC(droite, 32);
      break;
    case 6:
      irsend3.sendNEC(haut, 32);
      break;
    case 7:
      irsend3.sendNEC(bas, 32);
      break;
    case 8:
      irsend3.sendNEC(arriere, 32);
      break;
    case 9:
      irsend3.sendNEC(avance, 32);
      break;
    case 10:
      irsend3.sendNEC(keystoneplus, 32);
      break;
    case 11:
      irsend3.sendNEC(keystonemoins, 32);
      break;
    case 12:
      irsend3.sendNEC(hide, 32);
      break;

    default:
      // statements
      break;
  }
 }

}


void loop() {


  OSCBundle bundle;
  int size = Udp.parsePacket();

  if (size > 0) {
    while (size--) {
      bundle.fill(Udp.read());
    }
    if (!bundle.hasError()) {
      bundle.dispatch("/teleco", teleco);
    } else {
      error = bundle.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }

}
