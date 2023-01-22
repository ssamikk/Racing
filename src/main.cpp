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

    if (!GeneralWindows::createConnection()){
        return -5;
    }

    GeneralWindows windows;

    windows.show();

    return app.exec();
}
