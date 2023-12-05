#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11

/*Put your SSID & Password*/
const char* ssid = "NodemCu";  //Wifi adınız
const char* password = "kodeli123";  //wifi şifreniz

ESP8266WebServer server(80); //80 portunu kullanarak bir web server nesnesi oluşturduk

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 41);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

uint8_t DHTPin = D4;
uint8_t LED1pin = D2;
bool LED1status = LOW; //durumlarını tanımlıyoruz.
uint8_t LED2pin = D3;
bool LED2status = LOW;
uint8_t LED3pin = D5;
bool LED3status = LOW;
               
// DHT'yi tanımlıyoruz..
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  pinMode(LED3pin, OUTPUT);

  dht.begin();              
if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect); //Bağlantı sağlandıktan sonra server kontrolleri.
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/led3on", handle_led3on);
  server.on("/led3off", handle_led3off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Sunucusu Başladı");

}
void loop() {
  
  server.handleClient(); 
   if(LED1status)
  {digitalWrite(LED1pin, LOW);}
  else
  {digitalWrite(LED1pin, HIGH);}
  if(LED2status)
  {digitalWrite(LED2pin, LOW);}
  else
  {digitalWrite(LED2pin, HIGH);}
  if(LED3status)
  {digitalWrite(LED3pin, LOW);}
  else
  {digitalWrite(LED3pin, HIGH);}
  
}

void handle_OnConnect() {

  Temperature = dht.readTemperature(); // 
  Humidity = dht.readHumidity(); // 

  Serial.print("Sıcaklık: ");
  Serial.print(Temperature);
  Serial.print(" °C, Nem: ");
  Serial.print(Humidity);
  Serial.println(" %");

  LED1status = LOW;
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,LED2status,LED3status)); 
}
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("D2 Durumu: ON");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,true,LED2status,LED3status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("D2 Durumu: OFF");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,false,LED2status,LED3status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("D3 Durumu: ON");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,true,LED3status)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("D3 Durumu: OFF");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,false,LED3status)); 
}
void handle_led3on() {
  LED3status = HIGH;
  Serial.println("D5 Durumu: ON");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,LED2status,true)); 
}

void handle_led3off() {
  LED3status = LOW;
  Serial.println("D5 Durumu: OFF");
  server.send(200, "text/html", SendHTML(Temperature,Humidity,LED1status,LED2status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat,uint8_t led1stat,uint8_t led2stat,uint8_t led3stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<meta charset=\"utf-8\">\n";
  ptr +="<title>ESP8266 NodeMCU Akilli Ev</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c ;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #0095c7;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body bgcolor= BlanchedAlmond style=color:white>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU Akıllı Ev</h1>\n";
  
  ptr +="<p>SICAKLIK: ";
  ptr +=(int)Temperaturestat;
  ptr +="°C</p>";
  ptr +="<p>NEM: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  if(led1stat)
  {ptr +="<p>LED1 Durum: AÇIK</p><a class=\"button button-off\" href=\"/led1off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED1 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led1on\">AÇ</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Durum: AÇIK</p><a class=\"button button-off\" href=\"/led2off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED2 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led2on\">AÇ</a>\n";}

  if(led3stat)
  {ptr +="<p>LED3 Durum: AÇIK</p><a class=\"button button-off\" href=\"/led3off\">KAPAT</a>\n";}
  else
  {ptr +="<p>LED3 Durum: KAPALI</p><a class=\"button button-on\" href=\"/led3on\">AÇ</a>\n";}


  //Robolink Logo
  ptr += "<img src= 'data:image/png;base64,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' Z\" width=\"396\" height=\"198\">\n";  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}