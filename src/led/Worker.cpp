#include <Arduino.h>
#include "led/LedControl.h"
#include "led/Worker.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

Worker::Worker()
{
}

Worker::Worker(WorkerID workerID)
{
  this->id = workerID;
}

void Worker::tick()
{
  if (status == WorkerStatus::READY_WORKER)
  {
    status = WorkerStatus::RUNNING_WORKER;
  }
  lastTick = millis();
  this->onTick();
}

void Worker::prepare(RGB *color)
{
  this->currentColor = color;
  this->onPrepare();
}

void Worker::onTick()
{
  this->status = WorkerStatus::FINISHED_WORKER;
  Serial.println("onTick Function not implemented");
}

void Worker::onPrepare()
{
  Serial.println("Prepare Function not implemented");
}
