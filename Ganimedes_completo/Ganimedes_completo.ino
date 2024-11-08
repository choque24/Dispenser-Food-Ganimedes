/*
Proyecto: Dispenser de Comida para mascotas - Ganimedes

Finalidad Objetivos:  
  Dispensar comida en porciones elegibles por el usuario, además de automatizar su dispensacion
  Creacion de usuarios y perfiles acorde a la mascota

Cosas que hace:
  Leer la cantidad de vueltas del motor, calculando la porcion indicada
  Dispensar de manera precisa la comida

Metas: Simplificar code, que ande todo, que sea entendible escalable, etc

Mejoras:
  Creacion de aplicacion controladora
  Mejorar la interfaz de usuario
  Mejorar su gabinete

Faltantes:
  Probar, ensayar, realizar informe, manual de usuario, 
  Plaqueta para prototipado
*/

#include "var_const.h"
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Configuración de pines
  pinMode(BOTON_ELECCION, INPUT_PULLUP);
  pinMode(OPTO_PIN, INPUT_PULLUP);
  pinMode(BOTON_CONFIRMACION, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Configurar hora inicial (ajusta según necesites)
  rtc.setTime(0, 0, 0, 1, 1, 2024);  // 00, 1 de Enero 2024

  Serial.println("Dispensador de comida listo. Ingrese el número de porciones:");
  lcd.print("Elija Porciones");
}

void loop() {
  // Verificar si es hora de dispensar automáticamente
  verificarHoraDispensacion();
  // Mostrar hora actual en Serial para debug
  if (rtc.getMinute() % 10 == 0) {  // Cada minuto Cumple el if
    // Serial.printf("Hora actual: %02d:%02d\n", rtc.getHour(true), rtc.getMinute());
    dispensarComidaAutomatica();
  }

  // Mantener la funcionalidad manual
  if (elegir_porcion() >= 1) {
    if (confirmar()) {
      dispensarComida();
    }
  }
}