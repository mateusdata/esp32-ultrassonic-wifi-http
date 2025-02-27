#include "WiFi.h"
#include "HTTPClient.h"

// Definições do sensor ultrassônico
#define trigPin 26  // Pino Trig no GPIO 26
#define echoPin 27  // Pino Echo no GPIO 27
#define soundSpeed 0.034029  // Velocidade do som em cm/µs

// Definições da rede Wi-Fi
const char* ssid = "REDE_2G";      // Nome da rede Wi-Fi
const char* password = "20152015@@";  // Senha da rede

float dist;

void setup() {
  Serial.begin(9600);  // Inicia a comunicação serial a 9600 bps

  // Configurações dos pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Conexão com a rede Wi-Fi
  WiFi.mode(WIFI_STA);  // Define o modo estação (client)
  WiFi.begin(ssid, password);  // Conecta à rede Wi-Fi

  Serial.print("Conectando à ");
  Serial.println(ssid);

  // Aguarda até conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP()); // Mostra o IP obtido na rede
}

void loop() {
  dist = distanceTo();  // Chama a função para medir a distância

  // Se a distância for maior que 50 cm, faz a requisição HTTP
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi está CONECTADO");
  }
  if (dist > 100) {
    sendHTTPRequest();
  }

  delay(200);  // Delay para evitar leituras rápidas demais
}

// Função para medir a distância
float distanceTo() {
  unsigned long duration;
  float distance;

  // Envia o pulso para o sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // Mede o tempo do pulso

  // Calcula a distância em cm
  distance = (duration * soundSpeed) / 2;

  // Exibe a distância no Monitor Serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// Função para enviar a requisição HTTP
void sendHTTPRequest() {
  
  HTTPClient http;

  // Define o URL para a requisição
  http.begin("https://api-pink-eta.vercel.app/notifications");

  // Faz a requisição GET
  int httpCode = http.GET();

  if (httpCode > 0) {
    // Se a requisição for bem-sucedida, imprime o código HTTP
    Serial.printf("Código HTTP: %d\n", httpCode);

    // Obtém o conteúdo da resposta
    String payload = http.getString();
    
    // Imprime a resposta JSON
    Serial.println("Resposta JSON:");
    Serial.println(payload);
  } else {
    // Se houver erro na requisição, imprime o código de erro
    Serial.printf("Erro na requisição HTTP: %d\n", httpCode);
  }

  // Libera os recursos utilizados pela requisição
  http.end();
}
