#include "esp32-hal-gpio.h"
#include <LiquidCrystal.h>
const int BOTON_ELECCION = 14;
const int BOTON_CONFIRMACION = 27;
const int OPTO_PIN = 12;
const int LED = 23;
const int VUELTAS_POR_PORCION = 20;  // Ajusta este valor según sea necesario
const int DELAY_REBOTE = 50;
const int MAX_PORCIONES = 10;
int contadorVueltas = 0;
const int dientes_vueltas = 0;
bool ant_elec = HIGH;
bool ant_opto = HIGH;
bool ant_conf = HIGH;
int porciones = 0;
int porciones_int = 0;

const int rs = 3, en = 21, d4 = 19, d5 = 18, d6 = 5, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void actualizar_lcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Porciones: ");
  lcd.print(porciones);
  lcd.setCursor(0, 1);
  lcd.print("Apreta Confirmar");
};
int elegir_porcion() {
  bool lectura_eleccion = digitalRead(BOTON_ELECCION);
  if (lectura_eleccion != ant_elec) {
    delay(DELAY_REBOTE);
    if (lectura_eleccion == LOW) {
      if (porciones >= MAX_PORCIONES) {
        Serial.println("Ya esta capo deja de romper");
        ant_elec = lectura_eleccion;
        return porciones;
      }
      porciones++;
      Serial.print("Porciones: ");
      Serial.println(porciones);
      actualizar_lcd();
    }
    ant_elec = lectura_eleccion;
  }
  return porciones;
};

bool confirmar() {
  bool lectura_confirmacion = digitalRead(BOTON_CONFIRMACION);
  if (lectura_confirmacion != ant_conf) {
    delay(DELAY_REBOTE);
    if (lectura_confirmacion == LOW) {
      return HIGH;
    }
    ant_conf = lectura_confirmacion;
  }
  return LOW;
};

void contar_vueltas() {
  bool lectura_opto = digitalRead(OPTO_PIN);
  if (lectura_opto != ant_opto) {
    delay(DELAY_REBOTE);
    if (lectura_opto == LOW) {
      contadorVueltas += 20;
      Serial.println(contadorVueltas);
    }
    ant_opto = lectura_opto;
  }
};

void dispensarComida() {
  int vueltasObjetivo = porciones * VUELTAS_POR_PORCION;

  Serial.print("Dispensando ");
  Serial.print(porciones);
  Serial.println(" porciones...");
  lcd.setCursor(0, 1);
  lcd.print("Dispensando...  ");

  contadorVueltas = 0;
  while (contadorVueltas < vueltasObjetivo) {
    digitalWrite(LED, HIGH);
    contar_vueltas();
  }
  porciones = 0;
  digitalWrite(LED, LOW);  // Apaga el motor
  lcd.clear();
  lcd.print("Completado");
  delay(1000);
  lcd.clear();
  lcd.print("Elija Porciones");
  Serial.println("Dispensado completo.");
  Serial.println("Ingrese el número de porciones para la próxima vez:");
};
