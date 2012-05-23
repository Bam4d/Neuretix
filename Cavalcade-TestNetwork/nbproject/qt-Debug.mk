#############################################################################
# Makefile for building: dist/Debug/GNU-Linux-x86/Cavalcade-TestNetwork
# Generated by qmake (2.01a) (Qt 4.7.2) on: Wed May 23 14:41:13 2012
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: /usr/bin/qmake VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -ICMarkup -I. -I. -Inbproject -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lX11 -lglut -lGL -lGLU -lm -Wl,-rpath ../CavalCade/dist/Debug/GNU-Linux-x86 ../CavalCade/dist/Debug/GNU-Linux-x86/libCavalCade.so -Wl,-rpath ../CMarkup/dist/Debug/GNU-Linux-x86 ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so -Wl,-rpath ../GenomeLoader/dist/Debug/GNU-Linux-x86 ../GenomeLoader/dist/Debug/GNU-Linux-x86/libGenomeLoader.so -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux-x86/

####### Files

SOURCES       = main.cpp \
		OnlineRandomNums.cpp \
		GLEngine.cpp \
		CNNControl.cpp moc_CNNControl.cpp
OBJECTS       = build/Debug/GNU-Linux-x86/main.o \
		build/Debug/GNU-Linux-x86/OnlineRandomNums.o \
		build/Debug/GNU-Linux-x86/GLEngine.o \
		build/Debug/GNU-Linux-x86/CNNControl.o \
		build/Debug/GNU-Linux-x86/moc_CNNControl.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		nbproject/qt-Debug.pro
QMAKE_TARGET  = Cavalcade-TestNetwork
DESTDIR       = dist/Debug/GNU-Linux-x86/
TARGET        = dist/Debug/GNU-Linux-x86/Cavalcade-TestNetwork

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Debug.mk $(TARGET)

$(TARGET): ui_CNNControl.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dist/Debug/GNU-Linux-x86/ || $(MKDIR) dist/Debug/GNU-Linux-x86/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

qttmp-Debug.mk: nbproject/qt-Debug.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist: 
	@$(CHK_DIR_EXISTS) nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0 || $(MKDIR) nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0/ && $(COPY_FILE) --parents globals.h CNNControl.h GLEngine.h OnlineRandomNums.h nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0/ && $(COPY_FILE) --parents main.cpp OnlineRandomNums.cpp GLEngine.cpp CNNControl.cpp nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0/ && $(COPY_FILE) --parents CNNControl.ui nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0/ && (cd `dirname nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0` && $(TAR) Cavalcade-TestNetwork1.0.0.tar Cavalcade-TestNetwork1.0.0 && $(COMPRESS) Cavalcade-TestNetwork1.0.0.tar) && $(MOVE) `dirname nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0`/Cavalcade-TestNetwork1.0.0.tar.gz . && $(DEL_FILE) -r nbproject/build/Debug/GNU-Linux-x86/Cavalcade-TestNetwork1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) qttmp-Debug.mk


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_CNNControl.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_CNNControl.cpp
moc_CNNControl.cpp: ../CavalCade/CNNGlobals.h \
		../CMarkup/Markup.h \
		../CavalCade/axon.h \
		../CavalCade/axonList.h \
		../CavalCade/neuron.h \
		../CavalCade/group.h \
		../CavalCade/ControlTimer.h \
		../CavalCade/axon_event.h \
		../CavalCade/TimePoint.h \
		../CavalCade/TemporalWindow.h \
		../CavalCade/CavalcadeMind.h \
		../CavalCade/SaveLoadCNN.h \
		../GenomeLoader/GenomeLoaderGlobals.h \
		../GenomeLoader/Genetic.h \
		../GenomeLoader/ClusterMap.h \
		../GenomeLoader/ClusterMapLink.h \
		../GenomeLoader/Genome.h \
		../GenomeLoader/GAEngine.h \
		ui_CNNControl.h \
		CNNControl.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) CNNControl.h -o moc_CNNControl.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_CNNControl.h
compiler_uic_clean:
	-$(DEL_FILE) ui_CNNControl.h
ui_CNNControl.h: CNNControl.ui
	/usr/bin/uic-qt4 CNNControl.ui -o ui_CNNControl.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

build/Debug/GNU-Linux-x86/main.o: main.cpp CNNControl.h \
		../CavalCade/CNNGlobals.h \
		../CMarkup/Markup.h \
		../CavalCade/axon.h \
		../CavalCade/axonList.h \
		../CavalCade/neuron.h \
		../CavalCade/group.h \
		../CavalCade/ControlTimer.h \
		../CavalCade/axon_event.h \
		../CavalCade/TimePoint.h \
		../CavalCade/TemporalWindow.h \
		../CavalCade/CavalcadeMind.h \
		../CavalCade/SaveLoadCNN.h \
		../GenomeLoader/GenomeLoaderGlobals.h \
		../GenomeLoader/Genetic.h \
		../GenomeLoader/ClusterMap.h \
		../GenomeLoader/ClusterMapLink.h \
		../GenomeLoader/Genome.h \
		../GenomeLoader/GAEngine.h \
		ui_CNNControl.h \
		globals.h \
		GLEngine.h \
		OnlineRandomNums.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/main.o main.cpp

build/Debug/GNU-Linux-x86/OnlineRandomNums.o: OnlineRandomNums.cpp globals.h \
		GLEngine.h \
		../CavalCade/CNNGlobals.h \
		../CMarkup/Markup.h \
		../CavalCade/axon.h \
		../CavalCade/axonList.h \
		../CavalCade/neuron.h \
		../CavalCade/group.h \
		../CavalCade/ControlTimer.h \
		../CavalCade/axon_event.h \
		../CavalCade/TimePoint.h \
		../CavalCade/TemporalWindow.h \
		../CavalCade/CavalcadeMind.h \
		../CavalCade/SaveLoadCNN.h \
		../GenomeLoader/GenomeLoaderGlobals.h \
		../GenomeLoader/Genetic.h \
		../GenomeLoader/ClusterMap.h \
		../GenomeLoader/ClusterMapLink.h \
		../GenomeLoader/Genome.h \
		../GenomeLoader/GAEngine.h \
		OnlineRandomNums.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/OnlineRandomNums.o OnlineRandomNums.cpp

build/Debug/GNU-Linux-x86/GLEngine.o: GLEngine.cpp globals.h \
		GLEngine.h \
		../CavalCade/CNNGlobals.h \
		../CMarkup/Markup.h \
		../CavalCade/axon.h \
		../CavalCade/axonList.h \
		../CavalCade/neuron.h \
		../CavalCade/group.h \
		../CavalCade/ControlTimer.h \
		../CavalCade/axon_event.h \
		../CavalCade/TimePoint.h \
		../CavalCade/TemporalWindow.h \
		../CavalCade/CavalcadeMind.h \
		../CavalCade/SaveLoadCNN.h \
		../GenomeLoader/GenomeLoaderGlobals.h \
		../GenomeLoader/Genetic.h \
		../GenomeLoader/ClusterMap.h \
		../GenomeLoader/ClusterMapLink.h \
		../GenomeLoader/Genome.h \
		../GenomeLoader/GAEngine.h \
		OnlineRandomNums.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/GLEngine.o GLEngine.cpp

build/Debug/GNU-Linux-x86/CNNControl.o: CNNControl.cpp CNNControl.h \
		../CavalCade/CNNGlobals.h \
		../CMarkup/Markup.h \
		../CavalCade/axon.h \
		../CavalCade/axonList.h \
		../CavalCade/neuron.h \
		../CavalCade/group.h \
		../CavalCade/ControlTimer.h \
		../CavalCade/axon_event.h \
		../CavalCade/TimePoint.h \
		../CavalCade/TemporalWindow.h \
		../CavalCade/CavalcadeMind.h \
		../CavalCade/SaveLoadCNN.h \
		../GenomeLoader/GenomeLoaderGlobals.h \
		../GenomeLoader/Genetic.h \
		../GenomeLoader/ClusterMap.h \
		../GenomeLoader/ClusterMapLink.h \
		../GenomeLoader/Genome.h \
		../GenomeLoader/GAEngine.h \
		ui_CNNControl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/CNNControl.o CNNControl.cpp

build/Debug/GNU-Linux-x86/moc_CNNControl.o: moc_CNNControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/moc_CNNControl.o moc_CNNControl.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
