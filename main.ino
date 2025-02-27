#include "WiFi.h"
#include "HTTPClient.h"


#define trigPin 26  // Pino Trig no GPIO 26
#define echoPin 27  // Pino Echo no GPIO 27
#define soundSpeed 0.034029  // Velocidade do som em cm/µs

const char* ssid = "REDE_2G";     
const char* password = "20152015@@"; 

const char* esp32Key = "my-key-secret"; 

float dist;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Conectando à ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  dist = distanceTo();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi está CONECTADO");
    if (dist > 50) {
      sendHTTPRequest();
    }
  } else {
    Serial.println("Wi-Fi DESCONECTADO");
    WiFi.reconnect();
  }

  delay(30000);
}

float distanceTo() {
  unsigned long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * soundSpeed) / 2;

  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void sendHTTPRequest() {
  HTTPClient http;

  String url = "your_api/notifications";
  Serial.print("Tentando POST para: ");
  Serial.println(url);

  if (http.begin(url)) {
    Serial.println("Conexão iniciada com sucesso");

    http.addHeader("Content-Type", "application/json");
    http.addHeader("esp32Key", esp32Key);  

    String jsonPayload = "{\"level\": " + String(dist) + "}";
    Serial.print("Enviando JSON: ");
    Serial.println(jsonPayload);
    Serial.print("Header esp32Key: ");
    Serial.println(esp32Key);

    int httpCode = http.POST(jsonPayload);

    if (httpCode > 0) {
      Serial.printf("Código HTTP: %d\n", httpCode);
      String payload = http.getString();
      Serial.println("Resposta do servidor:");
      Serial.println(payload);
    } else {
      Serial.print("Erro na requisição: ");
      Serial.println(http.errorToString(httpCode));
    }
  } else {
    Serial.println("Falha ao iniciar conexão com o servidor");
  }

  http.end();
  Serial.println("Requisição finalizada");
}
