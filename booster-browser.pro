TEMPLATE = app

TARGET = booster-browser
QT += qml quick concurrent
qml.files = qml/preload.qml

CONFIG += link_pkgconfig
QT += feedback dbus sql waylandclient
PKGCONFIG += mlite5 sailfishsilicabackground-qt5 gio-2.0 glib-2.0 gmodule-2.0 gobject-2.0

# Not common with silica booster.
PKGCONFIG += qt5embedwidget

CONFIG += qdeclarative-boostable

# We want booster to have all relocations resolved at startup so they do not turn into private dirty pages within boosted
# applications. This adds a little extra initial memory but saves a lot of pages per app.
QMAKE_LFLAGS += -Wl,-z,now

target.path = /usr/libexec/mapplauncherd/
qml.path = /usr/share/$${TARGET}/

service.path = /usr/lib/systemd/user/
service.files = data/$${TARGET}.service

INSTALLS += target qml service

LIBS += -lapplauncherd
INCLUDEPATH += /usr/include/applauncherd/

SOURCES += src/booster-browser.cpp src/eventhandler.cpp
HEADERS += src/booster-browser.h src/eventhandler.h
OTHER_FILES += qml/preload.qml

