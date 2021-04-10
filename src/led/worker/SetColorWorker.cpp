#include <Arduino.h>
#include "led/worker/SetColorWorker.h"
#include "led/LedControl.h"
#include "main.h"

SetColorWorker::SetColorWorker(RGB *color) : Worker(WorkerID::SET_COLOR_WORKER)
{
  led.setColor(color->red, color->green, color->blue);
  status = WorkerStatus::FINISHED_WORKER;
};

SetColorWorker::SetColorWorker(unsigned int red, unsigned int green, unsigned int blue) : Worker(WorkerID::SET_COLOR_WORKER)
{
  led.setColor(red, green, blue);
  status = WorkerStatus::FINISHED_WORKER;
};

void SetColorWorker::onTick(){};
