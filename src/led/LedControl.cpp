#include <Arduino.h>
#include "config.h"
#include "led/worker.h"
#include <map>
#include "AsyncJson.h"
#include "ArduinoJson.h"

#include "led/worker/BlinkWorker.h"
#include "led/worker/FadeToWorker.h"

LedControl::LedControl() {}

void LedControl::playWorker(Worker *nextWorker)
{
  playWorker(nextWorker, false);
}

void LedControl::playWorker(Worker *nextWorker, bool skip)
{
  if (skip)
  {
    queue.clear();
    currentWorker = nextWorker;
  }
  else
  {
    queue.push_back(nextWorker);
  }
}

void LedControl::tick()
{
  if (currentWorker->status == WorkerStatus::FINISHED_WORKER)
  {
    currentWorker = queue.front() ? queue.front() : new Worker();
    queue.pop_front();
  }
  currentWorker->tick();
}

void LedControl::setColor(unsigned int red, unsigned int green, unsigned int blue)
{
  analogWrite(LED_RED, red % 1023);
  analogWrite(LED_GREEN, green % 1023);
  analogWrite(LED_BLUE, blue % 1023);
}

void LedControl::initLEDs()
{
  pinMode(LED_RED, OUTPUT);   //LED pin as output
  pinMode(LED_GREEN, OUTPUT); //LED pin as output
  pinMode(LED_BLUE, OUTPUT);  //LED pin as output
  setColor(LOW, LOW, LOW);
}

RGB::RGB(unsigned int _red, unsigned int _green, unsigned int _blue)
{
  red = _red;
  green = _green;
  blue = _blue;
};
