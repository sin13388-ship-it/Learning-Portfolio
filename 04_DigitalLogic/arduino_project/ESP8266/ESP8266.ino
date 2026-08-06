#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "thmrb311";
const char* password = "thmrbthmrb";

// ===== MQTT 設定 =====
const char* mqtt_server = "192.168.63.66";
const int mqtt_port = 1883;
const char* mqtt_user = "cubie";
const char* mqtt_password = "1234";
const char* mqtt_topic = "dht22/311_01";

// ===== DHT 設定 =====
#define DHTPIN 4        // GPIO4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ===== WiFi + MQTT =====
WiFiClient espClient;
PubSubClient client(espClient);

// ===== 連接 WiFi =====
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());
}

// ===== MQTT 重新連線 =====
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("ESP8266Client40", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 讀取溫濕度
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // 建立 JSON 字串
  String payload = "{";
  payload += "\"temperature\":";
  payload += temp;
  payload += ",";
  payload += "\"humidity\":";
  payload += hum;
  payload += "}";

  // 發送 MQTT
  client.publish(mqtt_topic, payload.c_str());

  Serial.println("Publish:");
  Serial.println(payload);

  delay(5000); // 每5秒送一次

}
