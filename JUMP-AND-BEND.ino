#define echoPin1 A0
#define echoPin2 A1
#define echoPin3 A2
#define echoPin4 A3

#define trigPin1 8 
#define trigPin2 9
#define trigPin3 10
#define trigPin4 7

#define ledPin1 13
#define ledPin2 12
#define ledPin3 11
#define ledPin4 6

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

// notes in the melody:
int melody[] = {
   NOTE_A3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8, 8};

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

long duration; 
int distance, ran, score; 

//#include <LiquidCrystal.h> 
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); 

int totalSecs ;                                                                                                                 
int mins ;
int secs;
String timeLeft;
unsigned long DELAY_TIME = 30000;
unsigned long delayStart = 0; 

void setup() {
  lcd.init();                      
  //lcd.init();
  lcd.backlight();

  pinMode(trigPin1, OUTPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(trigPin3, OUTPUT); 
  pinMode(trigPin4, OUTPUT); 

  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  pinMode(echoPin1, INPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  
  score=0;
  delayStart = millis();
  toneplay();toneplay();toneplay();toneplay();toneplay();
  delay(500);
}
void loop() {
  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);

  if (millis()-delayStart < DELAY_TIME) {  
    printAll();
    distance=100;
    ran = random(1,5);
    if (ran==1){
      digitalWrite(ledPin1, HIGH);
      do {
        printAll();
      
        digitalWrite(trigPin1, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin1, LOW);
      
        duration = pulseIn(echoPin1, HIGH);
        distance = duration * 0.034 / 2; 
      } while ( (distance > 20) && (millis()-delayStart < DELAY_TIME) );
    digitalWrite(ledPin1, LOW);
    }
    if (ran==2){
      digitalWrite(ledPin2, HIGH);
      do {
        printAll();
        
        digitalWrite(trigPin2, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin2, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin2, LOW);
      
        duration = pulseIn(echoPin2, HIGH);
        distance = duration * 0.034 / 2; 
      } while ( (distance > 20) && (millis()-delayStart < DELAY_TIME)  );
      digitalWrite(ledPin2, LOW);
    }
    if (ran==3){
      digitalWrite(ledPin3, HIGH);
      do {
        printAll();
        
        digitalWrite(trigPin3, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin3, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin3, LOW);
      
        duration = pulseIn(echoPin3, HIGH);
        distance = duration * 0.034 / 2; 
      } while ( (distance > 20) && (millis()-delayStart < DELAY_TIME) );
      digitalWrite(ledPin3, LOW);
    }
    if (ran==4){
      digitalWrite(ledPin4, HIGH);
      do {
        printAll();
        
        digitalWrite(trigPin4, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin4, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin4, LOW);
      
        duration = pulseIn(echoPin4, HIGH);
        distance = duration * 0.034 / 2; 
      } while ( (distance > 20) && (millis()-delayStart < DELAY_TIME) );
      digitalWrite(ledPin4, LOW);
    }
    if (millis()-delayStart >= DELAY_TIME) {
      toneplay();toneplay();toneplay();toneplay();toneplay();
    } else {
      score=score+1;
      toneplay(); 
      delay(500);
    }
  } else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Score:");
    lcd.setCursor(6,1);
    lcd.print(score);
    lcd.setCursor(1,0);
    lcd.print("PRESS BUTTON!"); 
       
    delay(300);
  }
}

void toneplay() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(5, melody[thisNote], noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 0.60;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(5);
  }
}
void printAll() {
    totalSecs = (DELAY_TIME - (millis() - delayStart))/1000; 
    if (totalSecs >= 0) {
      mins = totalSecs/60;                                           
      secs = totalSecs-mins*60;   
      timeLeft = (String(mins) + ":" + String(secs)); 
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Score:");
      lcd.setCursor(6,1);
      lcd.print(score);
      lcd.setCursor(6,0);
      lcd.print(timeLeft);
    } else {
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("Score:");
      lcd.setCursor(6,1);
      lcd.print(score);
      lcd.setCursor(1,0);
      lcd.print("PRESS BUTTON!");    
    }

    delay(200);
}
