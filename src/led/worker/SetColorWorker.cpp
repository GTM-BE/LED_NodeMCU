#include <Arduino.h>
#include "led/worker/SetColorWorker.h"
#include "led/LedControl.h"
#include "config.h"
#include "led/RGB.h"

SetColorWorker::SetColorWorker(RGB *color) : Worker(WorkerID::SET_COLOR_WORKER)
{
  status = WorkerStatus::FINISHED_WORKER;
};

SetColorWorker::SetColorWorker(unsigned int red, unsigned int green, unsigned int blue) : Worker(WorkerID::SET_COLOR_WORKER)
{
  this->color = new RGB(red, green, blue);
  status = WorkerStatus::FINISHED_WORKER;
};

void SetColorWorker::onPrepare()
{
  led.setColor(color->red, color->green, color->blue);
  this->currentColor = new RGB(this->color->red, this->color->green, this->color->blue);
}

void SetColorWorker::onTick(){};
