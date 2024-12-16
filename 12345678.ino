//FOR SP32-S3-WROOM-1 N8R2 N16R8 + 74HC595
#include <Arduino.h>

#define DATA_PIN 21  // DIO
#define CLOCK_PIN 18 // SCK
#define LATCH_PIN 19 // RCK

// Коды цифр (common cathode)
const uint8_t digitCode[10] = {
  0xC0, // 0
  0xF9, // 1
  0xA4, // 2
  0xB0, // 3
  0x99, // 4
  0x92, // 5
  0x82, // 6
  0xF8, // 7
  0x80, // 8
  0x90  // 9
};

// Новый порядок выбора разряда
const uint8_t digitSelect[8] = {
  0x10, // Первый слева разряд
  0x20,
  0x40,
  0x80,
  0x01,
  0x02,
  0x04,
  0x08  // Последний справа разряд
};

void shiftOutByte(uint8_t val) {
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, (val & 0x80) ? HIGH : LOW);
    val <<= 1;
    digitalWrite(CLOCK_PIN, HIGH);
  }
}

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(LATCH_PIN, LOW);
}

void loop() {
  uint8_t displayData[8];
  displayData[0] = digitCode[1]; // '1'
  displayData[1] = digitCode[2]; // '2'
  displayData[2] = digitCode[3]; // '3'
  displayData[3] = digitCode[4]; // '4'
  displayData[4] = digitCode[5]; // '5'
  displayData[5] = digitCode[6]; // '6'
  displayData[6] = digitCode[7]; // '7'
  displayData[7] = digitCode[8]; // '8'

  for (int i = 0; i < 8; i++) {
    digitalWrite(LATCH_PIN, LOW);
    shiftOutByte(displayData[i]);   // Сегменты
    shiftOutByte(digitSelect[i]);   // Разряд
    digitalWrite(LATCH_PIN, HIGH);
    delay(1);
  }
}
