#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as
QMAKE=qmake

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES=


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread -lX11 -lglut -lGL -lGLU -lm -Wl,-rpath,../CMarkup/dist/Debug/GNU-Linux-x86 -L../CMarkup/dist/Debug/GNU-Linux-x86 -lCMarkup -Wl,-rpath,../CavalCade/dist/Debug/GNU-Linux-x86 -L../CavalCade/dist/Debug/GNU-Linux-x86 -lCavalCade -Wl,-rpath,../NeuroPlasticity/dist/Debug/GNU-Linux-x86 -L../NeuroPlasticity/dist/Debug/GNU-Linux-x86 -lNeuroPlasticity -Wl,-rpath,../GenomeLoader/dist/Debug/GNU-Linux-x86 -L../GenomeLoader/dist/Debug/GNU-Linux-x86 -lGenomeLoader -Wl,-rpath,../Structures/dist/Debug/GNU-Linux-x86 -L../Structures/dist/Debug/GNU-Linux-x86 -lStructures

nbproject/qt-${CND_CONF}.mk: nbproject/qt-${CND_CONF}.pro FORCE
	${QMAKE} VPATH=. -o qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.pro
	mv -f qttmp-${CND_CONF}.mk nbproject/qt-${CND_CONF}.mk

FORCE:

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	"${MAKE}" -f nbproject/qt-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Test-GenerateSOM

${CND_BUILDDIR}/Debug/%.o: nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk "$@"

# Subprojects
.build-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug
	cd ../Structures && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS} nbproject/qt-${CND_CONF}.mk
	${MAKE} -f nbproject/qt-${CND_CONF}.mk distclean

# Subprojects
.clean-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Structures && ${MAKE}  -f Makefile CONF=Debug clean
