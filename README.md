# Monitoramento de Temperatura e Umidade com ESP32

Projeto de IoT desenvolvido utilizando uma ESP32 e um sensor DHT11 para realizar a leitura de temperatura e umidade e enviar os dados para a plataforma ThingSpeak por meio de uma conexão Wi-Fi.

## Tecnologias utilizadas

- ESP32
- Sensor DHT11
- Arduino IDE
- C++
- Wi-Fi
- ThingSpeak

## Funcionamento

O sensor DHT11 realiza a leitura da temperatura e da umidade.

A ESP32 recebe esses dados e utiliza uma conexão Wi-Fi para enviá-los para um canal na plataforma ThingSpeak.

No ThingSpeak, os dados são organizados da seguinte forma:

- Field 1: Temperatura
- Field 2: Umidade

## Conexões do sensor

| DHT11 | ESP32 |
|---|---|
| VCC | 3V3 |
| DATA | GPIO 4 |
| GND | GND |

## Etapas do projeto

### 1. Conexão Wi-Fi

Teste inicial para verificar a conexão da ESP32 com a rede Wi-Fi.

Código:
`01_conexao_wifi/conexao_wifi.ino`

### 2. Comunicação com o ThingSpeak

Teste do envio de dados da ESP32 para o ThingSpeak.

Código:
`02_conexao_thingspeak/conexao_thingspeak.ino`

### 3. Utilização de dois Fields

Teste do envio de dois valores para o mesmo canal do ThingSpeak.

Código:
`03_dois_fields/dois_fields.ino`

### 4. Projeto final

Integração da ESP32 com o sensor DHT11 e o ThingSpeak.

O sistema realiza a leitura da temperatura e da umidade e envia os valores para os Fields correspondentes.

Código:
`04_projeto_final/dht11_thingspeak.ino`

## Bibliotecas utilizadas

- WiFi
- ThingSpeak
- Adafruit Sensor
- DHT Sensor Library

## Resultado

O projeto permite realizar o monitoramento de temperatura e umidade utilizando a ESP32, com os dados enviados para a plataforma ThingSpeak para visualização.