#include <WiFi.h>
#include "ThingSpeak.h"

// Dados da rede Wi-Fi
const char* ssid = "wifi name";
const char* password = "password";

// Cria o objeto responsável pela conexão de rede
WiFiClient client;

// Número do canal utilizado no ThingSpeak
unsigned long myChannelNumber = "channel id";

// Chave de escrita do ThingSpeak
const char* myWriteAPIKey = "SUA_WRITE_API_KEY";

// Valor utilizado apenas para testar o envio de dados
float valor = 0;

void setup() {
  // Inicia o Monitor Serial
  Serial.begin(9600);
  delay(500);

  // Inicia a conexão com o Wi-Fi
  WiFi.begin(ssid, password);

  // Aguarda a conexão com a rede
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao Wi-Fi...");
  }

  Serial.println("Wi-Fi conectado!");

  // Define a ESP32 para trabalhar no modo estação
  WiFi.mode(WIFI_MODE_STA);

  // Mostra o endereço MAC da ESP32
  Serial.println(WiFi.macAddress());

  // Inicia a comunicação com o ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Envia o valor para o Field 1 do ThingSpeak
  int x = ThingSpeak.writeField(
    myChannelNumber,
    1,
    valor,
    myWriteAPIKey
  );

  // Verifica se o envio foi realizado com sucesso
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    // Mostra o código do erro caso o envio falhe
    Serial.println(
      "Problema ao atualizar o canal. HTTP error code: "
      + String(x)
    );
  }

  // Incrementa o valor utilizado no teste
  valor = valor + 1;

  // Aguarda 15,1 segundos antes do próximo envio
  delay(15100);

  // Reinicia o valor quando chegar a 10
  if (valor == 10) {
    valor = 0;
  }
}
