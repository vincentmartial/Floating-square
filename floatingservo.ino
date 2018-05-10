/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266

  Example for receiving open sound control (OSC) bundles on the ESP8266
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

char ssid[] = "HUAWEI_P9lite_39C3";          // your network SSID (name)
char pass[] = "lechitas";                    // your network password

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;


const IPAddress ip(192, 168, 1, 220);     // IP para este dispositivo
const IPAddress gateway(192, 168, 1, 1);  // IP gateway, normalmente es la del router
const IPAddress subnet(255, 255, 255, 0); // Mascara de subred

const IPAddress outIp(10,40,10,105);       // remote IP (not needed for receive)
const unsigned int outPort = 9999;        // remote port (not needed for receive)
const unsigned int localPort = 8888;        // local port to listen for UDP packets (here's where we send the packets)


OSCErrorCode error;
unsigned int ledState = LOW;              // LOW means led is *on*


#include <Servo.h> 

// dupliquer les lignes, une par servo 1, 2, 3 etc jusqu'à 9
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, ledState);    // turn *on* led

  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
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
  
servo1.writeMicroseconds(544);
servo2.writeMicroseconds(544);
servo3.writeMicroseconds(544);
servo4.writeMicroseconds(544);
servo5.writeMicroseconds(544);
servo6.writeMicroseconds(544);
servo7.writeMicroseconds(544);
servo8.writeMicroseconds(544);
servo9.writeMicroseconds(544);
delay(1000);

  //dupliquer les attach
  // Important : mettre D0,D5 etc...
  
  servo1.attach(16); // D0 ...
  servo2.attach(5);
  servo3.attach(4);
  servo4.attach(0);
  servo5.attach(2);
  servo6.attach(14);
  servo7.attach(12);
  servo8.attach(13);
  servo9.attach(15); // ... D8

}


void servo(OSCMessage &msg) {
  int servo = msg.getInt(0);
  int value = msg.getInt(1);
  Serial.print("/servo: ");
  Serial.println(servo);
  Serial.print("value: ");
  Serial.println(value);
  //digitalWrite(BUILTIN_LED, ledState);
  switch (servo) {
    case 1:
      servo1.writeMicroseconds(value);
      // statements
      break;
    case 2:
      servo2.writeMicroseconds(value);
      // statements
      break;
   // dupliquer de ici vvvvv
   case 3:
      servo3.writeMicroseconds(value);
      // statements
      break;
   case 4:
      servo4.writeMicroseconds(value);
      // statements
      break;
   case 5:
      servo5.writeMicroseconds(value);
      // statements
      break;
   case 6:
      servo6.writeMicroseconds(value);
      // statements
      break;
    case 7:
      servo7.writeMicroseconds(value);
      // statements
      break;
   case 8:
      servo8.writeMicroseconds(value);
      // statements
      break;
  case 9:
      servo9.writeMicroseconds(value);
      // statements
      break;     
    // jusqu'à là ^^^^^^^^
    // et changer case 3, 4 etc... ainsi que servo3, servo4 etc...
    default:
      // statements
      break;
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
      bundle.dispatch("/servo", servo);
    } else {
      error = bundle.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}



