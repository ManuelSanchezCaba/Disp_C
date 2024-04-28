#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(39, 38, 37, 36, 35, 34);

const int titleDuration = 5000;
const int calibreButton = 46;
const int longitudButton = 42;
const int cantidadButton = 43;
const int incrementarButton = 44;
const int decrementarButton = 45;
const int calibre12Button = 46;
const int calibre14Button = 47;
const int calibre16Button = 48;
const int okButton = 49;

int menu = 0;
int longitud = 1;
int cantidad = 1;
int calibre = 12;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Dispensador de");
  lcd.setCursor(0, 1);
  lcd.print("cable");
  delay(titleDuration);
  lcd.clear();
  updateMenu();
  pinMode(calibreButton, INPUT_PULLUP);
  pinMode(longitudButton, INPUT_PULLUP);
  pinMode(cantidadButton, INPUT_PULLUP);
  pinMode(incrementarButton, INPUT_PULLUP);
  pinMode(decrementarButton, INPUT_PULLUP);
  pinMode(calibre12Button, INPUT_PULLUP);
  pinMode(calibre14Button, INPUT_PULLUP);
  pinMode(calibre16Button, INPUT_PULLUP);
  pinMode(okButton, INPUT_PULLUP);

  Serial.begin(9600); // Inicializar comunicación serial
}

void loop() {
  if (!digitalRead(longitudButton)) {
    menu = 0;
    updateMenu();
    delay(100);
    while (!digitalRead(longitudButton));
  }
  if (!digitalRead(cantidadButton)) {
    menu = 1;
    updateMenu();
    delay(100);
    while (!digitalRead(cantidadButton));
  }

  switch (menu) {
    case 0: // Longitud
      if (!digitalRead(incrementarButton)) {
        longitud++;
        if (longitud < 1) {
          longitud = 1;
        }
        updateMenu();
        delay(200);
        while (!digitalRead(incrementarButton));
      }
      if (!digitalRead(decrementarButton)) {
        longitud--;
        if (longitud < 1) {
          longitud = 1;
        }
        updateMenu();
        delay(200);
        while (!digitalRead(decrementarButton));
      }
      break;
    case 1: // Cantidad
      if (!digitalRead(incrementarButton)) {
        cantidad++;
        if (cantidad < 1) {
          cantidad = 1;
        }
        updateMenu();
        delay(200);
        while (!digitalRead(incrementarButton));
      }
      if (!digitalRead(decrementarButton)) {
        cantidad--;
        if (cantidad < 1) {
          cantidad = 1;
        }
        updateMenu();
        delay(200);
        while (!digitalRead(decrementarButton));
      }
      break;
  }

  if (!digitalRead(calibre12Button)) {
    calibre = 12;
    updateMenu();
    delay(100);
    while (!digitalRead(calibre12Button));
  }
  if (!digitalRead(calibre14Button)) {
    calibre = 14;
    updateMenu();
    delay(100);
    while (!digitalRead(calibre14Button));
  }
  if (!digitalRead(calibre16Button)) {
    calibre = 16;
    updateMenu();
    delay(100);
    while (!digitalRead(calibre16Button));
  }

  if (!digitalRead(okButton)) {
    // Enviar datos al Arduino Uno a través de la comunicación serial
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("okButton: ");
    lcd.setCursor(0, 1);
    String data = String(calibre) + "," + String(longitud) + "," + String(cantidad);
    String data2 = "Hello from Arduino Uno";
    lcd.print(data2);
    Serial.println(data2);
    Serial.write(data2);
    delay(100);
//    while (!digitalRead(okButton));
  }
}

void updateMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibre ");
  lcd.print(calibre);
  lcd.setCursor(0, 1);
  
  switch (menu) {
    case 0: // Longitud
      lcd.print("Longitud: ");
      lcd.print(longitud);
      lcd.print("    ");
      break;
    case 1: // Cantidad
      lcd.print("Cantidad: ");
      lcd.print(cantidad);
      lcd.print("    ");
      break;
  }
}
