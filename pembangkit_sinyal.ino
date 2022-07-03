#include <EEPROM.h>
#include "TimerOne.h"
#define LED1 5
#define LED2 6


int LED1_ON;
int LED2_ON;
int LED1_OFF;
int LED2_OFF;
int LED1_state = 0;
int LED2_state = 0;
int LED1_time = 0;
int LED2_time = 0;
int arr_pos = 0;

void EEPROM_INT_WRITE(int address, int number){
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int EEPROM_INT_READ(int address){
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}

void EEPROM_READ(int* LED1_ON, int* LED2_ON, int* LED1_OFF, int* LED2_OFF) {
  int eeAddress = 16;
  *LED1_ON = EEPROM_INT_READ(eeAddress);
   eeAddress = eeAddress + sizeof(int);
  *LED2_ON = EEPROM_INT_READ(eeAddress);
   eeAddress = eeAddress + sizeof(int);
  *LED1_OFF = EEPROM_INT_READ(eeAddress);
   eeAddress = eeAddress + sizeof(int);
  *LED2_OFF = EEPROM_INT_READ(eeAddress);
 
}

void LED1_ITR(){
  LED1_time++;
  LED2_time++;
  if (LED1_state == 0){
    if (LED1_time > LED1_OFF){
      LED1_state = 1;
      LED1_time = 0;
      digitalWrite(LED1, HIGH);
    }
  } else{
    if (LED1_time > LED1_ON){
      LED1_state = 0;
      LED1_time = 0;
      digitalWrite(LED1, LOW);
    }
  }
  if (LED2_state == 0){
     if (LED2_time > LED1_OFF){
      LED2_state = 1;
      LED2_time = 0;
      digitalWrite(LED2, HIGH);
    }
  } else{
    if (LED2_time > LED1_OFF){
      LED2_state = 0;
      LED2_time = 0;
      digitalWrite(LED2, LOW);
    }
  }
  Serial.println("heyyy");
}

void EEPROM_WRITE(int LED1_ON, int LED2_ON, int LED1_OFF, int LED2_OFF) {
  int eeAddress = 16;
  EEPROM_INT_WRITE(eeAddress, LED1_ON);
  eeAddress = eeAddress + sizeof(int);
  EEPROM_INT_WRITE(eeAddress, LED2_ON);
  eeAddress = eeAddress + sizeof(int);
  EEPROM_INT_WRITE(eeAddress, LED1_OFF);
  eeAddress = eeAddress + sizeof(int);
  EEPROM_INT_WRITE(eeAddress, LED2_OFF);
}


void setup() {
  //  DDRD = D00000110;  
  pinMode(LED1, OUTPUT);
  Serial.begin(9600);
  pinMode(LED2, OUTPUT);

//  EEPROM_WRITE(5, 2, 3, 2);
  EEPROM_READ(&LED1_ON, &LED2_ON, &LED1_OFF, &LED2_OFF);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(LED1_ITR); 

  
}

void readSerial2(char* chr){
  
}

int* convert(char c[100])
{
  int *a;
  char *endptr, *ptr = c;
  int count = 1;

while (*ptr != '\0') {
    if (isdigit(*ptr)) {
        a[count++] = strtol(ptr, &endptr, 10);
        Serial.println(strtol(ptr, &endptr, 10));
    } else {
        endptr = ptr + 1;
    }

    ptr = endptr;
}

  return a;
}

 

void loop() {
  // put your main code here, to run repeatedly:
//  if (Serial.available() > 0) {
//    // read the incoming byte:
//    int incomingByte = Serial.read();
//
//    // say what you got:
//    Serial.print("I received: ");
//    Serial.println(incomingByte, DEC);
//  }
  char value[100];
  int i;
  int j;
  
  while (Serial.available() > 0){
    i = Serial.readBytesUntil('\n',value, sizeof(value)-1);
    value[100] = i;
    // Serial.println(i);
    // Serial.println(value);
    int* a = convert(value);
    LED1_ON = a[1];
    LED2_ON = a[2];
    LED1_OFF = a[3];
    LED2_OFF = a[4];
  }
}
