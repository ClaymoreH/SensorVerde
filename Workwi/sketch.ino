#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org"; 
const char* weather_api_key = "YOUR API HERE"; //Coloca tua api

// *** Cada ESP32 tem um ID***
const char* userID = "user_321"; 

WiFiClient espClient;
PubSubClient client(espClient);

const float BETA = 3950;  

void setup_wifi() {
  Serial.print("Conectando ao WiFi: ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi conectado! IP: " + WiFi.localIP().toString());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Recebido no tópico: ");
  Serial.println(topic);

  String receivedPayload;
  for (int i = 0; i < length; i++) {
    receivedPayload += (char)payload[i];
  }
  
  Serial.println("Mensagem: " + receivedPayload);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(userID)) {  
      Serial.println("Conectado!");

      // Cada ESP se inscreve apenas no seu próprio tópico
      String userTopic = "sensorVerde/" + String(userID);
      client.subscribe(userTopic.c_str());
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void getWeatherData() {
  HTTPClient http;
  String url = "http://api.weatherapi.com/v1/current.json?key=" + String(weather_api_key) + "&q=auto:ip";
  http.begin(url);
  
  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      StaticJsonDocument<512> weatherDoc;
      deserializeJson(weatherDoc, payload);

      StaticJsonDocument<256> doc;
      doc["UserID"] = userID;  // ID do usuário
      doc["Location"] = weatherDoc["location"]["name"].as<String>();
      doc["Region"] = weatherDoc["location"]["region"].as<String>();
      doc["Country"] = weatherDoc["location"]["country"].as<String>();
      doc["Temperature"] = weatherDoc["current"]["temp_c"].as<float>();
      doc["Condition"] = weatherDoc["current"]["condition"]["text"].as<String>();

      char jsonBuffer[256];
      serializeJson(doc, jsonBuffer);

      String weatherTopic = "sensorVerde/" + String(userID);
      client.publish(weatherTopic.c_str(), jsonBuffer);
      
      Serial.println("Dados do clima publicados:");
      Serial.println(jsonBuffer);
    }
  } else {
    Serial.print("Erro ao conectar à API do clima. Código HTTP: ");
    Serial.println(httpCode);
  }
  http.end();
}

void Publica_dados() {
  int valorPOT = analogRead(34);
  int Pot_Percent = map(valorPOT, 0, 4095, 0, 100);

  int analogValue = analogRead(35);
  float celsius = 1 / (log(1 / (4095. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  celsius = round(celsius * 10) / 10.0;

  StaticJsonDocument<256> doc;
  doc["UserID"] = userID;  // ID do usuário
  doc["Potenciometro"] = Pot_Percent;
  doc["Temperatura"] = celsius;

  char jsonBuffer[256];
  serializeJson(doc, jsonBuffer);

  // Publicar no tópico exclusivo do usuário
  String sensorTopic = "sensorVerde/" + String(userID);
  client.publish(sensorTopic.c_str(), jsonBuffer);
  
  Serial.println("Dados do sensor publicados:");
  Serial.println(jsonBuffer);
}

void setup() {
  pinMode(2, OUTPUT);     
  pinMode(15, OUTPUT);
  Serial.begin(115200);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void LEDs()
{
  //Conexao_WIFI
  if(WiFi.status())
  digitalWrite(2, HIGH);
  else
  digitalWrite(2, LOW);
  
  //Conexao_MQTT()
  if(client.connected())
  digitalWrite(15, HIGH);
  else
  digitalWrite(15, LOW);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  getWeatherData();
  Publica_dados();
  LEDs();
  delay(10000); 
}
