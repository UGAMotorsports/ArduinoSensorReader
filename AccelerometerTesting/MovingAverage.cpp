
const int averagingLength = 64; //should be a power of 2
int averagingArray[6][averagingLength];
int numberToReplace = 0;

void setNewAverage(int ax, int ay, int az, int gx, int gy, int gz) {
  averagingArray[0][numberToReplace] = ax;
  averagingArray[1][numberToReplace] = ay;
  averagingArray[2][numberToReplace] = az;
  averagingArray[3][numberToReplace] = gx;
  averagingArray[4][numberToReplace] = gy;
  averagingArray[5][numberToReplace] = gz;
  numberToReplace = (numberToReplace + 1) % averagingLength;
}

int returnAverage(int axisIndex) {
  int average = 0;
  for (int i = 0; i < averagingLength; i++) {
    average = average + averagingArray[axisIndex][i];
  }
  return average >> 6;
}

int averageAx() {
  return returnAverage(0);
}

int averageAy() {
  return returnAverage(1);
}

int averageAz() {
  return returnAverage(2);
}

int averageGx() {
  return returnAverage(3);
}

int averageGy() {
  return returnAverage(4);
}

int averageGz() {
  return returnAverage(5);
}

int getNumberToReplace() {
  return numberToReplace;
}

