#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include "network/UDP/Socket.h"

class UdpServer : public Socket
{
private:
  unsigned int readOffset = 0;
  unsigned int writeOffset = 0;

public:
  void tick() override;
};

#endif
