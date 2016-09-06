#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>

#include "FilterTest.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FilterTest>("camera.filter.test", 1, 0, "FilterTest");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    QObject::connect(view.engine(),SIGNAL(quit()),qApp,SLOT(quit()));

    return app.exec();
}
