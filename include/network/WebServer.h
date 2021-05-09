#ifndef WEB_SERVER_H_
#define WEB_SERVER_H_

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <map>

class WebServer
{
private:
  const String responseOkayJson = "{\nstatus: \"okay\"\n}";
  const String responseBadJson = "{\nstatus: \"bad\"\n}";
  const String API_VERSION = "v1";

public:
  void bind();
  void bind(int port);

private:
  void registerEndpoints(AsyncWebServer *website);
};

#endif

// test request
/*
  website.on("/update", HTTP_GET, [&](AsyncWebServerRequest *request) {
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
    else
    {
      int args = request->args();
      for (int i = 1; i < args; i++)
      {
      }
    }
    request->send_P(200, "text/text", "everything okay");
  });
*/
