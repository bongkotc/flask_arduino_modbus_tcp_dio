//เรียกใช้งาน Library
#include <SPI.h>//ส่วนของ SPI Interface
#include <Ethernet.h>//ส่วนของ Ethernet shield (W5100)
#include <ArduinoModbus.h>//ส่วนของ Modbus Library

byte mac[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };//กำหนดหมายเลข MAC Address ของ Ethernet Board
IPAddress ip(192, 168, 1, 100);//ตั้งค่า IP Address ของ Server

EthernetServer ethServer(502);//ตั้งค่า Port ของ Modbus

ModbusTCPServer modbusTCPServer;

//กำหนดที่จะใช้เชื่อมต่อหลอด LED 
const int ledPins[] = {4, 5, 6, 7, 8, 9, 11, 12};

//กำหนดที่จะใช้เชื่อมอ่านค่าจากปุ่มกด
const int inputPins[] = {30, 31, 32, 33, 34, 35, 36, 37};

const int startOutputAddressCoil = 0;
const int numOutputAddressCoil = 8;
const int startInputAddressCoil = 10;
const int numInputAddressCoil = 8;

void updateSwitch();
void updateLED();

void setup() {
  //ตั้งค่า ledPins ทั้งหมดเป็น Output
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);
  }

  //ตั้งค่า inputPins ทั้งหมดเป็น Input แบบ Pullup เพราะปุ่มกดเป็นแบบ Active Low
  for (int i = 0; i < 8; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  //ตั้งค่าเริ่มต้นการใช้งาน Serial Port
  Serial.begin(9600);
  while (!Serial);
  Serial.println("เริ่มต้นโปรแกรม");

  //เริ่มการตั้งค่า Ethernet shield (W5100) 
  Ethernet.begin(mac, ip);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("ไม่พบ Ethernet shield (W5100).  กรุณาตรวจสอบ");
    while (true) {
      delay(1);
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("กรุณาตรวจสอบสาย LAN");
  }

  //เริ่มต้น Start Port ของ Modbus
  ethServer.begin();
  
  if (!modbusTCPServer.begin()) {
    Serial.println("ไม่สามารถ Start Modbus Server ได้");
    while (1);
  }
  modbusTCPServer.configureCoils(startOutputAddressCoil,numOutputAddressCoil + startInputAddressCoil + numInputAddressCoil);  // Configure 8 coils
}

void loop() {
  //รอเครื่อง Client เชื่อมต่อเข้ามา
  EthernetClient client = ethServer.available();
  
  if (client) {
    Serial.println("มี Client เชื่อมต่อเข้ามา");

    //Server ยินยอมให้ client เชื่อมต่อได้
    modbusTCPServer.accept(client);

    while (client.connected()) {
      //รอการร้องขอข้อมูล Address ใดๆ      
      modbusTCPServer.poll();
      //Update ข้อมูลปุ่มกด
      updateSwitch();
      //Update ข้อมูล LED
      updateLED();
    }

    Serial.println("ยกเลิกการเชื่อมต่อ");
  }
}

void updateLED() {
  //อ่าน Address Coil ของ LED
    for (int i = 0; i < 8; i++) {
      bool coilValue = modbusTCPServer.coilRead(i);
      //นำข้อมูลที่อ่านได้มาเขียนที่ Pin ของ LED
//      digitalWrite(ledPins[i], coilValue ? HIGH : LOW);//กรณี LED Active High
        digitalWrite(ledPins[i], coilValue ? LOW : HIGH);//กรณี LED Active Low
    }
}

void updateSwitch() {
    //อ่าน Address Coil ของปุ่มกด
      for (int i = 0; i < numInputAddressCoil; i++) {
        //อ่านข้อมูลจาก Pin ของปุ่มกด
        int value = digitalRead(inputPins[i]);
        //นำข้อมูลที่อ่านได้มาเขียนที่ Address Coil ของปุ่มกด
        modbusTCPServer.coilWrite(startInputAddressCoil+i, value);
      }
}
