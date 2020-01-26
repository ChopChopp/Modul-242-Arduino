/* GridMovement.cpp und GridMovement.h stellen Funktionen zur Verfügung, 
welche für das Bewegen des Roboters notwendig sind. */

#pragma once

#include <Wire.h>
#include <Zumo32U4.h>

// Motor Geschwindigkeit beim Befahren einer geraden Strecke (maximal 400)
const uint16_t straightSpeed = 200;

const uint16_t intersectionDelay = 130;

// Motor Geschwindigkeit beim Wenden
const uint16_t turnSpeed = 200;

// Motor Geschwindigkeit beim Wenden auf Grund der Kalibrierung
const uint16_t calibrationSpeed = 200;

// Dieser Treshold wird für das Bestimmen von Kreuzungen gebraucht
const uint16_t sensorThreshold = 200;

// Wird gebraucht um das Ende des Labyrinths zu erkennen
const uint16_t sensorThresholdDark = 600;

// Die Anzahl an Liniensensoren
const uint8_t numSensors = 5;

const int32_t gyroAngle45 = 0x20000000;

void printBar(uint8_t barHeight);
uint16_t readSensors();
bool aboveLine(uint8_t sensorIndex);
bool aboveLineDark(uint8_t sensorIndex);
bool aboveDarkSpot();
extern uint16_t lineSensorValues[numSensors];
void turn(char dir);
void followSegment();
void driveToIntersectionCenter();
void driveToIntersectionCenter(bool * foundLeft, bool * foundStraight, bool * foundRight);
void gridMovementSetup();

extern L3G gyro;
extern Zumo32U4ButtonA buttonA;
extern Zumo32U4Motors motors;
extern Zumo32U4LCD lcd;
extern Zumo32U4LineSensors lineSensors;
