#include <Arduino.h>
#include "network/Connection.h"
#include <ESP8266HTTPClient.h>
#include "led/LedControl.h"
#include <IPAddress.h>
#include "main.h"

IPAddress master(192, 168, 178, 254);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(192, 168, 178, 254);
LedControl led = LedControl();

WiFiClient wifiClient;
HTTPClient httpClient;

#if SYSTEM != 0
unsigned long lastAK = millis();
#endif

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  Serial.write("\r\n");
#if SYSTEM == 0
  LedControl::setColor(0, 250, 0);
  Serial.println("Starting as Server");
#else
  LedControl::setColor(250, 0, 0);
  Serial.println("Starting as Client");
#endif
  connect();
}

void loop()
{
  /*---------- Loop for client aknowlage and led worker tick ----------*/
  //led.tick();
  delay(1);

#if SYSTEM != 0
  if (lastAK + 30000 < millis())
  {
    lastAK = millis();

    // Create json
    DynamicJsonDocument akJson(254);
    akJson["ip"] = WiFi.localIP().toString();

    // SerializeJson
    String data;
    serializeJson(akJson, data);
    Serial.println(data);

    // send data
    String URL = "http://" + master.toString() + "/api/v1/ak_slave";
    httpClient.begin(wifiClient, URL);
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.POST(data);
    httpClient.end();
  }
#endif
}
