#include "network/webServer/WebServer.h"
#include "led/LedControl.h"
#include "config.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <string>

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

void sendHtml(AsyncWebServerRequest *request, char *content, int code)
{
  String index_template(index_HTML);
  index_template.replace("<content>", content);
  index_template.replace("<value_red>", String(analogRead(LED_RED)));
  index_template.replace("<value_green>", String(analogRead(LED_GREEN)));
  index_template.replace("<value_blue>", String(analogRead(LED_BLUE)));

  request->send_P(code, "text/html", index_template.c_str());
  return;
};

void sendHtml(AsyncWebServerRequest *request, char *content)
{
  sendHtml(request, content, 200);
  return;
}

void sendNotFound(AsyncWebServerRequest *request)
{
  sendHtml(request, not_found_HTML, 404);
  return;
}

void initWebServer(int port)
{
  // Create AsyncWebServer object on port 80
  AsyncWebServer website(80);

  website.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    uint32_t free = system_get_free_heap_size();
    Serial.printf("%d\n", free);
    sendHtml(request, slider_HTML);
  });

  website.onNotFound(sendNotFound);

  website.on("/slider", HTTP_GET, [](AsyncWebServerRequest *request) {
    sendHtml(request, slider_HTML);
  });

  website.on("/buttons", HTTP_GET, [](AsyncWebServerRequest *request) {
    sendHtml(request, buttons_HTML);
  });

  website.on("/color", HTTP_GET, [](AsyncWebServerRequest *request) {
    sendHtml(request, color_HTML);
  });

  website.on("/test", HTTP_GET, [](AsyncWebServerRequest *request) {
    sendHtml(request, test_HTML);
  });

  website.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("worker"))
    {
      AsyncWebParameter *workerStr = request->getParam("worker");
      unsigned int id;
      std::stringstream ssW(workerStr->value().c_str());
      ssW >> id;

      std::map<uint8_t, String> data;
      int args = request->args();

      // LedControl::playWorker((WorkerID)id, request->hasParam("skip"));
    }
    /*
    else if (request->hasParam("red") && request->hasParam("green") && request->hasParam("blue"))
    {
      AsyncWebParameter *channelRED = request->getParam("red");
      AsyncWebParameter *channelGREEN = request->getParam("green");
      AsyncWebParameter *channelBLUE = request->getParam("blue");

      unsigned int red, green, blue;
      std::stringstream ssR(channelRED->value().c_str());
      ssR >> red;
      std::stringstream ssG(channelGREEN->value().c_str());
      ssG >> green;
      std::stringstream ssB(channelBLUE->value().c_str());
      ssB >> blue;
      LedControl::setColor(red, green, blue);
    }
    */
    else
    {
      int args = request->args();
      for (int i = 1; i < args; i++)
      {
      }
    }
    request->send_P(200, "text/text", "everything okay");
  });

  website.begin();
}

void initWebServer()
{
  initWebServer(80);
};
