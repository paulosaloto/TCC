#include <SD.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
int contaBytes = 0;
int   atualEtapa[6];
int   proximaEtapa[6];
uint8_t   atualExpressao=0;
// our servo # counter
uint8_t servonum = 0;

Adafruit_PWMServoDriver pwmHead = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmBody = Adafruit_PWMServoDriver(0x41);

File myFile;

