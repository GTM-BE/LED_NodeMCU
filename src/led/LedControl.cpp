#include <Arduino.h>
#include "config.h"
#include "led/worker.h"
#include <map>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "led/worker/SetColorWorker.h"
#include "led/RGB.h"

LedControl::LedControl()
{
  this->currentWorker = new Worker();
}

void LedControl::playWorker(Worker *nextWorker)
{
  this->queue.clear();
  this->queue.push_back(nextWorker);
}

void LedControl::addToQueue(Worker *nextWorker)
{
  this->queue.push_back(nextWorker);
}

int LedControl::getQueueLength()
{
  return this->queue.size();
}

void LedControl::skipWorker()
{
  this->currentWorker->status = WorkerStatus::FINISHED_WORKER;
}

void LedControl::stop()
{
  this->queue.clear();
  this->currentWorker->status = WorkerStatus::FINISHED_WORKER;
}

void LedControl::clear()
{
  this->queue.clear();
  this->playWorker(new SetColorWorker(new RGB(0, 0, 0)));
}

void LedControl::tick()
{
  if (currentWorker->status == WorkerStatus::FINISHED_WORKER)
  {
    Serial.printf("Queue size: %d\n", queue.size());
    if (queue.size() != 0)
    {
      this->currentColor = new RGB(currentWorker->currentColor->red, currentWorker->currentColor->green, currentWorker->currentColor->blue);
      currentWorker = queue.front();
      currentWorker->prepare(this->currentColor);
      queue.pop_front();
    }
  }
  else
  {
    currentWorker->tick();
  }
}

void LedControl::setColor(unsigned int red, unsigned int green, unsigned int blue)
{
  analogWrite(LED_RED, red % 1024);
  analogWrite(LED_GREEN, green % 1024);
  analogWrite(LED_BLUE, blue % 1024);
}

RGB *LedControl::getColor()
{
  return new RGB(analogRead(LED_RED), analogRead(LED_GREEN), analogRead(LED_BLUE));
}

void LedControl::initLEDs()
{
  pinMode(LED_RED, OUTPUT);   //LED pin as output
  pinMode(LED_GREEN, OUTPUT); //LED pin as output
  pinMode(LED_BLUE, OUTPUT);  //LED pin as output
  setColor(LOW, LOW, LOW);
}
