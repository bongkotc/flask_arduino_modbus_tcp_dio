/*
  Ethernet Modbus TCP Server LED

  This sketch creates a Modbus TCP Server with a simulated coil.
  The value of the simulated coil is set on the LED

  Circuit:
   - Any Arduino MKR Board
   - MKR ETH Shield

  created 16 July 2018
  by Sandeep Mistry
*/

#include <SPI.h>
#include <Ethernet.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

EthernetServer ethServer(502);

ModbusTCPServer modbusTCPServer;

//const int ledPin8 = LED_BUILTIN;
// Array of LED pins
const int ledPins[] = {4, 5, 6, 7, 8, 9, 11, 12};

// Array of input pins
const int inputPins[] = {30, 31, 32, 33, 34, 35, 36, 37};

const int startInputAddressCoil = 10;
const int numInputAddressCoil = 8;

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Set LED pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }

  // Set input pins as inputs
  for (int i = 0; i < 8; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet Modbus TCP Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

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

  // start the server
  ethServer.begin();
  
  // start the Modbus TCP server
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }

  // configure the LED
//  pinMode(ledPin8, OUTPUT);
//  digitalWrite(ledPin8, LOW);

  // configure a single coil at address 0x00
//  modbusTCPServer.configureCoils(0x00, 1);


  
  // Configure coils
//  modbusTCPServer.configureCoils(0, 8);  // Configure 8 coils
  modbusTCPServer.configureCoils(0,8 + startInputAddressCoil + numInputAddressCoil);  // Configure 8 coils
}

void loop() {
  // listen for incoming clients
  EthernetClient client = ethServer.available();
  
  if (client) {
    // a new client connected
    Serial.println("new client");

    // let the Modbus TCP accept the connection 
    modbusTCPServer.accept(client);

    while (client.connected()) {
      // poll for Modbus TCP requests, while client connected
      modbusTCPServer.poll();

      // update the LED
      updateLED();
    }

    Serial.println("client disconnected");
  }
}

void updateLED() {
  // read the current value of the coil
//  int coilValue = modbusTCPServer.coilRead(0x00);
//
//  if (coilValue) {
//    // coil value set, turn LED on
//    digitalWrite(ledPin8, HIGH);
//  } else {
//    // coild value clear, turn LED off
//    digitalWrite(ledPin8, LOW);
//  }

    for (int i = 0; i < 8; i++) {
      bool coilValue = modbusTCPServer.coilRead(i);
//      digitalWrite(ledPins[i], coilValue ? HIGH : LOW);
        digitalWrite(ledPins[i], coilValue ? LOW : HIGH);
    }

    // Read the state of input pins and update Modbus coils
      for (int i = 0; i < numInputAddressCoil; i++) {
        int value = digitalRead(inputPins[i]);
        modbusTCPServer.coilWrite(startInputAddressCoil+i, value);
      }
}
