#include "generalwindows.h"
#include "ui_generalwindows.h"

#include "gamescene.h"

#include <QtQuickWidgets/QtQuickWidgets>
#include <QDebug>

GeneralWindows::GeneralWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralWindows), m_gameScene(new GameScene(this))
{
    ui->setupUi(this);

    connect(ui->buttonBack, &QPushButton::clicked, this, &GeneralWindows::back_clicked);
    connect(ui->buttonBack2, &QPushButton::clicked, this, &GeneralWindows::back_clicked);
    connect(ui->buttonGame, &QPushButton::clicked, this, &GeneralWindows::game_clicked);
    connect(ui->buttonAbout, &QPushButton::clicked, this, &GeneralWindows::about_clicked);
    connect(ui->buttonLider, &QPushButton::clicked, this, &GeneralWindows::liderClicked);

    back_clicked();

    ui->graphicsView->setScene(m_gameScene);
    connect(m_gameScene, &GameScene::startWindow, this, &GeneralWindows::back_clicked);
    connect(m_gameScene, &GameScene::liderBoard, this, &GeneralWindows::liderClicked);
    resize(m_gameScene->sceneRect().width()+2, m_gameScene->sceneRect().height()+2);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    quickWidget = new QQuickWidget(QUrl("qrc:/racing/src/main.qml") , ui->graphicsView);
    if (!quickWidget->errors().isEmpty()){
        QMessageBox::critical(this, utr("Не верная загрузка QML"), utr("Ошибки: %1").arg(quickWidget->errors().size()));
    }
    quickWidget->setAttribute(Qt::WA_TranslucentBackground);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    quickWidget->setAttribute(Qt::WA_AlwaysStackOnTop);
    quickWidget->setClearColor(Qt::transparent);
    quickWidget->setAttribute(Qt::WA_AcceptTouchEvents);
//    resizeGameWidget();

    QQuickItem* pqiRoot = quickWidget->rootObject();
    if(pqiRoot) {
        QObject* pObjButton = pqiRoot->findChild<QObject*>("buttonRedo");
        if (pObjButton) {
            connect(pObjButton, SIGNAL(pressedMy()), this, SLOT(redoPressed()));
            connect(pObjButton, SIGNAL(relessedMy()), this, SLOT(redoRelessed()));
        } else {
            qDebug()<<"no redo";
        }
        pObjButton = pqiRoot->findChild<QObject*>("buttonBeck");
        if (pObjButton) {
            connect(pObjButton, SIGNAL(pressedMy()), this, SLOT(downPressed()));
            connect(pObjButton, SIGNAL(relessedMy()), this, SLOT(downRelessed()));
        } else {
            qDebug()<<"no beck";
        }
        pObjButton = pqiRoot->findChild<QObject*>("buttonLeft");
        if (pObjButton) {
            connect(pObjButton, SIGNAL(pressedMy()), this, SLOT(leftPressed()));
            connect(pObjButton, SIGNAL(relessedMy()), this, SLOT(leftRelessed()));
        } else {
            qDebug()<<"no left";
        }
        pObjButton = pqiRoot->findChild<QObject*>("buttonRight");
        if (pObjButton) {
            connect(pObjButton, SIGNAL(pressedMy()), this, SLOT(rightPressed()));
            connect(pObjButton, SIGNAL(relessedMy()), this, SLOT(rightRelessed()));
        } else {
            qDebug()<<"no right";
        }
    }
}

GeneralWindows::~GeneralWindows()
{
    delete ui;
}

void GeneralWindows::about_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void GeneralWindows::back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void GeneralWindows::game_clicked()
{
    m_gameScene->startTimer();
    ui->stackedWidget->setCurrentIndex(0);
}

void GeneralWindows::resizeGameWidget()
{
    QQuickItem* pqiRoot = quickWidget->rootObject();
    if(pqiRoot) {
        pqiRoot->setProperty ( "height", ui->graphicsView->viewport()->height());
        pqiRoot->setProperty ( "width", ui->graphicsView->viewport()->width());
    }
}

void GeneralWindows::rightPressed()
{
    m_gameScene->setRightDir(true);
}

void GeneralWindows::redoRelessed()
{
    m_gameScene->setUpDir(false);
}

void GeneralWindows::downRelessed()
{
    m_gameScene->setDownDir(false);
}

void GeneralWindows::leftRelessed()
{
    m_gameScene->setLeftDir(false);
}

void GeneralWindows::rightRelessed()
{
    m_gameScene->setRightDir(false);
}

void GeneralWindows::liderClicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void GeneralWindows::leftPressed()
{
    m_gameScene->setLeftDir(true);
}

void GeneralWindows::downPressed()
{
    m_gameScene->setDownDir(true);
}

void GeneralWindows::redoPressed()
{
    m_gameScene->setUpDir(true);
}

