
#include "MovingAverage.h"

MovingAverage::MovingAverage(int frameSize) {
  this->frameSize = frameSize;
  this->total = 0;
}

short MovingAverage::getMovingAverage(short newValue) {
  total = total - frame[startLoc % frameSize] + newValue;
  frame[startLoc % frameSize] = newValue;
  startLoc++;
  return total / frameSize;
}

