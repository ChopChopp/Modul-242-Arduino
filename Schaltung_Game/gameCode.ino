#include <LiquidCrystal.h>

const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

int start = 0;
int pos = 0;
bool alive = true;
bool topField[16];
bool botField[16];
String topFieldString;
String botFieldString;

//screen configurieren
void setup() {
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  //Eingabe vom Schield
  int x = analogRead(0);

  if (start == 0) { //bevor start
    lcd.setCursor(6, 0);
    lcd.print("Game");
    lcd.setCursor(0, 1);
    lcd.print(" <Finish Start> ");
    
    if (x < 60) {
      mazeCreator();
      start = 1;
    } else if (x < 600 && x >= 400) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Shutdown");
      delay(1000);
      start = 2;
    }

  } else if (start == 1) { //wärend das Game läuft 

    if (alive) { // solange der Spieler lebt
      if (x < 200 && x >= 60) { //Spieler neu positionieren
        pos = 0;
      } else if (x >= 200 && x < 400) {
        pos = 1;
      }

      if (pos == 0 && !topField[0] || pos == 1 && !botField[0]) { //Spielstand überprüfen
        alive = false;
      } else {

        // neuen Spielstand ausgeben
        arrToString();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(topFieldString);
        lcd.setCursor(0, 1);
        lcd.print(botFieldString);
        lcd.setCursor(0, pos);
        lcd.print("O");
        cicleArray();
      }

      digitalWrite(10 ,HIGH);
      digitalWrite(11 ,LOW);
      digitalWrite(12 ,HIGH);
      delay(250);
      digitalWrite(11 ,HIGH);
      digitalWrite(10 ,LOW);
      digitalWrite(12 ,LOW);
      delay(250); 

    } else { // nach dem Tod des Spielers 
      digitalWrite(10 ,LOW);
      digitalWrite(11 ,LOW);     
      digitalWrite(12 ,LOW); 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("dead");
      lcd.setCursor(0, 1);
      lcd.print("select for reset");
      if (x < 800 && x >= 600) {
        lcd.clear();
        alive = true;
        start = 0;
      }
    }
  } else { //herunterfahren
    lcd.clear(); 
    delay(10000000);
  }
}

void mazeCreator() { //maze initialisierung
  topField[0] = true;
  botField[0] = true;
  topField[1] = true;
  botField[1] = true;
  for (int i = 2; i <  16; i++) {
    bool newField = rand() & 1;
    topField[i] = newField;
    botField[i] = !newField;
  }
}

void cicleArray() { //maze erweitern und updaten
  for (int i = 0; i <  15; i++) {
    topField[i] = topField[i + 1];
    botField[i] = botField[i + 1];
  }
  bool newField = rand() & 1;
  topField[15] = newField;
  botField[15] = !newField;
}

void arrToString() { //maze in String umwandeln
  topFieldString = "";
  botFieldString = "";
  for (int i = 0; i <  16; i++) {
    if (topField[i]) {
      topFieldString = topFieldString + " ";
    } else {
      topFieldString = topFieldString + "#";
    }
    if (botField[i]) {
      botFieldString = botFieldString + " ";
    } else {
      botFieldString = botFieldString + "#";
    }
  }
}
