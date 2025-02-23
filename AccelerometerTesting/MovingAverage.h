
class MovingAverage {
  public:
    MovingAverage(int framesize, short** framePointer);
    short getMovingAverage(short newValue);

  private:
    short** frame;
    int frameSize;
    int startLoc;
    int total;
};
