#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "restauranttable.h"  //todomodel.h
#include "restaurantmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<RestaurantTableModel>("Restaurant",1,0,"RestaurantTableModel");
    qmlRegisterUncreatableType<RestaurantModel>("Restaurante",1,0, "RestaurantModel",
                                          QStringLiteral("RestaurantModel should not to be created in QML"));

    RestaurantModel restaurantModel;


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("restaurantModel"), &restaurantModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
