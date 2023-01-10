#ifndef GENERALWINDOWS_H
#define GENERALWINDOWS_H

#include <QWidget>
#include <QString>

#define utr QString::fromUtf8

class GameScene;
class QQuickWidget;
namespace Ui {
class GeneralWindows;
}

class GeneralWindows : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralWindows(QWidget *parent = nullptr);
    ~GeneralWindows();

private slots:
    void about_clicked();

    void back_clicked();

    void game_clicked();

    void resizeGameWidget();

    void redoPressed();

    void downPressed();

    void leftPressed();

    void rightPressed();

    void redoRelessed();

    void downRelessed();

    void leftRelessed();

    void rightRelessed();
private:
    Ui::GeneralWindows *ui;
    GameScene *m_gameScene;
    QQuickWidget *quickWidget;
};

#endif // GENERALWINDOWS_H
