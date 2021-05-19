#include <Arduino.h>
#include "network/Connection.h"
#include <ESP8266HTTPClient.h>
#include "led/LedControl.h"
#include <IPAddress.h>
#include "config.h"

IPAddress RasbpiAddress(192, 168, 178, 10);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(192, 168, 178, 254);

LedControl led = LedControl();
WiFiClient wifiClient;
HTTPClient httpClient;

unsigned long lastAK = 0;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);
  Serial.write("\r\n");

  LedControl::setColor(0, 250, 0);
  Serial.println("Starting as Server");
  connect();
}

void loop()
{
  /*---------- Loop for client aknowlage and led worker tick ----------*/
  //led.tick();
  delay(1);

  if (lastAK + 30000 < millis())
  {
    lastAK = millis();

    // Create json
    DynamicJsonDocument akJson(255);
    akJson["ip"] = WiFi.localIP().toString();

    // SerializeJson
    String data;
    serializeJson(akJson, data);
    Serial.println(data);

    // send data
    String URL = "http://" + RasbpiAddress.toString() + "/api/v1/ping";
    httpClient.begin(wifiClient, URL);
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.POST(data);
    httpClient.end();
  }
}
