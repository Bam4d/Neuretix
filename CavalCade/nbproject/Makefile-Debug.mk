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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/TimePoint.o \
	${OBJECTDIR}/group.o \
	${OBJECTDIR}/axon_event.o \
	${OBJECTDIR}/ControlTimer.o \
	${OBJECTDIR}/neuron.o \
	${OBJECTDIR}/axon.o \
	${OBJECTDIR}/TemporalWindow.o \
	${OBJECTDIR}/axonList.o \
	${OBJECTDIR}/CavalcadeMind.o \
	${OBJECTDIR}/SaveLoadCNN.o \
	${OBJECTDIR}/LeakyIntegrator.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath ../CMarkup/dist/Debug/GNU-Linux-x86 -L../CMarkup/dist/Debug/GNU-Linux-x86 -lCMarkup -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so: ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/TimePoint.o: TimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/TimePoint.o TimePoint.cpp

${OBJECTDIR}/group.o: group.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/group.o group.cpp

${OBJECTDIR}/axon_event.o: axon_event.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon_event.o axon_event.cpp

${OBJECTDIR}/ControlTimer.o: ControlTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/ControlTimer.o ControlTimer.cpp

${OBJECTDIR}/neuron.o: neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/neuron.o neuron.cpp

${OBJECTDIR}/axon.o: axon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon.o axon.cpp

${OBJECTDIR}/TemporalWindow.o: TemporalWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/TemporalWindow.o TemporalWindow.cpp

${OBJECTDIR}/axonList.o: axonList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axonList.o axonList.cpp

${OBJECTDIR}/CavalcadeMind.o: CavalcadeMind.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/CavalcadeMind.o CavalcadeMind.cpp

${OBJECTDIR}/SaveLoadCNN.o: SaveLoadCNN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/SaveLoadCNN.o SaveLoadCNN.cpp

${OBJECTDIR}/LeakyIntegrator.o: LeakyIntegrator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/LeakyIntegrator.o LeakyIntegrator.cpp

# Subprojects
.build-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so

# Subprojects
.clean-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
