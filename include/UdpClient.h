#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include "Socket.h"

class UdpClient : public Socket
{
public:
  void tick() override;
};

#endif
