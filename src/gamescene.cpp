#include "gamescene.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDir>
#include <QPainter>
#include <QMessageBox>
#include <QSqlQuery>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)),
      m_upDir(false), m_rightDir(false), m_downDir(false), m_leftDir(false), stop(false), start(false)
{
    loadPixmap();
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(m_timer, &QTimer::timeout, this, &GameScene::update);
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
    if(start && !stop){
        m_leftDir = newLeftDir;
    }
}

void GameScene::startTimer()
{
    start = false;
    stop = false;
    m_upDir = false;
    m_rightDir = false;
    m_downDir = false;
    m_leftDir = false;
    m_game.ready();
    schet = 0;
    update();
    schet = 0;
    m_timer->start(m_game.ITERATION_VALUE);
}

void GameScene::setDownDir(bool newDownDir)
{
    if(start && !stop){
        m_downDir = newDownDir;
    }
}

void GameScene::setRightDir(bool newRightDir)
{
    if(start && !stop){
        m_rightDir = newRightDir;
    }
}

void GameScene::setUpDir(bool newUpDir)
{
    if(start && !stop){
        m_upDir = newUpDir;
    }
}

void GameScene::carMovement()
{
    if (start){
        if(!stop){
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
        } else {
            m_game.car[0].speed = 0;
            m_game.car[0].angle = 0;
        }

        for(int i = 0; i < m_game.COUNT_OF_CARS; i++)
        {
            QPoint old(m_game.car[i].x, m_game.car[i].y);
            m_game.car[i].move();
            QPoint newPoint(m_game.car[i].x, m_game.car[i].y);
            if (Game::RECT.containsPoint(newPoint, Qt::WindingFill)){
                if (!Game::RECT.containsPoint(QPoint(old.x(), newPoint.y()), Qt::WindingFill)){
                    m_game.car[i].x = old.x();
                } else if (!Game::RECT.containsPoint(QPoint(newPoint.x(), old.y()), Qt::WindingFill)){
                    m_game.car[i].y = old.y();
                } else {
                    m_game.car[i].x = old.x();
                    m_game.car[i].y = old.y();
                }
            }
            newPoint = QPoint(m_game.car[i].x, m_game.car[i].y);
            if( !m_game.car[i].getFinishZone() && Game::RECT_FINISH.containsPoint(newPoint, Qt::WindingFill) ) {
                m_game.car[i].setFinishZone(true);
                if (old.y() > Game::RECT_FINISH.boundingRect().bottom()) {
                    m_game.car[i].setLaps(true);
                } else if (old.y() < Game::RECT_FINISH.boundingRect().top()){
                    m_game.car[i].setLaps(false);
                }
            } else if (m_game.car[i].getFinishZone() && !Game::RECT_FINISH.containsPoint(newPoint, Qt::WindingFill) ){
                m_game.car[i].setFinishZone(false);
                if (newPoint.y() < Game::RECT_FINISH.boundingRect().top()){
                    m_game.car[i].setLaps(true);
                } else if (newPoint.y() > Game::RECT_FINISH.boundingRect().bottom()) {
                    m_game.car[i].setLaps(false);
                }
            }
            if (m_game.car[i].getLaps() >= Game::COUNT_OF_LAPS) {
                m_game.stopGame(i);
                if (i == 0) {
                    stop = true;
                }
            }
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

//    QGraphicsPolygonItem* zaborItem = new QGraphicsPolygonItem(Game::RECT_FINISH);
//    zaborItem->setFillRule(Qt::WindingFill);
//    zaborItem->setPen(QPen(Qt::yellow));
//    zaborItem->setBrush(QBrush(Qt::yellow));
//    addItem(zaborItem);
//    zaborItem->setPos(-m_game.offsetX, -m_game.offsetY);

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

//        QGraphicsTextItem* schetItem = new QGraphicsTextItem();
//        schetItem->setTransformOriginPoint(21, 34);
//        QFont font = schetItem->font();
//        font.setPointSize(42);
//        font.setBold(true);
//        schetItem->setDefaultTextColor(Qt::magenta);
//        schetItem->setFont(font);
//        schetItem->setPos(m_game.car[i].x  - m_game.offsetX, m_game.car[i].y  - m_game.offsetY);
//        schetItem->setPlainText(tr("Laps: %1").arg(m_game.car[i].getLaps()));
//        addItem(schetItem);
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
    } else if (stop) {
        QVector<Car> vector;
        vector << m_game.car[0];
        bool first = true;
        for(int i=1; i < Game::COUNT_OF_CARS; i++)
        {
            for(int j=0; j < vector.size(); j++)
            {
                if (m_game.car[i].getStop().isValid() && m_game.car[i].getStop() <= vector[j].getStop()){
                    vector.append(m_game.car[i]);
                    first = false;
                    break;
                }
            }
        }

        QGraphicsTextItem* finishGame = new QGraphicsTextItem();
        finishGame->setTransformOriginPoint(21, 34);
        QFont font = finishGame->font();
        font.setPointSize(42);
        font.setBold(true);
        finishGame->setDefaultTextColor(Qt::yellow);
        finishGame->setFont(font);
        finishGame->setPos(m_game.car[0].x  - m_game.offsetX + 150, m_game.car[0].y  - m_game.offsetY - 100 );
        finishGame->setPlainText(first ? utr("Победа!!!") : utr("Проиграл :)"));
        addItem(finishGame);
        m_timer->stop();
        QSqlQuery query;
        for(int i = 0; i < vector.size(); i++ ) {
            Car car = vector[i];
            query.exec(utr("insert into person values('%1', %2, '%3')").arg(car.getName())
                       .arg(car.getStop().msecsSinceStartOfDay()).arg(car.getStop().toString("mm:ss:z")));
        }
        QMessageBox msgBox;
        msgBox.setWindowTitle(utr("Игра окончена"));
        msgBox.setText(utr("Хотите сыграть ещё?"));
//        msgBox.setInformativeText("Do you want to save your changes?");
        QPushButton *tableButton = msgBox.addButton(utr("Таблица лидеров"), QMessageBox::ActionRole);
        QPushButton *noButton = msgBox.addButton(utr("Нет"), QMessageBox::NoRole);
        QPushButton *yesButton = msgBox.addButton(utr("Да"), QMessageBox::YesRole);

        msgBox.exec();

        m_game.ready();

        if (msgBox.clickedButton() == (QAbstractButton*)yesButton) {
            m_game.ready();
            startTimer();
        } else if (msgBox.clickedButton() == (QAbstractButton*)noButton) {
            emit startWindow();
        } else {
            emit liderBoard();
        }

//        switch (QMessageBox::question(0, utr("Игра окончена"), utr("Хотите сыграть ещё?"), utr("Да"), utr("Нет"), utr("Таблица лидеров"), 1, 1)) {
//        case 0:
//            m_game.ready();
//            startTimer();
//            break;
//        case 2:
//            m_game.ready();
//            emit liderBoard();
//            break;
//        default:
//            m_game.ready();
//            emit startWindow();
//            break;
//        }
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (start && !stop) {
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
    if (start && !stop) {
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
