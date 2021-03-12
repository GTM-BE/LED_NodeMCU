#include <ESP8266WiFi.h>
#include "network/webServer/WebServer.h"
#include "config.h"

IPAddress SlaveAddresses[2] = {IPAddress(192, 168, 200, 201), IPAddress(192, 168, 200, 202)};
IPAddress MasterAddress = IPAddress(192, 168, 178, 200);

#if SYSTEM == 0
#include "network/UDP/UdpServer.h"
UdpServer server;
#else
#include "network/UDP/UdpServer.h"
UdpClient client;
#endif

#if SYSTEM == 0
IPAddress local_IP = MasterAddress;
#elif SYSTEM == 1
IPAddress local_IP = SlaveAddresses[0];
#elif SYSTEM == 2
IPAddress local_IP = SlaveAddresses[1];
#endif

IPAddress gateway(192, 168, 200, 1);
IPAddress subnet(255, 255, 255, 0);

void setWifiConfig()
{
  // AP config
  if (WiFi.softAP(AP_SSID, AP_PASSWORD, 0, true))
  {
    Serial.printf("AP config\nSSID: %s\nPassword: %s\n", AP_SSID, AP_PASSWORD);
    Serial.println("---------------------------------------------------");
  }
  else
  {
    Serial.println("Failed to change AP config!");
  }

  // Connection settings
  if (WiFi.config(local_IP, gateway, subnet))
  {
    Serial.printf("Connection config\nLocalIP: %s\nGateway: %s\nSubnet: %s\n", local_IP.toString().c_str(), gateway.toString().c_str(), subnet.toString().c_str());
    Serial.println("---------------------------------------------------");
  }
  else
  {
    Serial.println("Failed to change connection settings");
  };
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
  setWifiConfig();
  Serial.printf("Connected to WiFi: \"%s\"\n", WIFI_SSID);
  Serial.printf("Device IP-address: \"%s\"\n", WiFi.localIP().toString().c_str());

// start UDP socket
#if SYSTEM == 0
  Serial.println("Start web server");
  initWebServer();
  //Serial.println("Start UDP server");
  //server.bind();
#else
  Serial.println("Start UDP Client");
  client.bind();
#endif
  Serial.println("---------------------------------------------------");
}
