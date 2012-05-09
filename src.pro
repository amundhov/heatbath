TEMPLATE = app
CONFIG += console debug
CONFIG -= qt

QMAKE_CXXFLAGS += -g3

SOURCES += main.cpp \
    simulation.cpp

HEADERS += \
    simulation.h \
    parameters.h


LIBS += -lgsl -lgslcblas -lGL -lglut
