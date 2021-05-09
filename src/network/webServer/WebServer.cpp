#include "network/webServer/WebServer.h"
#include "led/LedControl.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <string>
#include "main.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

#include "led/worker/SetColorWorker.h"
#include "led/worker/BlinkWorker.h"
#include "led/worker/FadeToWorker.h"

AsyncWebServer website(80);

// Placeholder: <CONTENT>
char index_HTML[] = {
#include "network/webServer/html/index.html"
};

char not_found_HTML[] = {
#include "network/webServer/html/content/not_found.html"
};

char slider_HTML[] = {
#include "network/webServer/html/content/slider.html"
};

char buttons_HTML[] = {
#include "network/webServer/html/content/buttons.html"
};

char color_HTML[] = {
#include "network/webServer/html/content/color.html"
};

char test_HTML[] = {
#include "network/webServer/html/content/test.html"
};

void WebServer::bind()
{
  bind(80);
};

void WebServer::bind(int port)
{
  // Create AsyncWebServer
  website.onNotFound([&](AsyncWebServerRequest *request) {
    sendNotFound(request);
  });

  /*---------- Website routes ----------*/
  website.on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
    request->redirect("/slider");
  });

  website.on("/slider", HTTP_GET, [&](AsyncWebServerRequest *request) {
    sendHtml(request, slider_HTML);
  });

  website.on("/buttons", HTTP_GET, [&](AsyncWebServerRequest *request) {
    sendHtml(request, buttons_HTML);
  });

  website.on("/color", HTTP_GET, [&](AsyncWebServerRequest *request) {
    sendHtml(request, color_HTML);
  });

  website.on("/test", HTTP_GET, [&](AsyncWebServerRequest *request) {
    sendHtml(request, test_HTML);
  });

  registerEndpoints(&website);

  website.begin();
}

void WebServer::sendHtml(AsyncWebServerRequest *request, char *content, int code)
{
  String index_template(index_HTML);
  index_template.replace("<content>", content);
  index_template.replace("<value_red>", String(analogRead(LED_RED)));
  index_template.replace("<value_green>", String(analogRead(LED_GREEN)));
  index_template.replace("<value_blue>", String(analogRead(LED_BLUE)));
  index_template.replace("<master_ip>", master.toString());

  request->send(code, "text/html", index_template);
  return;
};

void WebServer::sendHtml(AsyncWebServerRequest *request, char *content)
{
  sendHtml(request, content, 200);
  return;
}

void WebServer::sendNotFound(AsyncWebServerRequest *request)
{
  sendHtml(request, not_found_HTML, 404);
  return;
}

void WebServer::registerEndpoints(AsyncWebServer *website)
{
  /*---------- API endpoints ----------*/
  // Shared
  website->on("/api/v1/system_status", HTTP_GET, [&](AsyncWebServerRequest *request) {
    DynamicJsonDocument statusJson(254);
    statusJson["status"] = "okay";
    statusJson["memory"] = system_get_free_heap_size();
    statusJson["ip"] = WiFi.localIP().toString();

    String statusResponse;
    serializeJson(statusJson, statusResponse);
    request->send(200, "application/json", statusResponse);
  });

  // Server
#if System == 0
  AsyncCallbackJsonWebHandler *broadcastHandler = new AsyncCallbackJsonWebHandler("/api/v1/broadcast", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject data = json.as<JsonObject>();
    Serial.println("GOT BROADCAST DATA");
    String endpoint = data["endpoint"].as<String>();
    data.remove("endpoint");
    JsonObject jsonData = data["data"].as<JsonObject>();
    String redirectData;
    serializeJson(jsonData, redirectData);
    Serial.println(redirectData);
    for (std::pair<const String, LedClient *> ledClient : clientMap)
    {
      String URL = "http://" + ledClient.first + endpoint;
      httpClient.begin(wifiClient, URL);
      httpClient.POST(redirectData);
      httpClient.addHeader("Content-Type", "application/json");
      httpClient.end();
      Serial.println(URL);
    }
    Serial.println("Finished sending!");
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(broadcastHandler);

  AsyncCallbackJsonWebHandler *akSlaveHandler = new AsyncCallbackJsonWebHandler("/api/v1/ak_slave", [&](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject data = json.as<JsonObject>();
    String deviceIP = data["ip"].as<String>();
    if (clientMap[deviceIP])
    {
      clientMap[deviceIP]->update();
    }
    else
    {
      clientMap[deviceIP] = new LedClient(deviceIP);
    }
    /*
    Serial.println("Device Found!!!");
    Serial.println(deviceIP);
    */
    request->send(200, "application/json", responseOkayJson);
  });
  website->addHandler(akSlaveHandler);
#endif

  // Client
#if System != 0
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
#endif
};
