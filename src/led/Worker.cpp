#include <Arduino.h>
#include "led/Worker.h"

Worker::Worker(WorkerID workerID)
{
  id = workerID;
}

void Worker::tick()
{
  lastTick = millis();
  onTick();
}

void Worker::onTick()
{
  Serial.println("onTick Function not implemented");
}
