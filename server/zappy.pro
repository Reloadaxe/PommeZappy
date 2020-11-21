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
    ./network/ClientThread.cpp \
    ./network/server_utils.cpp \
    ../commons/Item.cpp \
    ../commons/Deraumere.cpp \
    ../commons/Linemate.cpp \
    ../commons/Mendiane.cpp \
    ../commons/Sibur.cpp \
    ../commons/ItemFactory.cpp \
    Cell.cpp \
    Player.cpp \
    Map.cpp \
    game_commands.cpp \
    game_utils.cpp \
    parser_service.cpp \
    parser_utils.cpp \
    main.cpp

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
    ./network/ClientThread.h \
    ./network/server_utils.h \
    ../commons/Item.hh \
    ../commons/Deraumere.hh \
    ../commons/Linemate.hh \
    ../commons/Mendiane.hh \
    ../commons/Sibur.hh \
    Cell.hh \
    game_enums.hh \
    Player.hh \
    Map.hh \
    game_commands.h \
    game_utils.h \
    parser_service.h \
    main.h \
    parser_utils.h
