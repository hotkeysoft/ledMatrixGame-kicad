#include "rom.h"
#include "TMS1000.h"

#define K1 A0
#define K2 A1
#define K4 A2

#define O0 8
#define O1 9
#define O2 10
#define O3 11
#define O4 12

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

// Buzzer
#define R8 A3

#define R9 A4
#define R10 A5

// Buttons connected to K1-K8
void inputKCallback() {
      TMS1000::g_cpu.K = (PINC & 7) ^ 7;
}

// LED array connected to R0-R7
// Buzzer connected to R8
// Keypad connected do R9 R10
void outputRCallback(TMS1000::BYTE pin, bool state) {
  switch (pin) {
    case 0: case 1: case 2: case 3:
    case 4: case 5: case 6: case 7:
      digitalWrite(R0+pin, state);      
    break;
    case 8:
      digitalWrite(R8, state);
      break;
     case 9:
      digitalWrite(R9, !state);     
      break;
     case 10:
     digitalWrite(R10, !state);
    break;
  }
}

// R = LED Anode
// O = LED Cathode
// Ox = 0 to turn on LED
const uint8_t oMap[] = {
  0b11111111, // 0
  0b11111110, // 1
  0b11111101, // 2
  0b11111011, // 3
  0b11110111, // 4
  0b11101111, // 5
  0b11011111, // 6
  0b10111111, // 7
};

void outputOCallback(TMS1000::BYTE val) {
  PORTB = oMap[val & 7];
}

void setup() {
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K4, INPUT_PULLUP);

  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);  
  pinMode(R7, OUTPUT);  

  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  pinMode(R10, OUTPUT);

  pinMode(O0, OUTPUT);
  pinMode(O1, OUTPUT);
  pinMode(O2, OUTPUT);
  pinMode(O3, OUTPUT);
  pinMode(O4, OUTPUT);
  pinMode(O5, OUTPUT);
  pinMode(O6, OUTPUT);    
   
  TMS1000::Init(TMS1000::CPU_TMS1400, 4096, 128); 
  TMS1000::SetInputKCallback(inputKCallback);
  TMS1000::SetOutputOCallback(outputOCallback);
  TMS1000::SetOutputRCallback(outputRCallback);
  TMS1000::g_memory.ROM = rom;
  TMS1000::Reset();
}

void loop() {
  TMS1000::Step();
  delayMicroseconds(10);
}
