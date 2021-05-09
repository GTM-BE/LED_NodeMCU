#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include "led/Worker.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "list"

class RGB
{
public:
  unsigned int red;
  unsigned int green;
  unsigned int blue;

public:
  RGB(unsigned int _red, unsigned int _green, unsigned int _blue);
};

class LedControl
{
private:
  Worker *currentWorker;
  std::list<Worker *> queue;

public:
  LedControl();
  static void initLEDs();
  static void setColor(unsigned int red, unsigned int green, unsigned int blue);
  static void setColor(RGB colors);

  void playWorker(Worker *nextWorker);
  void playWorker(Worker *nextWorker, bool skip);
  void tick();
};

#endif
