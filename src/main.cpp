#include <QApplication>
#include <QQmlApplicationEngine>

#include "generalwindows.h"
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "racing_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    /*QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/racing/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);*/

    GeneralWindows windows;
    windows.show();

    return app.exec();
}

//#include <QApplication>
//#include <QObject>
//#include <QDialog>
//#include <QVBoxLayout>
//#include <QtQuickWidgets/QQuickWidget>

///*****************************************************************************/

//void show (QUrl component) {
//    QDialog* dialog = new QDialog();
//    dialog->setStyleSheet("background-color: green;");
//    QObject::connect(
//        QCoreApplication::instance(),
//        SIGNAL(aboutToQuit()),
//        dialog,
//        SLOT(deleteLater())
//    );
//    /*QObject::connect(dialog,&QObject::destroyed,[](){
//       qDebug() << "destroyed";
//    });*/
//    QQuickWidget* content = new QQuickWidget(component, dialog);
//    content->setResizeMode(QQuickWidget::SizeRootObjectToView);
//    content->setAttribute(Qt::WA_AlwaysStackOnTop);
//    content->setClearColor(Qt::transparent);
//    dialog->show();
//}

///*****************************************************************************/

//int main(int argc, char *argv[]) {
//    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QApplication a(argc, argv);

//    show(QStringLiteral("qrc:/racing/src/button.qml"));
//    show(QStringLiteral("qrc:/racing/src/button.qml"));
//    show(QStringLiteral("qrc:/racing/src/button.qml"));
//    show(QStringLiteral("qrc:/racing/src/button.qml"));

//    return a.exec();
//}

