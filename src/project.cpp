#include "DHT.h"  // Biblioteca para o sensor DHT

// Definições para o DHT22
#define DHTPIN 15      // Pino de dados do DHT22
#define DHTTYPE DHT22  // Tipo do sensor DHT22

DHT dht(DHTPIN, DHTTYPE);  // Cria uma instância do sensor DHT

// Definições para o HC-SR04
#define TRIG_PIN 13  // Pino Trig do HC-SR04
#define ECHO_PIN 12  // Pino Echo do HC-SR04

// Definição para o PIR
#define PIR_PIN 14  // Pino de sinal do PIR

// Definição para o LDR
#define LDR_PIN 35  // Pino analógico do LDR (usando GPIO35)

void setup() {
  // Inicialização do monitor serial
  Serial.begin(115200);

  // Inicialização do sensor DHT
  dht.begin();

  // Configuração dos pinos do HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configuração do pino do PIR
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Leitura do sensor DHT22 (temperatura e umidade)
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler do sensor DHT!");
  } else {
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" °C");
  }

  // Leitura do sensor ultrassônico HC-SR04 (nível de água)
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leitura da duração do pulso
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Nível de água (distância): ");
  Serial.print(distance);
  Serial.println(" cm");

  // Leitura do sensor PIR (movimento)
  int movimento = digitalRead(PIR_PIN);
  if (movimento == HIGH) {
    Serial.println("Movimento detectado!");
  } else {
    Serial.println("Área segura.");
  }

  // Leitura do sensor LDR (intensidade de luz)
  int luz = analogRead(LDR_PIN);
  Serial.print("Intensidade da luz: ");
  Serial.println(luz);

  // Aguarda 2 segundos antes da próxima leitura para evitar sobrecarga
  delay(2000);
}
