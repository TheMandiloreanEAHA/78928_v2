#include <WiFi.h>

const char* ssid = "dr-rojano";
const char* password = "78928-tw";

void setup() {
  Serial.begin(115200);
  delay(10);
  //Se inicia la conexión
  Serial.println();
  Serial.println();
  Serial.println("Conecting to");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  //Se verifica y se realiza la conexión
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //Lograda la conexión, muestra la información
  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.println("IP Adress: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  // put your main code here, to run repeatedly:
}
