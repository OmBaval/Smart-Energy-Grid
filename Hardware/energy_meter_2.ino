#include "WiFi.h"
#include <HTTPClient.h>
#include <ZMPT101B.h>

#define SENSITIVITY 500.0f
#define ACTectionRange 20;
#define VREF 3.3

const char* ssid = "Honey Patel";
const char* password = "21012005";

String GOOGLE_SCRIPT_ID = "AKfycbw5H-cp3a6rKOr9Ly9RyHYhxkpRTJk7kvLGufwxiLSyPkKG-ujGlNzL4gI2cknUezwL";

int vsensor = 35;
const int ACPin = 34;
ZMPT101B voltageSensor(vsensor, 50.0);

float correctionfactor = 20;
float Current_Value = 0;

char units[5];
unsigned long last_time = 0;
unsigned long current_time = 0;
float Wh = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ACPin, INPUT);
  voltageSensor.setSensitivity(SENSITIVITY);
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  char units;

  float ACcurrent = 0;
  float current_value = readACCurrentValue();
  ACcurrent = current_value;

  delay(1000);
  
  Serial.print("Current: ");
  Serial.println(ACcurrent);
  

  float acvoltage = voltageSensor.getRmsVoltage();
  Serial.print("Voltage: ");
  Serial.println(acvoltage);

  float P = acvoltage * ACcurrent;
  Serial.print("Power: ");
  Serial.println(P);

  last_time = current_time;
  current_time = millis();
  Wh = Wh + P * ((current_time - last_time) / 3600000.0);
  Serial.print("Units: ");
  Serial.println(Wh);

  String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "voltage=" + String(acvoltage) + "&current=" + String(ACcurrent) + "&power=" + String(P) + "&units=" + String(Wh);
  HTTPClient http;
  http.begin(urlFinal.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();

  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("Payload: " + payload);
  }
  http.end();
  delay(1000);
}

float readACCurrentValue() {
  float ACCurrentValue = 0;
  float peakVoltage = 0;
  float voltageVirtualValue = 0; 
  for (int i = 0; i < 5; i++) {
    peakVoltage += analogRead(ACPin); 
    peakVoltage = peakVoltage + correctionfactor;
    delay(1);
  }
  peakVoltage = peakVoltage / 5;
  voltageVirtualValue = peakVoltage * 0.707;

  voltageVirtualValue = (voltageVirtualValue / 4095 * VREF) / 2;
  ACCurrentValue = voltageVirtualValue * ACTectionRange;
  return ACCurrentValue;
}
