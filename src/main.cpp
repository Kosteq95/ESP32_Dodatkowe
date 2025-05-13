#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

AsyncWebServer serwer(80);



void Scan_Network(void);
void Web_Page_Setup(void);

void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("Moj adres MAC:"+ WiFi.macAddress() + "Rozpoczynam laczenie! ");
  WiFi.begin("PAKISO_LAB","pakisolab");
  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.println("Pomyslnie połączono! Otrzymałem IP: " + WiFi.localIP().toString());
  Web_Page_Setup();

  
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

void Web_Page_Setup(void){
  serwer.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
    String html = R"html(
    <!DOCTYPE html>
<!--[if lt IE 7]>      <html class="no-js lt-ie9 lt-ie8 lt-ie7"> <![endif]-->
<!--[if IE 7]>         <html class="no-js lt-ie9 lt-ie8"> <![endif]-->
<!--[if IE 8]>         <html class="no-js lt-ie9"> <![endif]-->
<!--[if gt IE 8]>      <html class="no-js"> <!--<![endif]-->
<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>Strona Postawiona na ESP32</title>
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="">
    </head>
    <body>
        <!--[if lt IE 7]>
            <p class="browsehappy">You are using an <strong>outdated</strong> browser. Please <a href="#">upgrade your browser</a> to improve your experience.</p>
        <![endif]-->
        <h5>Witaj świecie!</h5>
        
        <script src="" async defer></script>
    </body>
</html>
    )html";


    request->send(200,"text/html",html);
  });

  serwer.begin();
}

//TEST
