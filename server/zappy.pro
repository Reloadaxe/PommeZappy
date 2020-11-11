TARGET = server
QT -= core widgets

CONFIG += c++14 console
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic -Werror

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  \
            parser_service.cpp \
            parser_utils.cpp \
            server.cpp \
            server_net_utils.cpp

#INCLUDEPATH += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    parser_service.h \
    server.h \
    parser_utils.h \
    server_net_utils.h
