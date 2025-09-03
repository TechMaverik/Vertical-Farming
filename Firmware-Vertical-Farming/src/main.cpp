#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

// Custom helpers (you mentioned these, assumed to exist in your project)
#include "displayMsgHelper.h"
#include "gasSensorHelper.h"
#include "dhtSensorHelper.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define MQ2_PIN 18
#define DHTPIN 19      
#define DHTTYPE DHT11
#define INDICATOR 13
#define RELAYPIN 5


// WiFi & MQTT credentials
const char* ssid = "Ai Lab";
const char* password = "Welc0me@123";
const char* mqtt_server = "broker.mqtt.cool";  
const int mqtt_port = 1883;
int timeCounter= 1;
bool relayStatus = false;

// MQTT Topics
const char* mqtt_temp_status  = "vertical_farming/temp";  
const char* mqtt_humid_status = "vertical_farming/humidity"; 
const char* mqtt_gas_status   = "vertical_farming/gas"; 
const char* mqtt_relay_status = "vertical_farming/relay"; 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void triggerRelay()
{
  Serial.println("Triggering Relay");
  digitalWrite(RELAYPIN,HIGH);
  delay(10000);
  digitalWrite(RELAYPIN,LOW);
  delay(100);
}

void setup() {
  dht.begin();
  Serial.begin(9600);
  Wire.begin(21, 22); // SDA=21, SCL=22  
  WiFi.begin(ssid, password);
  
  pinMode(MQ2_PIN, INPUT);
  pinMode(INDICATOR, OUTPUT);
  pinMode(RELAYPIN,OUTPUT);

  // WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(INDICATOR, LOW);
    delay(500);
    digitalWrite(INDICATOR, HIGH);
    Serial.print(".");
    delay(500);
  }
  digitalWrite(INDICATOR, LOW);
  Serial.println("\nWiFi connected");
  
  client.setServer(mqtt_server, mqtt_port);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("FarmNet");
  display.setCursor(0, 30);
  display.setTextSize(1);
  display.println("Built in AI & D&T Lab");
  display.setCursor(0, 50);
  display.setTextSize(1);
  display.println("DPS-Indirapuram 2025");
  display.display();
  delay(5000);
}

void loop() {
  if (!client.connected()) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Connecting..");
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println(ssid);   
    display.display(); 
    reconnect();
  }
  client.loop();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  bool state = detectedHydoCarbonPresence(MQ2_PIN);

  const char* hydrocarbon;
  
  
  Serial.println(timeCounter);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("FarmNet");
  display.display(); 
  
  if (state == true) {
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println("Hydrocarbon: Absent");
    display.display();
    hydrocarbon = "Absent";
  } else {
    display.setCursor(0, 25);
    display.setTextSize(1);
    display.println("Hydrocarbon: Present");
    display.display();
    hydrocarbon = "Present";
  }
  
  display.setCursor(0, 35);
  display.setTextSize(1);
  display.println("Temperature:");
  display.setCursor(72, 35);
  display.print(temperature);
  display.setCursor(110, 35);
  display.print("C ");
  display.display();

  display.setCursor(0, 45);
  display.setTextSize(1);
  display.println("Humidity:");
  display.setCursor(68, 45);
  display.print(humidity);
  display.setCursor(100, 45);
  display.print("%");
  display.display();  

  // ✅ Publish sensor data every 5 seconds
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    char tempMsg[50];
    snprintf(tempMsg, sizeof(tempMsg), "%.2f", temperature);
    client.publish(mqtt_temp_status, tempMsg);

    char humMsg[50];
    snprintf(humMsg, sizeof(humMsg), "%.2f", humidity);
    client.publish(mqtt_humid_status, humMsg);
    client.publish(mqtt_gas_status, hydrocarbon);   

    Serial.println("✅ Published all sensor data to MQTT.");
  }
  if (timeCounter%6==0)
  {
    relayStatus=true;   
    display.setCursor(0, 55);
    display.setTextSize(1);
    display.println("Pump:");
    display.setCursor(68, 55);
    display.print("ON");  
    display.display();
    client.publish(mqtt_relay_status, relayStatus ? "1" : "0");
    triggerRelay();
  }
  else{
    relayStatus = false;
    client.publish(mqtt_relay_status, relayStatus ? "1" : "0");
  }
  timeCounter++;
  delay(5000);
}
