QT += core

TARGET = Calendar
DEFINES += APP_NAME=\\\"'$$TARGET'\\\"

equals (QT_MAJOR_VERSION, 4): QT += declarative
equals (QT_MAJOR_VERSION, 5): QT += qml quick quickwidgets

RC_ICONS = app.ico

HEADERS += ../LunarCalendar.h
SOURCES += main.cpp ../LunarCalendar.cpp

DISTFILES += ../Calender.qml

equals(QT_MAJOR_VERSION, 4) {
    equals(QT_MINOR_VERSION, 7): QT_QUICK_VERSION = 1.0
    equals(QT_MINOR_VERSION, 8): QT_QUICK_VERSION = 1.1
}

equals(QT_MAJOR_VERSION, 5): QT_QUICK_VERSION = 2.$${QT_MINOR_VERSION}

macx {
    !isEmpty(QT_QUICK_VERSION): QtQuickVersion.commands += "grep -rl 'QtQuick [0-9]\\.[0-9]' $$PWD/ | xargs sed -i '' 's/QtQuick [0-9]\\.[0-9]/QtQuick $${QT_QUICK_VERSION}/g';"
}

unix:!macx {
    !isEmpty(QT_QUICK_VERSION): QtQuickVersion.commands += "grep -rl 'QtQuick [0-9]\\.[0-9]' $$PWD/ | xargs sed -i 's/QtQuick [0-9]\\.[0-9]/QtQuick $${QT_QUICK_VERSION}/g';"
}

QtQuickVersion.target = FORCE

PRE_TARGETDEPS += FORCE
QMAKE_EXTRA_TARGETS += QtQuickVersion

msvc {
    DEFINES += COMPILER_MSVC
}

mingw {
    DEFINES += COMPILER_MINGW
}
