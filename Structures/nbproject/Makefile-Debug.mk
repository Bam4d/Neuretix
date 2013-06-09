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
	${OBJECTDIR}/SelfOrganisingMap.o


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
LDLIBSOPTIONS=-Wl,-rpath,../NeuroPlasticity/dist/Debug/GNU-Linux-x86 -L../NeuroPlasticity/dist/Debug/GNU-Linux-x86 -lNeuroPlasticity

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libStructures.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libStructures.${CND_DLIB_EXT}: ../NeuroPlasticity/dist/Debug/GNU-Linux-x86/libNeuroPlasticity.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libStructures.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libStructures.${CND_DLIB_EXT} -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/SelfOrganisingMap.o: SelfOrganisingMap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/SelfOrganisingMap.o SelfOrganisingMap.cpp

# Subprojects
.build-subprojects:
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libStructures.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../NeuroPlasticity && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CavalCade && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../GenomeLoader && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
