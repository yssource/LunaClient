#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "luna/manager.h"
#include "model/settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_QUICK_CONTROLS_1_STYLE", "Flat");
    QGuiApplication app(argc, argv);

    //model::Settings settings;
    //settings.setLunaManager(worker.lunaManager());

    luna::Manager manager;
    manager.setMode(luna::ProviderType::audio);

    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("Luna", &settings);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    int ret = app.exec();

    return ret;
}
