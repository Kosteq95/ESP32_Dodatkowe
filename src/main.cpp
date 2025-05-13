#include <Arduino.h>
#include <WiFi.h>


void Scan_Network(void);

void setup() {
  pinMode(2,OUTPUT);
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  
  
}

void loop() {
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);
  Scan_Network();
}


void Scan_Network(void){
  int n = WiFi.scanNetworks();
  if (n == 0)
    Serial.println("Nie znaleziono sieci WiFi");
  else
    Serial.printf("Znaleziono %d sieci. \n\r", n);
    
    for (uint8_t i = 0; i < n; i++)
    {
      String nazwa_sieci = WiFi.SSID(i);
      int32_t sila_sieci = WiFi.RSSI(i);
      
      Serial.println(String(i) +". Nazwa sieci:" + nazwa_sieci + " Siła sygnału:" + String(sila_sieci));
    }
    

}

