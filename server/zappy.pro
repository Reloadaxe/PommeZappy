TARGET = server
QT += core widgets network

CONFIG += c++14 console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic -Werror

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
    ./network/Client.cpp \
    ./network/Server.cpp \
    ./network/server_utils.cpp \
    #../commons/Item.cpp \
    #Cell.cpp \
    #Map.cpp \
    #Player.cpp \
    game_utils.cpp \
    parser_service.cpp \
    parser_utils.cpp \
    server.cpp

INCLUDEPATH += \
    ./network \
    ../commons

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ./network/Client.h \
    ./network/Server.h \
    ./network/server_utils.h \
    #../commons/Item.hh \
    #Cell.hh \
    #Map.hh \
    #Player.hh \
    game_utils.h \
    parser_service.h \
    server.h \
    parser_utils.h
