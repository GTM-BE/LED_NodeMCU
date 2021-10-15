#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include "led/Worker.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "list"
#include "led/RGB.h"

class LedControl
{
private:
  std::list<Worker *> queue;
  Worker *currentWorker;
  RGB *currentColor = new RGB(0, 0, 0);

public:
  LedControl();
  static void initLEDs();
  static void setColor(unsigned int red, unsigned int green, unsigned int blue);
  static void setColor(RGB colors);
  static RGB *getColor();

  void playWorker(Worker *nextWorker);
  void addToQueue(Worker *nextWorker);
  int getQueueLength();
  void skipWorker();
  void stop();
  void clear();
  void tick();
};

#endif
