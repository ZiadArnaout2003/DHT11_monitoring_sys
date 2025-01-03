#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>
#include <LiquidCrystal.h>
float tempC;
float tempF;
float humidity;
LiquidCrystal lcd(2,4,5,18,19,21);
const char *ssid = "VIRGIN063";
const char *password = "EE9C32D4";

WebServer server(80);
DHT dht(15, DHT11);
void handleData() {
  String json = "{";
  json += "\"temperature\":" + String(tempC, 1) + ",";
  json += "\"temperatureF\":" + String(tempF, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1);
  json += "}";

  server.sendHeader("Access-Control-Allow-Origin", "*"); // Allow all origins
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(200, "application/json", json);
}



void setup(void) {
  lcd.begin(16, 2); // Initialize LCD with 16 columns and 2 rows
  lcd.setCursor(0, 0); // Display initialization message
  lcd.print("Initializing...");
  delay(2000); // Wait for sensor and peripherals to stabilize
  lcd.clear(); // Clear the display for normal operation
  Serial.begin(115200);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/data", HTTP_GET, handleData);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
    humidity = readDHTHumidity();
    tempC = readDHTTemperature();
    tempF = readDHTTemperatureF();
    server.handleClient();
      lcd.setCursor(0, 0);
     lcd.print("Humidity: ");
      lcd.print(humidity, 1); // Print with 1 decimal place
      lcd.print("%          "); // Fill the rest with spaces to clear old text

      lcd.setCursor(0, 1);
      lcd.print("Temp:");
      lcd.print(tempC, 1); // Print Celsius with 1 decimal place
      lcd.print("C ");
      lcd.print(tempF, 1); // Print Celsius with 1 decimal place
      lcd.print("F ");
  delay(2);//allow the cpu to switch to other tasks
}


float readDHTTemperature() {
  // Sensor readings may also be up to 2 seconds
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    // Serial.println(t);
    return t;
  }
}
float readDHTTemperatureF() {
  // Sensor readings may also be up to 2 seconds
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature(true);
  if (isnan(t)) {    
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    // Serial.println(t);
    return t;
  }
}

float readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1;
  }
  else {
    // Serial.println(h);
    return h;
  }
}