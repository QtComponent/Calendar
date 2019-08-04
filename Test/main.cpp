#include "../LunarCalendar.h"
#include <QApplication>

#ifdef COMPILER_MSVC
#define FROM_LOCAL_8BIT(content) QString::FROM_LOCAL_8BIT(content)
#elif COMPILER_MINGW
#define FROM_LOCAL_8BIT(content) QString(content)
#else
#define FROM_LOCAL_8BIT(content) QString(content)
#endif

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QDeclarativeView>
#else
#include <QQuickView>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<LunarCalendar>("LunarCalendar",
                                   1,
                                   0,
                                   "LunarCalendar");

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QDeclarativeView viewer;
#else
    QQuickView viewer;
#endif

    viewer.setTitle(APP_NAME + FROM_LOCAL_8BIT("(Qt君)"));
    viewer.setSource(QUrl::fromLocalFile(QLatin1String("../Calender.qml")));
    viewer.show();
    return app.exec();
}
