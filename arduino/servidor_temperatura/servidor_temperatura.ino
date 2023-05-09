#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

#include "DHTesp.h"
#define DHTpin 15
DHTesp dht;


const char* ssid= "Redmi Note 7";
const char* password = "ickkck16";
AsyncWebServer server(80);

void setup() {

  Serial.begin(115200);
  conectarse();
  Serial.println("Estado\tHumedad (%)\tTemperatura (C)\t(F)\tIndiceCalor (C)\t(F)");
  dht.setup(DHTpin, DHTesp::DHT11);

  delay(dht.getMinimumSamplingPeriod());
  float humedad =  dht.getHumidity();
  float temperatura = dht.getTemperature();
  if (isnan(humedad) || isnan(temperatura)){
    Serial.println("No se pudo leer sensor DHT!");
    return;
  }
  
  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request){
    int numParametros =request->params();
    Serial. print(numParametros);
    if(numParametros ==0){
      request->send(200,"text/html","<h1> Sensor de temperatura GOD </h1>");
      
    }else{
      AsyncWebParameter *p=request->getParam(0);
      String html="<H1> hola " + p->value() + "desde ESP32</H1>";
      request->send(200,"text/html",html);
    }
  });

  server.on("/estado",HTTP_GET,[](AsyncWebServerRequest *r){
    String aux = dht.getStatusString();
    String htmlR="<H1>Estado del sensor: " + aux + "</H1>";
    r->send(200,"text/html",htmlR);
    
  });

  server.on("/c",HTTP_GET,[](AsyncWebServerRequest *r){
    float temperatura = dht.getTemperature();
    String htmlR="<H1>Temperatura: \t" + String(temperatura) + " C</H1>";
    r->send(200,"text/html",htmlR);
    
  }); 

  server.on("/f",HTTP_GET,[](AsyncWebServerRequest *r){
    float temperatura = dht.getTemperature();
    float tempF = dht.toFahrenheit(temperatura);
    String htmlR="<H1>Temperatura: \t" + String(tempF) + " F</H1>";
    r->send(200,"text/html",htmlR);
    
  });  
  
  server.on("/h",HTTP_GET,[](AsyncWebServerRequest *r){
    float humedad =  dht.getHumidity();
    String htmlR="<H1>Humedad: \t" + String(humedad) + "</H1>";
    r->send(200,"text/html",htmlR);
  });   

  server.on("/ic",HTTP_GET,[](AsyncWebServerRequest *r){
    float humedad =  dht.getHumidity();
    float temperatura = dht.getTemperature();    
    float icc = dht.computeHeatIndex(temperatura, humedad, false);
    String htmlR="<H1>Indice de calor: \t" + String(icc) + "C</H1>";
    r->send(200,"text/html",htmlR);
  });  

  server.on("/if",HTTP_GET,[](AsyncWebServerRequest *r){
    float humedad =  dht.getHumidity();
    float temperatura = dht.getTemperature();
    float icf = dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true);
    String htmlR="<H1>Indice de calor: \t" + String(icf) + "F</H1>";
    r->send(200,"text/html",htmlR);
  });  
  
  server.begin();

}
void loop() {
  
}

void conectarse(){
  Serial.print("Conectando");Serial.println(ssid);
  WiFi.begin(ssid,password);
while(WiFi.status()!=WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
Serial.print(WiFi.localIP());
}
