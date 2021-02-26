#ifndef CONNECTION_H
#define CONNECTION_H
#include "config.h"

void connect();
void setAPConfig();

/**
 * // Send Packet
 * Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
 * Udp.write(char*);
 * Udp.endPacket();
 */

#endif
