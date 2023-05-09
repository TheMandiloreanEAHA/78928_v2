#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char* ssid= "Redmi Note 7";
const char* password = "ickkck16";
AsyncWebServer server(80);

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  conectarse();
  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request){
    int numParametros =request->params();
    Serial. print(numParametros);
    if(numParametros ==0){
      request->send(200,"text/html","<h1> hola mundo </h1>");
      digitalWrite(2, HIGH);
    }else{
      AsyncWebParameter *p=request->getParam(0);
      String html="<H1> hola " + p->value() + "desde ESP32</H1>";
      request->send(200,"text/html",html);
    }
  });

  server.on("/adios",HTTP_GET,[](AsyncWebServerRequest *r){
    r->send(200,"text/html","<h1>adios</h1>");
    digitalWrite(2, LOW);
  });
  
  server.begin();

}
void loop() {
  // put your main code here, to run repeatedly:
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