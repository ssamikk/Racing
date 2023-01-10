#ifndef CAR_H
#define CAR_H
#include <cmath>
struct Car
{
  float x,y,speed,angle; int n;
  int num_checkpoints;
  int points[8][2];

  Car(int _num_checkpoints = 0, const int _points[8][2] = {});

  void move();

  void findTarget();
};



#endif // CAR_H
