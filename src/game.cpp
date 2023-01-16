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
const QSize Game::RESOLUTION = QSize(640, 300);
const int Game::COUNT_OF_CARS = 5;

Game::Game()
    : PATH_TO_BACKGROUND_PIXMAP(":/images/bg.png"),
      PATH_TO_CAR_PIXMAP{QString(":/images/car0.png"), QString(":/images/car1.png"), QString(":/images/car2.png"),
                         QString(":/images/car3.png"), QString(":/images/car4.png")},
      ITERATION_VALUE(1000.0f/60.0f),
      car_R(22), speed(0), angle(0), maxSpeed(12), acc(0.2f), dec(0.3f), turnSpeed(0.08), offsetX(0), offsetY(0)
{
    for(int i=0; i < COUNT_OF_CARS;i++)
    {
      car[i] = Car(num_checkpoints, points);
      car[i].x = 150+i*50;
      car[i].y = 3080+i;
      car[i].speed = 0;
    }
}

void Game::start()
{
    for(int i=0; i < COUNT_OF_CARS;i++)
    {
        car[i].speed = 7+i;
    }
}

bool Game::pt_in_polygon2(const Point &test, const std::vector<Point> &polygon)
{

    static const int q_patt[2][2]= { {0,1}, {3,2} };

    if (polygon.size()<3) {
        return false;
    }
    typename std::vector<Point>::const_iterator end=polygon.end();
    Point pred_pt=polygon.back();
    pred_pt.x-=test.x;
    pred_pt.y-=test.y;

    int pred_q=q_patt[pred_pt.y<0][pred_pt.x<0];

    int w=0;

    for(typename std::vector<Point>::const_iterator iter=polygon.begin();iter!=end;++iter)
    {
        Point cur_pt = *iter;

        cur_pt.x-=test.x;
        cur_pt.y-=test.y;

        int q=q_patt[cur_pt.y<0][cur_pt.x<0];

        switch (q-pred_q)
        {
        case -3:++w;break;
        case 3:--w;break;
        case -2:if(pred_pt.x*cur_pt.y>=pred_pt.y*cur_pt.x) ++w;break;
        case 2:if(!(pred_pt.x*cur_pt.y>=pred_pt.y*cur_pt.x)) --w;break;
        }

        pred_pt = cur_pt;
        pred_q = q;

    }

    return w!=0;

}

bool Game::pt_in_polygon(const Point &test, const std::vector<Point> &polygon)
{
    if (polygon.size()<3) return false;

    std::vector<Point>::const_iterator end=polygon.end();

    Point last_pt=polygon.back();

    last_pt.x-=test.x;
    last_pt.y-=test.y;

    double sum=0.0;

    for(
        std::vector<Point>::const_iterator iter=polygon.begin();
        iter!=end;
        ++iter
        )
    {
        Point cur_pt=*iter;
        cur_pt.x-=test.x;
        cur_pt.y-=test.y;

        double del= last_pt.x*cur_pt.y-cur_pt.x*last_pt.y;
        double xy= cur_pt.x*last_pt.x+cur_pt.y*last_pt.y;

        sum+=
                (
                    atan((last_pt.x*last_pt.x+last_pt.y*last_pt.y - xy)/del)+
                    atan((cur_pt.x*cur_pt.x+cur_pt.y*cur_pt.y- xy )/del)
                    );

        last_pt=cur_pt;

    }

    return fabs(sum)>0.00001;

}

Game::Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}
