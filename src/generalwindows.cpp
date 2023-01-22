#include "generalwindows.h"
#include "ui_generalwindows.h"

#include "gamescene.h"

#include <QtQuickWidgets/QtQuickWidgets>
#include <QDebug>
#include <QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

GeneralWindows::GeneralWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralWindows), m_gameScene(new GameScene(this))
{
    ui->setupUi(this);

    model = new QSqlQueryModel(this);
    model->setQuery("SELECT lastname, time_str FROM person order by time_lap");

    model->setHeaderData(0, Qt::Horizontal, utr("Участник"));
    model->setHeaderData(1, Qt::Horizontal, utr("Время"));

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(2);

    connect(ui->buttonBack, &QPushButton::clicked, this, &GeneralWindows::back_clicked);
    connect(ui->buttonBack2, &QPushButton::clicked, this, &GeneralWindows::back_clicked);
    connect(ui->buttonGame, &QPushButton::clicked, this, &GeneralWindows::game_clicked);
    connect(ui->buttonAbout, &QPushButton::clicked, this, &GeneralWindows::about_clicked);
    connect(ui->buttonLider, &QPushButton::clicked, this, &GeneralWindows::lider_clicked);

    back_clicked();

    ui->graphicsView->setScene(m_gameScene);
    connect(m_gameScene, &GameScene::startWindow, this, &GeneralWindows::back_clicked);
    connect(m_gameScene, &GameScene::liderBoard, this, &GeneralWindows::lider_clicked);
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

void GeneralWindows::lider_clicked()
{
    model->setQuery("SELECT lastname, time_str, time_lap FROM person order by time_lap");
    ui->tableView->hideColumn(2);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->stackedWidget->setCurrentIndex(3);
}

bool GeneralWindows::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("racingdatabase.data");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table person (lastname varchar(40), time_lap int, time_str varchar(20))");

    return true;
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

