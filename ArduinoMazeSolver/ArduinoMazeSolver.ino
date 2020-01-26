/*
  Autor:        Camil Schmid, Umut Oeztuerk
  Version:      1.0
  Beschreibung: Dieser Code beschreibt das Lösen eines Labyrinthes für den zumo32u4.
                Er ist stark inspiriert vom Beispielcode für den zumo32u4, welcher von der eingefügten Library zur Verfügung getstellt wird.
  */

#include <Wire.h>
#include <Zumo32U4.h>
#include "GridMovement.h"

Zumo32U4LCD lcd;
Zumo32U4Buzzer buzzer;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
L3G gyro;

//In der path Variable wird der bisher zurückgelegte Weg festgehalten anhand von Buchstaben wie 'L' und 'R' für Links und Rechts
char path[100];
uint8_t pathLength = 0;

void setup()
{
  buzzer.playFromProgramSpace(PSTR("!>g32>>c32"));

  gridMovementSetup();

  // mazeSolve() durchsucht das ganze Labyrinth bis es den optimalen Weg findet
  mazeSolve();
}

void loop()
{
  // Das Labyrinth wurde gelöst, wartet auf den User den A Knopf zu betätigen
  buttonA.waitForButton();


  mazeFollowPath();
}

// Diese Funktion entscheidet, in welche Richtung der Roboter sich wenden soll
char selectTurn(bool foundLeft, bool foundStraight, bool foundRight)
{

  if(foundLeft) { return 'L'; }
  else if(foundStraight) { return 'S'; }
  else if(foundRight) { return 'R'; }
  else { return 'B'; }
}

// Die mazeSolve() Funktion folgt dem Prinzip, bei jeder Kreuzung
// nach links zu wenden, was schlussendlich bei einem regulären Labyrinth zum Ausganz führen wird
void mazeSolve()
{
  pathLength = 0;
  buzzer.playFromProgramSpace(PSTR("!L16 cdegreg4"));
  delay(1000);

  while(1)
  {
    // Folge momentaner Linie bis Kreuzung erscheint
    followSegment();
    
    // bis zur Kreuzung fahren und schauen, was für 
    // Abbiege-Möglichkeiten es gibt
    bool foundLeft, foundStraight, foundRight;
    driveToIntersectionCenter(&foundLeft, &foundStraight, &foundRight);

    if(aboveDarkSpot())
    {
      // Das Ende des Labyrinths wurde erreicht und der Roboter wird gestoppt
      break;
    }

    char dir = selectTurn(foundLeft, foundStraight, foundRight);

    if (pathLength >= sizeof(path))
    {
      lcd.clear();
      lcd.print(F("pathfull"));
      while(1)
      {
        ledRed(1);
      }
    }

    path[pathLength] = dir;
    pathLength++;

    simplifyPath();
    displayPath();

    if (pathLength == 2 && path[0] == 'B' && path[1] == 'B')
    {
      buzzer.playFromProgramSpace(PSTR("!<b4"));
    }

    turn(dir);
  }

  // Das Labyrinth wurde optimal gelöst und nun werden die Motoren ausgeschaltet
  // Zudem wird ein Ton abgespielt um das Ende zu symbolosieren.
  motors.setSpeeds(0, 0);
  buzzer.playFromProgramSpace(PSTR("!>>a32"));
}

// Löst das Labyrinth erneut
void mazeFollowPath()
{
  buzzer.playFromProgramSpace(PSTR("!>c32"));
  delay(1000);

  for(uint16_t i = 0; i < pathLength; i++)
  {
    followSegment();
    driveToIntersectionCenter();
    turn(path[i]);
  }
  
  followSegment();

  motors.setSpeeds(0, 0);
  buzzer.playFromProgramSpace(PSTR("!>>a32"));
}

// Dient zur vereinfachung der Wege des Labyrinthes
void simplifyPath()
{
  if(pathLength < 3 || path[pathLength - 2] != 'B')
  {
    return;
  }

  int16_t totalAngle = 0;

  for(uint8_t i = 1; i <= 3; i++)
  {
    switch(path[pathLength - i])
    {
    case 'L':
      totalAngle += 90;
      break;
    case 'R':
      totalAngle -= 90;
      break;
    case 'B':
      totalAngle += 180;
      break;
    }
  }
  
  totalAngle = totalAngle % 360;

  switch(totalAngle)
  {
  case 0:
    path[pathLength - 3] = 'S';
    break;
  case 90:
    path[pathLength - 3] = 'L';
    break;
  case 180:
    path[pathLength - 3] = 'B';
    break;
  case 270:
    path[pathLength - 3] = 'R';
    break;
  }

  // The path is now two steps shorter.
  pathLength -= 2;
}

void displayPath()
{
  lcd.clear();
  lcd.print("Solving");
  lcd.gotoXY(0,1);
  lcd.print("...");
}
