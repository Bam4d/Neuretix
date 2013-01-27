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
OBJECTFILES= \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../CavalCade/dist/Debug/GNU-Linux-x86 -L../CavalCade/dist/Debug/GNU-Linux-x86 -lCavalCade -Wl,-rpath,../CMarkup/dist/Debug/GNU-Linux-x86 -L../CMarkup/dist/Debug/GNU-Linux-x86 -lCMarkup -Wl,-rpath,../NeuroPlasticity/dist/Debug/GNU-Linux-x86 -L../NeuroPlasticity/dist/Debug/GNU-Linux-x86 -lNeuroPlasticity -Wl,-rpath,../GenomeLoader/dist/Debug/GNU-Linux-x86 -L../GenomeLoader/dist/Debug/GNU-Linux-x86 -lGenomeLoader -Wl,-rpath,../Structures/dist/Debug/GNU-Linux-x86 -L../Structures/dist/Debug/GNU-Linux-x86 -lStructures -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom: ../CavalCade/dist/Debug/GNU-Linux-x86/libCavalCade.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom: ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom: ../NeuroPlasticity/dist/Debug/GNU-Linux-x86/libNeuroPlasticity.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom: ../GenomeLoader/dist/Debug/GNU-Linux-x86/libGenomeLoader.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom: ../Structures/dist/Debug/GNU-Linux-x86/libStructures.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug
	cd ../Structures && ${MAKE}  -f Makefile CONF=Debug
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug
	cd ../Structures && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test-neuroplasticityinsom

# Subprojects
.clean-subprojects:
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Structures && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Structures && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
