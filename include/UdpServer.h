#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include "Socket.h"

class UdpServer : public Socket
{
public:
  void tick() override;
};

#endif
