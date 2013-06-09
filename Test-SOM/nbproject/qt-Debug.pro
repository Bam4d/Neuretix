# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = Test-SOM
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui
SOURCES += main.cpp GLEngine.cpp
HEADERS += globals.h GLEngine.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += -lpthread  -Wl,-rpath,../CMarkup/dist/Debug/GNU-Linux-x86 ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so -Wl,-rpath,../CavalCade/dist/Debug/GNU-Linux-x86 ../CavalCade/dist/Debug/GNU-Linux-x86/libCavalCade.so -Wl,-rpath,../GenomeLoader/dist/Debug/GNU-Linux-x86 ../GenomeLoader/dist/Debug/GNU-Linux-x86/libGenomeLoader.so -Wl,-rpath,../Structures/dist/Debug/GNU-Linux-x86 ../Structures/dist/Debug/GNU-Linux-x86/libStructures.so -lX11 -lglut -lGL -lGLU -lm  -lmgl -lmgl-wnd  
