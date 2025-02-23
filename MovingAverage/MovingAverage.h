
#include "Arduino.h"

class MovingAverage {
  public:
    MovingAverage(int framesize);
    int16_t getMovingAverage(int16_t newValue);

  private:
    int16_t* frame;
    uint8_t* frameSize;
    uint8_t startLoc;
    int64_t total;
};
