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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2018280917/axonList.o \
	${OBJECTDIR}/TimePoint.o \
	${OBJECTDIR}/_ext/2018280917/axon.o \
	${OBJECTDIR}/_ext/2018280917/SaveLoadCNN.o \
	${OBJECTDIR}/_ext/2018280917/group.o \
	${OBJECTDIR}/axon_event.o \
	${OBJECTDIR}/_ext/2018280917/neuron.o \
	${OBJECTDIR}/_ext/2018280917/ControlTimer.o \
	${OBJECTDIR}/TemporalWindow.o \
	${OBJECTDIR}/_ext/2018280917/CavalcadeMind.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/2018280917/axonList.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/axonList.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/axonList.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/axonList.cpp

${OBJECTDIR}/TimePoint.o: TimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/TimePoint.o TimePoint.cpp

${OBJECTDIR}/_ext/2018280917/axon.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/axon.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/axon.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/axon.cpp

${OBJECTDIR}/_ext/2018280917/SaveLoadCNN.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/SaveLoadCNN.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/SaveLoadCNN.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/SaveLoadCNN.cpp

${OBJECTDIR}/_ext/2018280917/group.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/group.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/group.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/group.cpp

${OBJECTDIR}/axon_event.o: axon_event.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon_event.o axon_event.cpp

${OBJECTDIR}/_ext/2018280917/neuron.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/neuron.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/neuron.cpp

${OBJECTDIR}/_ext/2018280917/ControlTimer.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/ControlTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/ControlTimer.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/ControlTimer.cpp

${OBJECTDIR}/TemporalWindow.o: TemporalWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/TemporalWindow.o TemporalWindow.cpp

${OBJECTDIR}/_ext/2018280917/CavalcadeMind.o: /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/CavalcadeMind.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/2018280917
	${RM} $@.d
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2018280917/CavalcadeMind.o /home/bam4d/NetBeansProjects/Cavalcade-Ubuntu-Glut/CavalCade/CavalcadeMind.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCavalCade.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
