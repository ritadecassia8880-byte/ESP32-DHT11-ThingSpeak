#include <WiFi.h>

// Dados da rede Wi-Fi
const char* ssid = "wifi name";
const char* password = "password";

void setup() {
  // Inicia o Monitor Serial
  Serial.begin(115200);

  // Inicia a conexão com o Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Conectando ao Wi-Fi");

  // Aguarda até a ESP32 se conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Informa que a conexão foi realizada
  Serial.println();
  Serial.println("Wi-Fi conectado!");

  // Mostra o endereço IP da ESP32
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Não há nenhuma ação contínua neste primeiro teste
}