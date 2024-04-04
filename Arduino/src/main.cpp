/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
*/

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <Wire.h>
/*------------------------------ Constantes ---------------------------------*/

#define BAUD 115200        // Frequence de transmission serielle

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false;  // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;  // Drapeau prêt à lire un message

int ledState = 0;
int potValue = 0;
//LiquidCrystal
  /*Circuit:
 * OLED RS pin to digital pin 22
 * OLED Enable pin to digital pin 24
 * OLED D4 pin to digital pin 26
 * OLED D5 pin to digital pin 28
 * OLED D6 pin to digital pin 30
 * OLED D7 pin to digital pin 32
 * OLED R/W pin to ground
 */
LiquidCrystal lcd(22,24,26,28,30,32);
// Pin potentiomatte
#define pinPOT A9

// Pins bargraph
#define pinBAR1 12
#define pinBAR2 11
#define pinBAR3 10
#define pinBAR4 9
#define pinBAR5 8
#define pinBAR6 7
#define pinBAR7 6
#define pinBAR8 5
#define pinBAR9 4
#define pinBAR10 3

// Pins DELs
#define pinDEL1 51
#define pinDEL2 49
#define pinDEL3 47
#define pinDEL4 45

// Pins Acceleromatte
#define pinACCX A15
#define pinACCY A14
#define pinACCZ A13
#define pinACCST A12

// Pins Joystick
#define pinJOYX A11
#define pinJOYY A10
#define pinJOYCLICK 53

// Pins moteur et vibrateur
#define pinMOTEUR 13
#define pinSPEAKER 37

// Pins Boutons/Gachettes
#define pinBUTTON1 29
#define pinBUTTON2 31
#define pinBUTTON3 35
#define pinBUTTON4 33
#define pinGACHETTE1 23
#define pinGACHETTE2 25

/*------------------------- Prototypes de fonctions -------------------------*/
void sendMsg(); 
void readMsg();
void serialEvent();
/*---------------------------- Fonctions "Main" -----------------------------*/

void setup() {
  Serial.begin(BAUD);               // Initialisation de la communication serielle
  // Pins BarGraph
  pinMode(pinBAR1, OUTPUT); // BARGRAPH 1
  pinMode(pinBAR2, OUTPUT);
  pinMode(pinBAR3, OUTPUT);
  pinMode(pinBAR4, OUTPUT);
  pinMode(pinBAR5, OUTPUT); // THROUGH 
  pinMode(pinBAR6, OUTPUT);
  pinMode(pinBAR7, OUTPUT);
  pinMode(pinBAR8, OUTPUT);
  pinMode(pinBAR9, OUTPUT);
  pinMode(pinBAR10, OUTPUT);  // BARGRAPH 10

  // Pins LEDs
  pinMode(pinDEL1, OUTPUT);
  pinMode(pinDEL2, OUTPUT);
  pinMode(pinDEL3, OUTPUT);
  pinMode(pinDEL4, OUTPUT);

  // Pins Acceleromatte
  pinMode(pinACCX, INPUT); 
  pinMode(pinACCY, INPUT); 
  pinMode(pinACCZ, INPUT); 

  // Pins Speaker et Moteur
  pinMode(pinMOTEUR, OUTPUT);

  // Pins Boutons
  pinMode(pinBUTTON1, INPUT);
  pinMode(pinBUTTON2, INPUT);
  pinMode(pinBUTTON3, INPUT);
  pinMode(pinBUTTON4, INPUT);
  digitalWrite(pinBUTTON1, HIGH);
  digitalWrite(pinBUTTON2, HIGH);
  digitalWrite(pinBUTTON3, HIGH);
  digitalWrite(pinBUTTON4, HIGH);

  // Pins Gachettes
  pinMode(pinGACHETTE1, INPUT);
  pinMode(pinGACHETTE2, INPUT);
  digitalWrite(pinGACHETTE1, HIGH);
  digitalWrite(pinGACHETTE2, HIGH);

  // Pins Joystick
  pinMode(pinJOYX, INPUT);
  pinMode(pinJOYY, INPUT);
  pinMode(pinJOYCLICK, INPUT);
  //Démarage LCD
  lcd.begin(16, 2);
  delay(100);
}

double i = 0;

/* Boucle principale (infinie) */
void loop() { 
  lcd.setCursor(0,0);
  lcd.print("Pot value:");
  lcd.print(analogRead(pinPOT));
  lcd.setCursor(0,1);
  lcd.print("A:");
  lcd.print(digitalRead(pinBUTTON3));
  lcd.print(" B:");
  lcd.print(digitalRead(pinBUTTON4));
  lcd.print(" Y:");
  lcd.print(digitalRead(pinBUTTON1));
  lcd.print(" X:");
  lcd.print(digitalRead(pinBUTTON2));
  delay(3);
  lcd.clear();
  // Acceleromatte


  //Serial.println(accX);
  //Serial.println(accY);
  //Serial.println(accZ);

  // JoyStick
  //Serial.println(analogRead(pinJOYX));
  //Serial.println(analogRead(pinJOYY));
  //Serial.println(digitalRead(pinJOYCLICK));

  // Moteur
  //digitalWrite(pinMOTEUR, HIGH); // P2
  //digitalWrite(pinSPEAKER, HIGH); // P1

  /*i += 0.001;
  Serial.println(sin(i)* 1023);
  analogWrite(pinMOTEUR, sin(i)* 1023);*/

  // Bar Graph
  //Serial.println(analogRead(pinPOT));  //Debug
  switch (map(analogRead(pinPOT), 0, 1000, 0, 10))
  {
  case 0:
    digitalWrite(pinBAR1, HIGH);
    digitalWrite(pinBAR2, HIGH);
    digitalWrite(pinBAR3, HIGH);
    digitalWrite(pinBAR4, HIGH);
    digitalWrite(pinBAR5, HIGH);
    digitalWrite(pinBAR6, HIGH);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break;
  case 1:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, HIGH);
    digitalWrite(pinBAR3, HIGH);
    digitalWrite(pinBAR4, HIGH);
    digitalWrite(pinBAR5, HIGH);
    digitalWrite(pinBAR6, HIGH);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break;
  case 2:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, HIGH);
    digitalWrite(pinBAR4, HIGH);
    digitalWrite(pinBAR5, HIGH);
    digitalWrite(pinBAR6, HIGH);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break;
  case 3:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, HIGH);
    digitalWrite(pinBAR5, HIGH);
    digitalWrite(pinBAR6, HIGH);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break; 
  case 4:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, HIGH);
    digitalWrite(pinBAR6, HIGH);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break;
  case 5:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, HIGH);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break; 
  case 6:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    digitalWrite(pinBAR7, HIGH);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break; 
  case 7:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    digitalWrite(pinBAR7, LOW);
    digitalWrite(pinBAR8, HIGH);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break; 
  case 8:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    digitalWrite(pinBAR7, LOW);
    digitalWrite(pinBAR8, LOW);
    digitalWrite(pinBAR9, HIGH);
    digitalWrite(pinBAR10, HIGH);
    break; 
  case 9:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    digitalWrite(pinBAR7, LOW);
    digitalWrite(pinBAR8, LOW);
    digitalWrite(pinBAR9, LOW);
    digitalWrite(pinBAR10, HIGH);
    break;   
  case 10:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    digitalWrite(pinBAR7, LOW);
    digitalWrite(pinBAR8, LOW);
    digitalWrite(pinBAR9, LOW);
    digitalWrite(pinBAR10, LOW);
    break;   
  default:
    break;
  }

  // Boutons
  // Si le bouton est appuye alors on allume sa DEL
  if(!digitalRead(pinBUTTON1)){
    digitalWrite(pinDEL3, LOW);
  }
  else {
    digitalWrite(pinDEL3, HIGH);
  }

  if(!digitalRead(pinBUTTON2)){
    digitalWrite(pinDEL2, LOW);
  }
  else{ 
    digitalWrite(pinDEL2, HIGH);
  }

  if(!digitalRead(pinBUTTON3)){
    digitalWrite(pinDEL1, LOW);
  }
  else{ 
    digitalWrite(pinDEL1, HIGH);
  }
  
  if(!digitalRead(pinBUTTON4)){
    digitalWrite(pinDEL4, LOW);
  }
  else{ 
    digitalWrite(pinDEL4, HIGH);
  }

  if(shouldRead_){
    readMsg();
    sendMsg();
  }
}

/*---------------------------Definition de fonctions ------------------------*/

void serialEvent() { shouldRead_ = true; }


/*---------------------------Definition de fonctions ------------------------
Fonction d'envoi
Entrée : Aucun
Sortie : Aucun
Traitement : Envoi du message
-----------------------------------------------------------------------------*/
void sendMsg() {
  StaticJsonDocument<500> doc;
  // Elements du message
  doc["time"] = millis();
  doc["pot"] = analogRead(A0);
  doc["bouton1"] = digitalRead(pinBUTTON1);
  doc["bouton2"] = digitalRead(pinBUTTON2);
  doc["bouton3"] = digitalRead(pinBUTTON3);
  doc["bouton4"] = digitalRead(pinBUTTON4);
  
  doc["AccX"] = analogRead(pinACCX);
  doc["AccY"] = analogRead(pinACCY);
  doc["AccZ"] = analogRead(pinACCZ);
  doc["JoyX"] = analogRead(pinJOYX);
  doc["JoyY"] = analogRead(pinJOYY);
  doc["JoyBouton"] = digitalRead(pinJOYCLICK);
  doc["Gachette1"] = digitalRead(pinGACHETTE1);
  doc["Gachette2"] = digitalRead(pinGACHETTE2);
  // Serialisation
  serializeJson(doc, Serial);

  // Envoie
  Serial.println();
  shouldSend_ = false;
}

/*---------------------------Definition de fonctions ------------------------
Fonction de reception
Entrée : Aucun
Sortie : Aucun
Traitement : Réception du message
-----------------------------------------------------------------------------*/
void readMsg(){
  // Lecture du message Json
  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  // Lecture sur le port Seriel
  DeserializationError error = deserializeJson(doc, Serial);
  shouldRead_ = false;

  // Si erreur dans le message
  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
    return;
  }
  
  // Analyse des éléments du message message
  parse_msg = doc["led"];
  if (!parse_msg.isNull()) {
    // mettre la led a la valeur doc["led"]
    digitalWrite(pinDEL1,doc["led"].as<bool>());
  }
}