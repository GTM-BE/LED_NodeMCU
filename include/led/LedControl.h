#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include "led/Worker.h"
#include <map>

class RGB
{
public:
  unsigned int red;
  unsigned int green;
  unsigned int blue;
};

class LedControl
{
private:
  Worker currentWorker;

public:
  static void initLEDs();
  static void setColor(unsigned int red, unsigned int green, unsigned int blue);
  static void setColor(RGB colors);
  void playWorker(WorkerID id);
  void playWorker(WorkerID id, bool waitOnCurrentWorker);
  void playWorker(WorkerID id, std::map<uint8_t, String> data);
  void playWorker(WorkerID id, bool waitOnCurrentWorker, std::map<uint8_t, String> data);
  void tick();
};

#endif
