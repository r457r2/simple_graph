#-------------------------------------------------
#
# Project created by QtCreator 2013-08-07T01:02:40
#
#-------------------------------------------------

QT       += core
QT	 -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple_graph

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    graphtest.cpp \
    spanningtreebuilder.cpp


HEADERS  += \
    VertexDescriptor.h \
    EdgeDescriptor.h \
    Graph.h \
    Representation.h \
    ListRepresentation.h \
    MatrixRepresentation.h \
    graphtest.h \
    TaskOne.h \
    TaskTwo.h \
    spanningtreebuilder.h
