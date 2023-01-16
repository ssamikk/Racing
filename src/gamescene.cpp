#include "gamescene.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDir>
#include <QPainter>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)),
      m_upDir(false), m_rightDir(false), m_downDir(false), m_leftDir(false)
{
    loadPixmap();
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
    start = false;
    schet = 0;
    update();
    schet = 0;
}

void GameScene::loadPixmap()
{
    if(m_bgPixmap.load(m_game.PATH_TO_BACKGROUND_PIXMAP))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }


    if(m_carPixmap[0].load(m_game.PATH_TO_CAR_PIXMAP[0]))
    {
        qDebug() << "CarPixmap[0] is loaded successfully";
    }
    else
    {
        qDebug() << "CarPixmap[0] is loaded successfully";
    }

    if(m_carPixmap[1].load(m_game.PATH_TO_CAR_PIXMAP[1]))
    {
        qDebug() << "CarPixmap[1] is loaded successfully";
    }
    else
    {
        qDebug() << "CarPixmap[1] is loaded successfully";
    }

    if(m_carPixmap[2].load(m_game.PATH_TO_CAR_PIXMAP[2]))
    {
        qDebug() << "CarPixmap[2] is loaded successfully";
    }
    else
    {
        qDebug() << "CarPixmap[2] is loaded successfully";
    }

    if(m_carPixmap[3].load(m_game.PATH_TO_CAR_PIXMAP[3]))
    {
        qDebug() << "CarPixmap[3] is loaded successfully";
    }
    else
    {
        qDebug() << "CarPixmap[3] is loaded successfully";
    }

    if(m_carPixmap[4].load(m_game.PATH_TO_CAR_PIXMAP[4]))
    {
        qDebug() << "CarPixmap[4] is loaded successfully";
    }
    else
    {
        qDebug() << "CarPixmap[4] is loaded successfully";
    }
}

void GameScene::setLeftDir(bool newLeftDir)
{
    m_leftDir = newLeftDir;
}

void GameScene::startTimer()
{
    m_timer->start(m_game.ITERATION_VALUE);
}

void GameScene::setDownDir(bool newDownDir)
{
    m_downDir = newDownDir;
}

void GameScene::setRightDir(bool newRightDir)
{
    m_rightDir = newRightDir;
}

void GameScene::setUpDir(bool newUpDir)
{
    m_upDir = newUpDir;
}

void GameScene::carMovement()
{
    if (start){
        if (m_upDir && m_game.speed < m_game.maxSpeed)
        {
            if (m_game.speed < 0)
            {
                m_game.speed += m_game.dec;
            }
            else
            {
                m_game.speed += m_game.acc;
            }
        }

        if (m_downDir && m_game.speed > -m_game.maxSpeed)
        {
            if (m_game.speed > 0)
            {
                m_game.speed -= m_game.dec;
            }
            else
            {
                m_game.speed -= m_game.acc;
            }
        }


        if (!m_upDir && !m_downDir)
        {
            if (m_game.speed - m_game.dec > 0)
            {
                m_game.speed -= m_game.dec;
            }
            else if (m_game.speed + m_game.dec < 0)
            {
                m_game.speed += m_game.dec;
            }
            else
            {
                m_game.speed = 0;
            }
        }


        if (m_rightDir && m_game.speed!=0)
        {
            m_game.angle += m_game.turnSpeed * m_game.speed/m_game.maxSpeed;
        }

        if (m_leftDir && m_game.speed!=0)
        {
            m_game.angle -= m_game.turnSpeed * m_game.speed/m_game.maxSpeed;
        }

        m_game.car[0].speed = m_game.speed;
        m_game.car[0].angle = m_game.angle;

        for(int i = 0; i < m_game.COUNT_OF_CARS; i++)
        {
            m_game.car[i].move();
        }

        for(int i=1; i < m_game.COUNT_OF_CARS ;i++)
        {
            m_game.car[i].findTarget();
        }
    }
}

void GameScene::carCollision()
{
    for(int i = 0; i < Game::COUNT_OF_CARS;i++)
    {
        if( m_game.car[i].x  < 50 ) {
            m_game.car[i].x = 50;
        } else if ( m_game.car[i].x > 2750 ) {
            m_game.car[i].x = 2750;
        }
        if (m_game.car[i].y < 250 ) {
            m_game.car[i].y = 250;
        } else if ( m_game.car[i].y > 3500 ) {
            m_game.car[i].y = 3500;
        }

        std::vector<Game::Point> rect = {Game::Point(500,500), Game::Point(500,3000),
                                         Game::Point(2250,3000), Game::Point(2250,500),
                                         Game::Point(500,500)};
        Game::Point point(m_game.car[i].x, m_game.car[i].x);
        if(i == 0){
            qDebug()<< "Game::pt_in_polygon2(point, rect)";
            qDebug()<< Game::pt_in_polygon2(point, rect);
            qDebug()<< Game::pt_in_polygon(point, rect);
        }
        for(int j=0; j<Game::COUNT_OF_CARS;j++)
        {
            int dx=0, dy=0;
            while (dx*dx + dy*dy < 4 * m_game.car_R * m_game.car_R)
            {
                m_game.car[i].x += dx/10.0;
                m_game.car[i].y += dy/10.0;
                m_game.car[j].x -= dx/10.0;
                m_game.car[j].y -= dy/10.0;
                dx = m_game.car[i].x - m_game.car[j].x;
                dy = m_game.car[i].y - m_game.car[j].y;
                if (!dx && !dy)
                {
                    break;
                }
            }
        }
    }
}



void GameScene::update()
{
    clear();
    setBackgroundBrush(QBrush(Qt::gray));
    QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem(m_bgPixmap);
    bgItem->setTransformationMode(Qt::SmoothTransformation);
    bgItem->setScale(2);
    addItem(bgItem);

    carMovement();
    carCollision();

    if (m_game.car[0].x > 320)
    {
        m_game.offsetX = m_game.car[0].x-320;
    }
    if ( m_game.car[0].y > 120)
    {
        m_game.offsetY = m_game.car[0].y-120;
    }
    bgItem->setPos(-m_game.offsetX, -m_game.offsetY);

    for(int i=0; i < Game::COUNT_OF_CARS; i++)
    {
        QGraphicsPixmapItem* carItem = new QGraphicsPixmapItem(m_carPixmap[i]);
        carItem->setTransformationMode(Qt::SmoothTransformation);
        carItem->setScale(1);
        //42x69 average of pixmaps
        carItem->setTransformOriginPoint(21, 34);
        carItem->setPos(m_game.car[i].x - m_game.offsetX, m_game.car[i].y - m_game.offsetY);
        carItem->setRotation(m_game.car[i].angle * 180/3.141593);
        addItem(carItem);
    }

    if (schet < 3000){
        schet += m_game.ITERATION_VALUE;
        QGraphicsTextItem* schetItem = new QGraphicsTextItem();
        schetItem->setTransformOriginPoint(21, 34);
        QFont font = schetItem->font();
        font.setPointSize(42);
        font.setBold(true);
        schetItem->setDefaultTextColor(Qt::magenta);
        schetItem->setFont(font);
        schetItem->setPos(m_game.car[0].x  - m_game.offsetX + 150, m_game.car[0].y  - m_game.offsetY - 100 );
        if (schet < 1000 ) {
            schetItem->setPlainText("3");
        } else if (schet < 2000) {
            schetItem->setPlainText("2");
        } else if (schet < 3000) {
            schetItem->setPlainText("1");
        }
        addItem(schetItem);
    } else if (!start){
        start = true;
        m_game.start();
        QGraphicsTextItem* schetItem = new QGraphicsTextItem();
        schetItem->setTransformOriginPoint(21, 34);
        QFont font = schetItem->font();
        font.setPointSize(42);
        font.setBold(true);
        schetItem->setDefaultTextColor(Qt::magenta);
        schetItem->setFont(font);
        schetItem->setPos(m_game.car[0].x  - m_game.offsetX + 150, m_game.car[0].y  - m_game.offsetY - 100 );
        schetItem->setPlainText("Go");
        addItem(schetItem);
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (start) {
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
        {
            m_upDir = true;
        }
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
        {
            m_rightDir = true;
        }
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
        {
            m_downDir = true;
        }
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
        {
            m_leftDir = true;
        }
            break;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if (start) {
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
        {
            m_upDir = false;
        }
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
        {
            m_rightDir = false;
        }
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
        {
            m_downDir = false;
        }
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
        {
            m_leftDir = false;
        }
            break;
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}
