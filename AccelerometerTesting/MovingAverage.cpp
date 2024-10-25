
#include "MovingAverage.h"
#include <Arduino.h>

MovingAverage::MovingAverage(int frameSize) {
  this->frameSize = frameSize;
  this->startLoc = 0;
  this->frame = calloc(frameSize, sizeof(int16_t));
  this->total = 0;
}

int16_t MovingAverage::getMovingAverage(int16_t newValue) {
  total = total - frame[startLoc] + newValue;
  frame[startLoc] = newValue;
  startLoc++;
  if (startLoc >= frameSize) {
    startLoc = 0;
  }
  return (total / (int64_t)frameSize);
}

