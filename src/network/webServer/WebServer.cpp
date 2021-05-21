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
    statusJson["maxMemory"] = 81920;
    statusJson["rst"] = system_get_rst_info();
    statusJson["adc"] = system_adc_read();
    statusJson["ip"] = WiFi.localIP().toString();

    system_get_os_print();

    String statusResponse;
    serializeJson(statusJson, statusResponse);
    request->send(200, "application/json", statusResponse);
  });

  website->on("/api/v1/worker/clear", HTTP_GET, [&](AsyncWebServerRequest *request) {
    led.clear();
    request->send(200, "application/json", responseOkayJson);
  });
  
  website->on("/api/v1/worker/stop", HTTP_GET, [&](AsyncWebServerRequest *request) {
    led.stop();
    request->send(200, "application/json", responseOkayJson);
  });
  
  /*---------- API for LED's ----------*/
  AsyncCallbackJsonWebHandler *workerBlinkHandler = new AsyncCallbackJsonWebHandler("/api/v1/worker/blink", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject data = json.as<JsonObject>();
    bool skip = data["skip"].as<bool>();
    unsigned int delay = data["delay"].as<unsigned int>();
    unsigned int red = data["red"].as<unsigned int>();
    unsigned int green = data["green"].as<unsigned int>();
    unsigned int blue = data["blue"].as<unsigned int>();

    if(skip) {
      led.playWorker(new BlinkWorker(delay, new RGB(red, green, blue)));
    } else {
      led.addToQueue(new BlinkWorker(delay, new RGB(red, green, blue)));
    }
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(workerBlinkHandler);

  AsyncCallbackJsonWebHandler *workerFadeToHandler = new AsyncCallbackJsonWebHandler("/api/v1/worker/fade_to", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject data = json.as<JsonObject>();
    bool skip = data["skip"].as<bool>();
    unsigned int step = data["step"].as<unsigned int>();
    unsigned int red = data["red"].as<unsigned int>();
    unsigned int green = data["green"].as<unsigned int>();
    unsigned int blue = data["blue"].as<unsigned int>();

    if(skip) {
      led.playWorker(new FadeToWorker(new RGB(red, green, blue), step));
    } else {
      led.addToQueue(new FadeToWorker(new RGB(red, green, blue), step));
    }
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(workerFadeToHandler);

  AsyncCallbackJsonWebHandler *workerSetColorHandler = new AsyncCallbackJsonWebHandler("/api/v1/worker/set_color", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject data = json.as<JsonObject>();
    bool skip = data["skip"].as<bool>();
    unsigned int red = data["red"].as<unsigned int>();
    unsigned int green = data["green"].as<unsigned int>();
    unsigned int blue = data["blue"].as<unsigned int>();

    if(skip) {
      led.playWorker(new SetColorWorker(new RGB(red, green, blue)));
    } else {
      led.addToQueue(new SetColorWorker(new RGB(red, green, blue)));
    }
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(workerSetColorHandler);
};
