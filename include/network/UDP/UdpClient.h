#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include "network/UDP/Socket.h"
#include "led/LedControl.h"

class UdpClient : public Socket
{
public:
  LedControl ledController;

private:
  unsigned int offset;

public:
  void tick() override;
};

#endif
