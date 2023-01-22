#include "game.h"

const int Game::num_checkpoints = 8;
const int Game::points[8][2]=
{
    {240, 1470},
    {260, 400},
    {1420,450},
    {1550,1240},
    {2400,1470},
    {2380,3300},
    {1290, 3430},
    {240, 3180}
};
const QSize Game::RESOLUTION = QSize(760, 340);
const int Game::COUNT_OF_CARS = 5;
const int Game::COUNT_OF_LAPS = 3;
const QPolygon Game::RECT(QVector<QPoint>() << QPoint(500,550) << QPoint(1250, 550)
                          << QPoint(1250, 1550) <<
                          QPoint(2250,1550) << QPoint(2250,3200) <<
                          QPoint(500,3200) << QPoint(500,550));
const QPolygon Game::RECT_FINISH(QVector<QPoint>() << QPoint(0,2700) << QPoint(550, 2700) <<
                          QPoint(550,3000) << QPoint(0,3000));

Game::Game()
    : PATH_TO_BACKGROUND_PIXMAP(":/images/bg.png"),
      PATH_TO_CAR_PIXMAP{QString(":/images/car0.png"), QString(":/images/car1.png"), QString(":/images/car2.png"),
                         QString(":/images/car3.png"), QString(":/images/car4.png")},
      ITERATION_VALUE(1000.0f/60.0f),
      car_R(22), speed(0), angle(0), maxSpeed(12), acc(0.2f), dec(0.3f), turnSpeed(0.08), offsetX(0), offsetY(0)
{
    ready();
}

void Game::ready()
{
    for(int i=0; i < COUNT_OF_CARS;i++)
    {
      car[i] = Car(num_checkpoints, points);
      car[i].x = 150+i*50;
      car[i].y = 3080+i;
      car[i].speed = 0;
      switch (i) {
      case 0:
          car[i].setName(utr("Самойленко"));
          break;
      case 1:
          car[i].setName(utr("Иванов"));
          break;
      case 2:
          car[i].setName(utr("Петров"));
          break;
      case 3:
          car[i].setName(utr("Сименов"));
          break;
      case 4:
          car[i].setName(utr("Викторов"));
          break;
      default:
          car[i].setName(utr("Никодимов"));
          break;
      }
    }
}

void Game::start()
{
    startGame = QTime::currentTime();
    for(int i=0; i < COUNT_OF_CARS;i++)
    {
        car[i].speed = 7+i;
    }
}

void Game::stopGame( int carNumber )
{
    if (carNumber < 0 || carNumber >= car_R ){
        return;
    }
    car[carNumber].stopGame(startGame);
}
