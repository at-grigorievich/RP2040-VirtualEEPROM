#include <Arduino.h>
#include "VirtualEEPROM.h"

VirtualEEPROM eeprom;

struct MyData {
  uint16_t x;
  uint16_t y;
  uint16_t z;
};

void read();
void write();

void setup() {
  Serial.begin(115200);
  while (!Serial) ; 
  delay(1000);

  Serial.println("read from Flash EEPROM only?: [Y/N]");

  delay(1000);

  bool isReadOnly = false;
  bool isSelected = false;

  while(isSelected == false){
    char result = Serial.read();

    if(result == 'y') {
      isReadOnly = true;
      isSelected = true;
    }
    else if(result == 'n') {
      isSelected = true;
    }
  }

  eeprom.begin();

  if(isReadOnly) {
    read();
  }
  else {
    write();
    read();
  }
}

void loop() { }

void read() {
    Serial.println("read...");
    MyData read_data_1;
    MyData read_data_2;

    eeprom.readStruct(0, read_data_1);
    eeprom.readStruct(9, read_data_2);

    Serial.print("x_1 = "); Serial.println(read_data_1.x);
    Serial.print("y_1 = "); Serial.println(read_data_1.y);
    Serial.print("z_1 = "); Serial.println(read_data_1.z);

    Serial.print("x_2 = "); Serial.println(read_data_2.x);
    Serial.print("y_2 = "); Serial.println(read_data_2.y);
    Serial.print("z_2 = "); Serial.println(read_data_2.z);
}

void write()
{
  Serial.println("write...");
   MyData dataOut1 = {123, 456, 789};
   MyData dataOut2 = {111, 666, 999};

   eeprom.writeStruct(0, dataOut1);
   eeprom.writeStruct(9, dataOut2);

   eeprom.commit();
}