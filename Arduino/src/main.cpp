/* 
 * Auteurs: Jean-Samuel Lauzon    
 * Date: Fevrier 2022
*/

/*------------------------------ Librairies ---------------------------------*/
#include <Arduino.h>
#include <ArduinoJson.h>

/*------------------------------ Constantes ---------------------------------*/

#define BAUD 9600        // Frequence de transmission serielle

/*---------------------------- Variables globales ---------------------------*/

volatile bool shouldSend_ = false;  // Drapeau prêt à envoyer un message
volatile bool shouldRead_ = false;  // Drapeau prêt à lire un message

int ledState = 0;
int potValue = 0;

// Pin potentiomatte
// DIFF: A0

// Pins bargraph
#define pinBAR1 3
#define pinBAR2 4
#define pinBAR3 5
#define pinBAR4 6
#define pinBAR5 7
#define pinBAR6 8
#define pinBAR7 9
#define pinBAR8 10
#define pinBAR9 11
#define pinBAR10 12

// Pins DELs
#define pinDEL1 22
#define pinDEL2 24
#define pinDEL3 26
#define pinDEL4 28

// Pins Acceleromatte
// X: A1 Y: A2 Z: A3

// Pins Boutons/Gachettes
#define pinBUTTON1 23
#define pinBUTTON2 25
#define pinBUTTON3 27
#define pinBUTTON4 29
#define pinGACHETTE1 31
#define pinGACHETTE2 33

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
  pinMode(A1, INPUT); // X
  pinMode(A2, INPUT); // Y
  pinMode(A3, INPUT); // Z

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
}

/* Boucle principale (infinie) */
void loop() {

  if(shouldRead_){
    readMsg();
    sendMsg();
  }

  potValue = analogRead(A0);
  //Serial.println(potValue);          // debug
  
  // Acceleromatte
  int accX = analogRead(A1);
  int accY = analogRead(A2);
  int accZ = analogRead(A3);

  //Serial.println(accX);
  //Serial.println(accY);
  //Serial.println(accZ);

  // Bar Graph
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

  //Serial.println(analogRead(A0));
  switch (map(potValue, 500, 1000, 0, 10))
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
    break;
  case 2:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    break;
  case 3:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    break; 
  case 4:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    break;
  case 5:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    break; 
  case 6:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    break; 
  case 7:
    digitalWrite(pinBAR1, LOW);
    digitalWrite(pinBAR2, LOW);
    digitalWrite(pinBAR3, LOW);
    digitalWrite(pinBAR4, LOW);
    digitalWrite(pinBAR5, LOW);
    digitalWrite(pinBAR6, LOW);
    digitalWrite(pinBAR7, LOW);
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
  Serial.println(digitalRead(pinBUTTON1));
  Serial.println(digitalRead(pinBUTTON2));
  Serial.println(digitalRead(pinBUTTON3));
  Serial.println(digitalRead(pinBUTTON4));

  if(!digitalRead(pinBUTTON1)){
    digitalWrite(pinDEL1, HIGH);
  }
  else {
    digitalWrite(pinDEL1, LOW);
  }

  if(!digitalRead(pinBUTTON2)){
    digitalWrite(pinDEL2, HIGH);
  }
  else{ 
    digitalWrite(pinDEL2, LOW);
  }

  if(!digitalRead(pinBUTTON3)){
    digitalWrite(pinDEL3, HIGH);
  }
  else{ 
    digitalWrite(pinDEL3, LOW);
  }
  
  if(!digitalRead(pinBUTTON4)){
    digitalWrite(pinDEL4, HIGH);
  }
  else{ 
    digitalWrite(pinDEL4, LOW);
  }
  delay(50);  // delais de 10 ms
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
  doc["analog"] = potValue;

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