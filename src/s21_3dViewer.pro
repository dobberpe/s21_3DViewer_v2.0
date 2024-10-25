QT += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/src/gifimage/qtgifimage.pri)

QMAKE_CFLAGS   += -Wall -Wextra -Werror -std=gnu11
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++17 -O0 -DGL_SILENCE_DEPRECATION

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += silent

SOURCES += \
    main_window/main_window.cpp \
    command/command.cpp \
    main.cpp \
    graphics/graphics.cpp \
    graphics/render_strategy.cpp \
    logger/logger.cpp

HEADERS += \
    main_window/main_window.hpp \
    command/command.hpp \
    graphics/graphics.hpp \
    graphics/render_strategy.hpp \
    controller/worker.hpp \
    controller/worker.tpp \
    figure/figure.hpp \
    figure/figure.tpp \
    parser/parser.hpp \
    parser/parser.tpp \
    logger/logger.hpp

# LIBS += -lGL -lGLU

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
