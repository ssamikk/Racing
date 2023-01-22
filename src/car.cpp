#include "car.h"
#include "game.h"

Car::Car(int _num_checkpoints, const int _points[8][2])
    : speed(2), angle(0), n(0), laps(0), finishZone(false)
{
    num_checkpoints = _num_checkpoints;
    for(int i = 0; i < num_checkpoints; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            points[i][j] = _points[i][j];
        }
    }
}

void Car::move()
{
    x += sin(angle) * speed;
    y -= cos(angle) * speed;
}

void Car::findTarget()
{
    float tx= points[n][0];
    float ty= points[n][1];
    float beta = angle-atan2(tx-x,-ty+y);
    if (sin(beta)<0)
    {
        angle+=0.005*speed;
    }
    else
    {
        angle-=0.005*speed;
    }
    if ((x-tx)*(x-tx)+(y-ty)*(y-ty)<25*25)
    {
        n=(n+1) % num_checkpoints;
    }
}

bool Car::getFinishZone() const
{
    return finishZone;
}

void Car::setFinishZone(bool newFinishZone)
{
    finishZone = newFinishZone;
}

int Car::getLaps() const
{
    return laps;
}

void Car::setLaps(bool newLaps)
{
    if (newLaps){
        laps++;
    } else {
        laps--;
    }
    if (laps >= Game::COUNT_OF_LAPS) {
        speed = 0;
    }
}

void Car::stopGame(QTime start)
{
    if ( stop.isValid() ) {
        return;
    }
    stop = QTime::fromMSecsSinceStartOfDay(start.msecsTo(QTime::currentTime()));
}

QString Car::getName() const
{
    return name;
}

void Car::setName(const QString &value)
{
    name = value;
}

QTime Car::getStop() const
{
    return stop;
}
