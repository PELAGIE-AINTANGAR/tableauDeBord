#include <LiquidCrystal.h>  // Inclure la librairie pour l'écran LCD
#include <DHT.h>  // Inclure la librairie pour le capteur DHT

#define DHTPIN 13   // Définir la broche de signal du capteur DHT
#define DHTTYPE DHT11   // Définir le type de capteur DHT
DHT dht(DHTPIN, DHTTYPE);   // Créer une instance du capteur DHT

const int ledBleu = A1;  // Broche pour la LED bleue
const int ledRouge = A2; // Broche pour la LED rouge
const int ledVerte = A3; // Broche pour la LED verte
const int ledJaune = A4; // Broche pour la LED jaune

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);  // Définir les broches pour l'écran LCD

void setup() {
  lcd.begin(16, 2);  // Initialiser l'écran LCD
  dht.begin();  // Initialiser le capteur DHT
  pinMode(ledBleu, OUTPUT);
  pinMode(ledRouge, OUTPUT);
  pinMode(ledVerte, OUTPUT);
  pinMode(ledJaune, OUTPUT);
}

void loop() {
  // Lire la température et l'humidité
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Allumer la LED bleue si la température est inférieure à 22 degrés Celsius, sinon allumer la LED rouge
  if (temperature < 22) {
    analogWrite(ledBleu, 255);  // Allumer la LED bleue à pleine intensité (255)
    analogWrite(ledRouge, 0);   // Éteindre la LED rouge
  } else {
    analogWrite(ledBleu, 0);    // Éteindre la LED bleue
    analogWrite(ledRouge, 255); // Allumer la LED rouge à pleine intensité (255)
  }

  // Allumer la LED verte si l'humidité est confortable, sinon allumer la LED jaune
  if (humidity >= 40 && humidity <= 60) {
    analogWrite(ledVerte, 255); // Allumer la LED verte à pleine intensité (255)
    analogWrite(ledJaune, 0);   // Éteindre la LED jaune
  } else {
    analogWrite(ledVerte, 0);   // Éteindre la LED verte
    analogWrite(ledJaune, 255); // Allumer la LED jaune à pleine intensité (255)
  }

  // Afficher les données sur l'écran LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(2000);  // Attendre 2 secondes avant de lire à nouveau les données
}