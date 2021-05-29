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
  std::list<Worker *> queue;
  Worker *currentWorker;

public:
  LedControl();
  static void initLEDs();
  static void setColor(unsigned int red, unsigned int green, unsigned int blue);
  static void setColor(RGB colors);
  static RGB * getColor();

  void playWorker(Worker *nextWorker);
  void addToQueue(Worker *nextWorker);
  void skipWorker();
  void stop();
  void clear();
  void tick();
};

#endif
