#include "network/WebServer.h"
#include "led/LedControl.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <string>
#include "config.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

#include "led/worker/SetColorWorker.h"
#include "led/worker/BlinkWorker.h"
#include "led/worker/FadeToWorker.h"

AsyncWebServer website(80);


void WebServer::bind()
{
  bind(80);
};

void WebServer::bind(int port)
{
  // Create AsyncWebServer
  registerEndpoints(&website);

  website.begin();
}

void WebServer::registerEndpoints(AsyncWebServer *website)
{
  /*---------- API endpoints ----------*/
  website->on("/api/v1/system_status", HTTP_GET, [&](AsyncWebServerRequest *request) {
    DynamicJsonDocument statusJson(254);
    statusJson["status"] = "okay";
    statusJson["memory"] = system_get_free_heap_size();
    statusJson["ip"] = WiFi.localIP().toString();

    String statusResponse;
    serializeJson(statusJson, statusResponse);
    request->send(200, "application/json", statusResponse);
  });

  AsyncCallbackJsonWebHandler *setColorHandler = new AsyncCallbackJsonWebHandler("/api/v1/set_color", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject data = json.as<JsonObject>();
    bool skip = data["skip"].as<bool>();
    unsigned int red = data["red"].as<unsigned int>();
    unsigned int green = data["green"].as<unsigned int>();
    unsigned int blue = data["blue"].as<unsigned int>();
    led.playWorker(new SetColorWorker(red, green, blue), skip);
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(setColorHandler);

  AsyncCallbackJsonWebHandler *blinkHandler = new AsyncCallbackJsonWebHandler("/api/v1/blink", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    request->send(200, "application/json", responseOkayJson);
    JsonObject data = json.as<JsonObject>();
    bool skip = data["skip"].as<bool>();
    unsigned int red = data["red"].as<unsigned int>();
    unsigned int green = data["green"].as<unsigned int>();
    unsigned int blue = data["blue"].as<unsigned int>();
    bool delay = data["delay"].as<bool>();
    led.playWorker(new BlinkWorker(delay, new RGB(red, green, blue)), skip);
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(blinkHandler);
};
