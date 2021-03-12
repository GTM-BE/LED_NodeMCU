#ifndef WORKER_H_
#define WORKER_H_

#include <map>

enum WorkerID
{
  INVALID_WORKER = 0x00,
  BLINK_WORKER = 0x01,
  FADE_TO_WORKER = 0x02
};

class Worker
{
public:
  WorkerID id;
  unsigned long lastTick = 0;

public:
  Worker(WorkerID workerID);
  void tick();
  virtual void onTick();
  virtual void dataFromMap(std::map<String, String>);
};

#endif
