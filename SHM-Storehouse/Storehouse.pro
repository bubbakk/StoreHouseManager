QT += core network

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Necessary to add web server/client
#PRJDIR       = ./3rdparty/qhttp
#include($$PRJDIR/commondir.pri)


SOURCES += \
        main.cpp \
    warehouse.cpp \
    warehousemajordomo.cpp \
    storeobject.cpp \
    objectcylinder.cpp \
    ../sharedcode/shmrequestparser.cpp \
    ../sharedcode/tcpchat.cpp \
    ../sharedcode/tcpServer.cpp \
    ../sharedcode/shmrequest.cpp \
    ../sharedcode/chat.cpp \
    ../sharedcode/webserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    warehouse.h \
    warehousemajordomo.h \
    storeobject.h \
    objectcylinder.h \
    ../sharedcode/shmrequestparser.h \
    ../sharedcode/tcpchat.h \
    ../sharedcode/tcpServer.h \
    ../sharedcode/shmrequest.h \
    ../sharedcode/chat.h \
    ../sharedcode/webserver.h

# Add qhttp libray
unix:!macx: LIBS += -L$$PWD/../third-party/qhttp/xbin/ -lqhttp
INCLUDEPATH += $$PWD/../third-party/qhttp/xbin
DEPENDPATH += $$PWD/../third-party/qhttp/xbin
