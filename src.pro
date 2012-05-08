TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    simulation.cpp

HEADERS += \
    simulation.h \
    parameters.h


LIBS += -lgsl -lgslcblas -lGL -lglut
