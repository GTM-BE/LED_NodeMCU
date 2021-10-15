#ifndef SET_COLOR_WORKER_H_
#define SET_COLOR_WORKER_H_

#include "led/Worker.h"
#include "led/LedControl.h"
#include "led/RGB.h"

class SetColorWorker : public Worker
{
public:
    SetColorWorker(RGB *color);
    SetColorWorker(unsigned int red, unsigned int green, unsigned int blue);
    void onTick() override;
    void onPrepare() override;

private:
    RGB *color;
};

#endif
