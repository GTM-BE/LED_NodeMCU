#include <Arduino.h>
#include "network/Connection.h"
#include <ESP8266HTTPClient.h>
#include "led/LedControl.h"
#include "led/worker/FadeToWorker.h"
#include <IPAddress.h>
#include "config.h"
#include "led/RGB.h"

// IPAddress RasbpiAddress(192, 168, 178, 10);
IPAddress RasbpiAddress(192, 168, 178, 76);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(192, 168, 178, 254);

LedControl led = LedControl();
WiFiClient wifiClient;
HTTPClient httpClient;

unsigned long lastAK = 0;

void setup()
{
  // put your setup code here, to run once:
#if enableSerial == 1
  Serial.begin(BAUD_RATE);
  Serial.write("\r\n");
#endif

  LedControl::setColor(0, 0, 85);
  delay(250);
  LedControl::setColor(0, 85, 0);
  delay(250);
  LedControl::setColor(85, 0, 0);
  delay(250);
  LedControl::setColor(0, 0, 0);
  delay(1000);
  Serial.println("Starting...");

#if testMode == 0
  connect();
#endif
}

void loop()
{
  /*---------- Loop for client aknowlage and led worker tick ----------*/
  led.tick();
  delay(100);
#if testMode == 0
  if (lastAK + 3e4 < millis())
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
    String URL = "http://" + RasbpiAddress.toString() + ":8888/api/v1/mcu/ping";
    httpClient.begin(wifiClient, URL);
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.POST(data);
    httpClient.end();
  }
#else
  if (led.getQueueLength() == 0)
  {
    unsigned int step = 1;
    led.addToQueue(new FadeToWorker(new RGB(100, 0, 0), step));
    led.addToQueue(new FadeToWorker(new RGB(0, 0, 0), step));
    led.addToQueue(new FadeToWorker(new RGB(0, 100, 0), step));
    led.addToQueue(new FadeToWorker(new RGB(0, 0, 0), step));
    led.addToQueue(new FadeToWorker(new RGB(0, 0, 100), step));
    led.addToQueue(new FadeToWorker(new RGB(0, 0, 0), step));
  }
#endif
}
