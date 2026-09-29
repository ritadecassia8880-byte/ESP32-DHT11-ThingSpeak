#include <WiFi.h>
#include "ThingSpeak.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// ==============================
// CONFIGURAÇÃO DO WI-FI
// ==============================

const char* ssid = "wifi name";
const char* password = "password";

// Objeto responsável pela conexão de rede
WiFiClient client;


// ==============================
// CONFIGURAÇÃO DO SENSOR DHT11
// ==============================

// Pino DATA do DHT11 conectado ao GPIO 4 da ESP32
#define DHTPIN 4

// Define o modelo do sensor
#define DHTTYPE DHT11

// Cria o objeto do sensor
DHT_Unified dht(DHTPIN, DHTTYPE);

// Tempo mínimo entre as leituras do sensor
uint32_t delayMS;


// ==============================
// CONFIGURAÇÃO DO THINGSPEAK
// ==============================

// Número do canal utilizado no ThingSpeak
unsigned long myChannelNumber = "channel id";

// Chave utilizada para enviar os dados
const char* myWriteAPIKey = "SUA_WRITE_API_KEY";


void setup() {

  // Inicia o Monitor Serial
  Serial.begin(9600);
  delay(500);


  // ==============================
  // INICIA O SENSOR
  // ==============================

  dht.begin();

  Serial.println("DHT11 iniciado.");

  // Obtém as informações do sensor
  sensor_t sensor;

  dht.temperature().getSensor(&sensor);

  // Obtém o intervalo mínimo recomendado entre leituras
  delayMS = sensor.min_delay / 1000;


  // ==============================
  // CONEXÃO COM O WI-FI
  // ==============================

  WiFi.begin(ssid, password);

  // Aguarda até a ESP32 se conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao Wi-Fi...");
  }

  Serial.println("Wi-Fi conectado!");

  // Define a ESP32 como estação Wi-Fi
  WiFi.mode(WIFI_MODE_STA);

  // Mostra o endereço MAC da ESP32
  Serial.println(WiFi.macAddress());


  // ==============================
  // INICIA O THINGSPEAK
  // ==============================

  ThingSpeak.begin(client);

  Serial.println("ThingSpeak iniciado.");
}


void loop() {

  // Aguarda o intervalo recomendado pelo sensor
  delay(delayMS);

  // Cria uma variável para armazenar as informações da leitura
  sensors_event_t event;


  // ==============================
  // LEITURA DA TEMPERATURA
  // ==============================

  dht.temperature().getEvent(&event);

  // Verifica se ocorreu algum erro na leitura
  if (isnan(event.temperature)) {
    Serial.println("Erro ao ler temperatura!");
    return;
  }

  // Armazena a temperatura em uma variável
  float temperatura = event.temperature;


  // ==============================
  // LEITURA DA UMIDADE
  // ==============================

  dht.humidity().getEvent(&event);

  // Verifica se ocorreu algum erro na leitura
  if (isnan(event.relative_humidity)) {
    Serial.println("Erro ao ler umidade!");
    return;
  }

  // Armazena a umidade em uma variável
  float umidade = event.relative_humidity;


  // ==============================
  // MOSTRA OS DADOS NO MONITOR SERIAL
  // ==============================

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  Serial.println("-----------------------------");


  // ==============================
  // ENVIO PARA O THINGSPEAK
  // ==============================

  // Field 1 recebe a temperatura
  ThingSpeak.setField(1, temperatura);

  // Field 2 recebe a umidade
  ThingSpeak.setField(2, umidade);

  // Envia os dois Fields para o mesmo canal
  int x = ThingSpeak.writeFields(
    myChannelNumber,
    myWriteAPIKey
  );


  // ==============================
  // VERIFICA O ENVIO
  // ==============================

  if (x == 200) {
    Serial.println("Fields atualizados com sucesso.");
  } else {
    Serial.print("Problema ao atualizar os Fields. ");
    Serial.print("HTTP error code: ");
    Serial.println(x);
  }

  // Aguarda 15,1 segundos antes do próximo envio
  delay(15100);
}