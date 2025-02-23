
#include "MovingAverage.h"

MovingAverage::MovingAverage(int frameSize, short** framePointer) {
  this->frameSize = frameSize;
  this->frame = framePointer;
  this->total = 0;
}

short MovingAverage::getMovingAverage(short newValue) {
  total = total - (*frame)[startLoc % frameSize] + newValue;
  (*frame)[startLoc % frameSize] = newValue;
  startLoc++;
  return total / frameSize;
}

