
#include "MovingAverage.h"
#include "Arduino.h"

MovingAverage::MovingAverage(int frameSize) {
  this->frameSize = frameSize;
  this->frame = (short*)malloc(frameSize * sizeof(short));
  this->total = 0;
}

short MovingAverage::getMovingAverage(short newValue) {
  total = total - frame[startLoc % frameSize] + newValue;
  frame[startLoc % frameSize] = newValue;
  startLoc++;
  return total / frameSize;
}

