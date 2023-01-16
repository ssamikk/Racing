#ifndef GAME_H
#define GAME_H
#include "car.h"
#include <QPoint>
#include <QSize>

class Game
{
public:
    Game();
    void start();
    static const int num_checkpoints;
    static const int points[8][2];
    static const QSize RESOLUTION;

    const QString PATH_TO_BACKGROUND_PIXMAP;
    const QString PATH_TO_CAR_PIXMAP[5];
    const float ITERATION_VALUE;

    static const int COUNT_OF_CARS;

    struct Point
    {
        Point(int x, int y);
        int x;
        int y;
    };

    static bool pt_in_polygon2(const Point &test, const std::vector<Point> &polygon);
    static bool pt_in_polygon(const Point &test,const std::vector<Point> &polygon);
    float car_R;

    Car car[5];

   float speed, angle;
   float maxSpeed;
   float acc, dec;
   float turnSpeed;

   int offsetX,offsetY;
};

#endif // GAME_H
