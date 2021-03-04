#include <ESP8266WiFi.h>
#include "config.h"

IPAddress SlaveAddresses[2] = {IPAddress(192, 168, 179, 201), IPAddress(192, 168, 179, 202)};
IPAddress MasterAddress = IPAddress(192, 168, 179, 200);

#if SYSTEM == 0
#include "UdpServer.h"
UdpServer server;
#else
#include "UdpClient.h"
UdpClient client;
#endif

#if SYSTEM == 0
IPAddress local_IP = MasterAddress;
#elif SYSTEM == 1
IPAddress local_IP = SlaveAddresses[1];
#elif SYSTEM == 2
IPAddress local_IP = SlaveAddresses[2];
#endif

IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);

void setWifiConfig()
{
  // AP config
  WiFi.softAP(AP_SSID, AP_PASSWORD, 1, true, 1);

  // Connection settings
  WiFi.config(local_IP, gateway, subnet);
}

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
  Serial.println("Changeing network config");
  setWifiConfig();
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

  Serial.printf("Connected to WiFi: \"%s\"\n", WIFI_SSID);
  Serial.printf("Device IP-address: \"%s\"\n", WiFi.localIP().toString().c_str());
  Serial.println("Start UDP socket");

// start UDP socket
#if SYSTEM == 0
  server.bind();
#else
  client.bind();
#endif
}
