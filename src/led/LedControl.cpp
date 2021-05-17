#include <Arduino.h>
#include "config.h"
#include "led/worker.h"
#include <map>
#include "AsyncJson.h"
#include "ArduinoJson.h"
#include "led/worker/SetColorWorker.h"

LedControl::LedControl() {}

void LedControl::playWorker(Worker *nextWorker)
{
  this->queue.clear();
  this->queue.push_back(nextWorker);
}

void LedControl::addToQueue(Worker *nextWorker) {
  this->queue.push_back(nextWorker);
}

void LedControl::skipWorker() {
  this->currentWorker->status = WorkerStatus::FINISHED_WORKER;
}

void LedControl::stop() {
  this->queue.clear();
  this->currentWorker->status = WorkerStatus::FINISHED_WORKER;
}

void LedControl::clear() {
  this->queue.clear();
  this->playWorker(new SetColorWorker(new RGB(0,0,0)));
}

void LedControl::tick()
{
  if (currentWorker->status == WorkerStatus::FINISHED_WORKER)
  {
    if(queue.front()) {
      currentWorker = queue.front();
      queue.pop_front();
    }
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
