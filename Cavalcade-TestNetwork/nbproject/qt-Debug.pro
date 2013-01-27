# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = Cavalcade-TestNetwork
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui
SOURCES += main.cpp GLEngine.cpp CNNControl.cpp
HEADERS += globals.h CNNControl.h GLEngine.h
FORMS += CNNControl.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += CMarkup 
LIBS += -lpthread  -lX11 -lglut -lGL -lGLU -lm  -Wl,-rpath,../CavalCade/dist/Debug/GNU-Linux-x86 ../CavalCade/dist/Debug/GNU-Linux-x86/libCavalCade.so -Wl,-rpath,../CMarkup/dist/Debug/GNU-Linux-x86 ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so -Wl,-rpath,../GenomeLoader/dist/Debug/GNU-Linux-x86 ../GenomeLoader/dist/Debug/GNU-Linux-x86/libGenomeLoader.so  
