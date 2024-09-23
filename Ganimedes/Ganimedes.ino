#include "var_const.h"

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BOTON_ELECCION, INPUT_PULLUP);
  pinMode(OPTO_PIN, INPUT_PULLUP);
  pinMode(BOTON_CONFIRMACION, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.println("Dispensador de comida listo. Ingrese el número de porciones:");
  lcd.print("Elija Porciones");
}

void loop() {
  if (elegir_porcion() >= 1) {
    if (confirmar()) {
      dispensarComida();
    }
  }
}
