#include <Arduino.h>
#include "config.h"
#include "led/worker.h"
#include <map>

#include "led/worker/BlinkWorker.h"
#include "led/worker/FadeToWorker.h"

void LedControl::playWorker(WorkerID id)
{
  playWorker(id, false);
}

void LedControl::playWorker(WorkerID id, bool waitOnCurrentWorker)
{
  std::map<uint8_t, String> empty_map;
  playWorker(id, waitOnCurrentWorker, empty_map);
}

void LedControl::playWorker(WorkerID id, std::map<uint8_t, String> data)
{
  playWorker(id, false, data);
}

void LedControl::playWorker(WorkerID id, bool waitOnCurrentWorker, std::map<uint8_t, String> data) {}

void LedControl::tick()
{
  currentWorker.tick();
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
