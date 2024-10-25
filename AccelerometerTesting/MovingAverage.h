
class MovingAverage {
  public:
    MovingAverage(int framesize);
    short getMovingAverage(short newValue);

  private:
    short* frame;
    int frameSize;
    int startLoc;
    int total;
};
