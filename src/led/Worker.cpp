#include <Arduino.h>
#include "led/Worker.h"
#include "AsyncJson.h"
#include "ArduinoJson.h"

Worker::Worker() {}

Worker::Worker(WorkerID workerID)
{
  id = workerID;
}

void Worker::tick()
{
  if (status == WorkerStatus::READY_WORKER)
  {
    status = WorkerStatus::RUNNING_WORKER;
  }
  lastTick = millis();
  onTick();
}

void Worker::onTick()
{
  //Serial.println("onTick Function not implemented");
}
