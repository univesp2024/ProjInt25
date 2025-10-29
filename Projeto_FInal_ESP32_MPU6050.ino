#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <WebSocketsClient.h>

const char* ssid = "ssid_rede";
const char* password = "senha_rede";

const char* host = "ip_pc";  // IP do PC rodando o servidor
const uint16_t port = 5000;           // Porta do servidor WebSocket

Adafruit_MPU6050 mpu;
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.println("✅ WebSocket conectado!");
      break;
    case WStype_DISCONNECTED:
      Serial.println("⚠️ WebSocket desconectado!");
      break;
    case WStype_TEXT:
      Serial.printf("Mensagem recebida: %s\n", payload);
      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!mpu.begin()) {
    Serial.println("Erro ao iniciar MPU6050!");
    while (1);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  WiFi.begin(ssid, password);
  Serial.print("Conectando Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Wi-Fi conectado!");
  Serial.print("IP do ESP32: ");
  Serial.println(WiFi.localIP());

  webSocket.begin(host, port, "/ws");  // rota WebSocket do servidor Python
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Cria o JSON com os dados do acelerômetro
  String data = "{";
  data += "\"x\":" + String(a.acceleration.x, 2) + ",";
  data += "\"y\":" + String(a.acceleration.y, 2) + ",";
  data += "\"z\":" + String(a.acceleration.z, 2);
  data += "}";

  webSocket.sendTXT(data);
  Serial.println(data);

  delay(100);
}
