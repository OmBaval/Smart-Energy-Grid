#include "WiFi.h"
#include <HTTPClient.h>
#include <ZMPT101B.h>

// WiFi credentials
const char* ssid = "Honey Patel";   // change SSID
const char* password = "21012005";  // change password
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "AKfycbyUmV2OvUUatUs3kpJ5TCZAUUnjWAJZXEM2XikMTY6ud-loCjGQ3S8lVC0dY55E4FCZ2w";  // change Gscript ID

#define SENSITIVITY 500.0f
// and the voltage source frequency is 50 Hz.
int vsensor = 35;
//const int ACPin = 33;
ZMPT101B voltageSensor(vsensor, 50.0);

float correctionfactor = 20;


#define VREF 3.3
char units[5];
unsigned long last_time = 0;
unsigned long current_time = 0;
float Wh = 0;
const int sensorIn = 34;  // pin where the OUT pin from sensor is connected on Arduino
int mVperAmp = 185;       // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("ACS712 current sensor");
  // pinMode(ACPin,INPUT);
  voltageSensor.setSensitivity(SENSITIVITY);

  // connect to WiFi
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

  

  float acvoltage = voltageSensor.getRmsVoltage();
  Serial.println("");
  Serial.println(acvoltage);
 
  Voltage = getVPP();
  VRMS = (Voltage / 2.0) * 0.707;              //root 2 is 0.707
  AmpsRMS = ((VRMS * 1000) / mVperAmp) - 0.3;  //0.3 is the error I got for my sensor

  Serial.println(AmpsRMS);
  Watt = (AmpsRMS * 240 / 1.2);

  Serial.println(Watt);

  float P = acvoltage * AmpsRMS;
  last_time = current_time;
  current_time = millis();
  Wh = Wh + P * ((current_time - last_time) / 3600000.0);
  
  String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "voltage=" + String(acvoltage) + "&current=" + String(AmpsRMS) + "&power=" + String(P)+ "&units=" + String(Wh);
 
  HTTPClient http;
  http.begin(urlFinal.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  
  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("Payload: " + payload);
  }
  //---------------------------------------------------------------------
  http.end();
  delay(1000);
}

float getVPP() {
  float result;
  int readValue;        // value read from the sensor
  int maxValue = 0;     // store max value here
  int minValue = 4096;  // store min value here ESP32 ADC resolution

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000)  //sample for 1 Sec
  {
    readValue = analogRead(sensorIn);
    // see if you have a new maxValue
    if (readValue > maxValue) {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue) {
      /*record the minimum sensor value*/
      minValue = readValue;
    }
  }

  // Subtract min from max
  result = ((maxValue - minValue) * 3.3) / 4096.0;  //ESP32 ADC resolution 4096

  return result;
}
