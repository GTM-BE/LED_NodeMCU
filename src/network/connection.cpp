#include <ESP8266WiFi.h>
#include "config.h"

#if IS_CLIENT == true
#include "UdpClient.h"
UdpClient client;
#else
#include "UdpServer.h"
UdpServer server;
#endif

void getAvailabeNetworks()
{
  int networkIndex = WiFi.scanNetworks();
  if (networkIndex > 0)
  {
    for (int i = 0; i < networkIndex; i++)
    {
      Serial.println(WiFi.SSID(i));
    }
  }
  else
  {
    Serial.println("Nothing found!");
  }
}

void connect()
{
  Serial.println("Changeing AP config");
  Serial.printf("Connecting to %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  bool idleConnection = true;
  while (idleConnection)
  {
    Serial.printf(".");
    switch (WiFi.status())
    {
    case WL_NO_SHIELD:
      exit(0);
      break;
    case WL_IDLE_STATUS:
      break;
    case WL_NO_SSID_AVAIL:
      idleConnection = false;
      Serial.println("No SSID available");
      exit(1);
      break;
    case WL_SCAN_COMPLETED:
      idleConnection = false;
      Serial.println("Invalid scan detected while connecting!");
      exit(1);
      break;
    case WL_CONNECTED:
      idleConnection = false;
      Serial.println("Connected to network!");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("Connection failed!");
      exit(1);
      break;
    case WL_CONNECTION_LOST:
      Serial.println("Connection lost, while connecting!");
      exit(1);
      break;
    case WL_DISCONNECTED:
      break;
    default:
      break;
    }
    delay(1000);
  }

  Serial.printf("Connected to WiFi \"%s\"\n", WIFI_SSID);
  Serial.println("Start UDP socket");
  // start UDP socket
#if IS_CLIENT == true
  client.bind();
#else
  server.bind()
#endif
}
