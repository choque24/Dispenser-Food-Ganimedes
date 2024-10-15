#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"
#include "var_const.h"
const char *ssid = "Jes32"; // red wifi
const char *password = "1234569701"; // contraseña de red wifi

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = -14400; // resta 3 horas para ajustar la zona horaria
const int daylightOffset_sec = 3600; // una hora en segundos

const uint16_t espera = 1000;

const long tarde = 43200; // 12 horas en segundos

const char *time_zone = "CET-1CEST,M3.5.0,M10.5.0/3";

unsigned long lastActivationTime = 0;
bool isActive = false;

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}

void setup() { {
  Serial.begin(115200);
 Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(BOTON_ELECCION, INPUT_PULLUP);
  pinMode(OPTO_PIN, INPUT_PULLUP);
  pinMode(BOTON_CONFIRMACION, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.println("Dispensador de comida listo. Ingrese el número de porciones:");
  lcd.print("Elija Porciones");
}
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  esp_sntp_servermode_dhcp(1);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  sntp_set_time_sync_notification_cb(timeavailable);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  // Inicializar el tiempo de la última activación
  lastActivationTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Verificar si han pasado 12 horas desde la última activación/desactivación
  if (currentTime - lastActivationTime >= tarde) {
    isActive = !isActive; // Cambiar el estado
    lastActivationTime = currentTime; // Actualizar el tiempo de la última activación
    
    if (isActive) {
      Serial.println("Activado");
      // Aquí puedes agregar el código para activar lo que necesites
       if (elegir_porcion() >= 1) {
    if (confirmar()) {
      dispensarComida();
    }
  }



    } else {
      Serial.println("Desactivado");
      // Aquí puedes agregar el código para desactivar lo que necesites


    }
  }
  
  // Imprimir el tiempo local cada segundo
  static unsigned long lastPrintTime = 0;
  if (currentTime - lastPrintTime >= espera) {
    printLocalTime();
    lastPrintTime = currentTime;
  }
}