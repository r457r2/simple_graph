#-------------------------------------------------
#
# Project created by QtCreator 2013-08-07T01:02:40
#
#-------------------------------------------------

QT       += core\
	    gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple_graph
TEMPLATE = app


SOURCES += main.cpp


HEADERS  += \
    VertexDescriptor.h \
    EdgeDescriptor.h \
    Graph.h \
    Representation.h \
    ListRepresentation.h \
    MatrixRepresentation.h
