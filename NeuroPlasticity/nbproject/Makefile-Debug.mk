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
	${OBJECTDIR}/STDPNeuron.o \
	${OBJECTDIR}/SAxon.o \
	${OBJECTDIR}/PreSynapticCyclicCache.o \
	${OBJECTDIR}/PreSynapticEvent.o \
	${OBJECTDIR}/STDPGroup.o \
	${OBJECTDIR}/PreSynapticTimePoint.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,../CMarkup/dist/Debug/GNU-Linux-x86 -L../CMarkup/dist/Debug/GNU-Linux-x86 -lCMarkup -Wl,-rpath,../CavalCade/dist/Debug/GNU-Linux-x86 -L../CavalCade/dist/Debug/GNU-Linux-x86 -lCavalCade

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNeuroPlasticity.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNeuroPlasticity.${CND_DLIB_EXT}: ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNeuroPlasticity.${CND_DLIB_EXT}: ../CavalCade/dist/Debug/GNU-Linux-x86/libCavalCade.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNeuroPlasticity.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNeuroPlasticity.${CND_DLIB_EXT} -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/STDPNeuron.o: STDPNeuron.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/STDPNeuron.o STDPNeuron.cpp

${OBJECTDIR}/SAxon.o: SAxon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/SAxon.o SAxon.cpp

${OBJECTDIR}/PreSynapticCyclicCache.o: PreSynapticCyclicCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/PreSynapticCyclicCache.o PreSynapticCyclicCache.cpp

${OBJECTDIR}/PreSynapticEvent.o: PreSynapticEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/PreSynapticEvent.o PreSynapticEvent.cpp

${OBJECTDIR}/STDPGroup.o: STDPGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/STDPGroup.o STDPGroup.cpp

${OBJECTDIR}/PreSynapticTimePoint.o: PreSynapticTimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/PreSynapticTimePoint.o PreSynapticTimePoint.cpp

# Subprojects
.build-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libNeuroPlasticity.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
