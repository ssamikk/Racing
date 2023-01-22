#ifndef GAME_H
#define GAME_H
#include "car.h"
#include <QPoint>
#include <QPolygon>
#include <QSize>
#include <QTime>

class Game
{
public:
    Game();
    void ready();
    void start();
    void stopGame(int carNumber);
    static const int num_checkpoints;
    static const int points[8][2];
    static const QSize RESOLUTION;

    const QString PATH_TO_BACKGROUND_PIXMAP;
    const QString PATH_TO_CAR_PIXMAP[5];
    const float ITERATION_VALUE;

    static const int COUNT_OF_CARS;
    static const int COUNT_OF_LAPS;
    static const QPolygon RECT;
    static const QPolygon RECT_FINISH;

    float car_R;

    Car car[5];

    float speed, angle;
    float maxSpeed;
    float acc, dec;
    float turnSpeed;

    int offsetX,offsetY;
protected:
    QTime startGame;
};

#endif // GAME_H
