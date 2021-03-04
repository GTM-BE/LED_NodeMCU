#ifndef CONNECTION_H
#define CONNECTION_H
#include "config.h"
#include "ESP8266WiFi.h"

extern IPAddress SlaveAddresses[2];
extern IPAddress MasterAddress;

void connect();
void setAPConfig();

/**
 * // Send Packet
 * Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
 * Udp.write(char*);
 * Udp.endPacket();
 */

#endif
