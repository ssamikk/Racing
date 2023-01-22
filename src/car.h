#ifndef CAR_H
#define CAR_H

#include <QString>
#include <QTime>

#ifndef utr
# define utr QString::fromUtf8
#endif

struct Car
{
public:
  Car(int _num_checkpoints = 0, const int _points[8][2] = {});

  float x,y,speed,angle;
  int n;
  int num_checkpoints;
  int points[8][2];

  void move();

  void findTarget();

  bool getFinishZone() const;

  void setFinishZone(bool newFinishZone);

  int getLaps() const;
  void setLaps(bool newLaps);

  void stopGame(QTime start);

  QString getName() const;
  void setName(const QString &value);

  QTime getStop() const;

protected:
  int laps;
  bool finishZone;
  QTime stop;
  QString name;
};



#endif // CAR_H
