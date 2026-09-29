#include <WiFi.h>
#include "ThingSpeak.h"

// Dados da rede Wi-Fi
const char* ssid = "wifi name";
const char* password = "password";

// Objeto utilizado para a comunicação com a internet
WiFiClient client;

// Número do canal utilizado no ThingSpeak
unsigned long myChannelNumber = "channel id";

// Chave de escrita do ThingSpeak
const char* myWriteAPIKey = "SUA_WRITE_API_KEY";

// Valores utilizados para testar os dois Fields
float valor1 = 0;
float valor2 = 100;

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

  // Define a ESP32 como estação Wi-Fi
  WiFi.mode(WIFI_MODE_STA);

  // Mostra o endereço MAC da ESP32
  Serial.println(WiFi.macAddress());

  // Inicia a comunicação com o ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Define o valor que será enviado para o Field 1
  ThingSpeak.setField(1, valor1);

  // Define o valor que será enviado para o Field 2
  ThingSpeak.setField(2, valor2);

  // Envia os dois Fields para o mesmo canal
  int x = ThingSpeak.writeFields(
    myChannelNumber,
    myWriteAPIKey
  );

  // Verifica se o envio foi realizado com sucesso
  if (x == 200) {
    Serial.println("Fields atualizados com sucesso.");
  } else {
    // Mostra o código do erro caso o envio falhe
    Serial.println(
      "Problema ao atualizar os Fields. HTTP error code: "
      + String(x)
    );
  }

  // Altera os valores para o próximo teste
  valor1 = valor1 + 1;
  valor2 = valor2 + 1;

  // Reinicia o primeiro valor quando chegar a 10
  if (valor1 == 10) {
    valor1 = 0;
  }

  // Reinicia o segundo valor quando chegar a 110
  if (valor2 == 110) {
    valor2 = 100;
  }

  // Aguarda 15,1 segundos antes do próximo envio
  delay(15100);
}