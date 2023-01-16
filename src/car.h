#ifndef CAR_H
#define CAR_H
#include <cmath>
struct Car
{
  float x,y,speed,angle; int n;
  int num_checkpoints;
  int points[8][2];
public:
  Car(int _num_checkpoints = 0, const int _points[8][2] = {});

  void move();

  void findTarget();

  bool getFinishZone() const;

  void setFinishZone(bool newFinishZone);

  int getLaps() const;
  void setLaps(bool newLaps);

protected:
  int laps;
  bool finishZone;
};



#endif // CAR_H
