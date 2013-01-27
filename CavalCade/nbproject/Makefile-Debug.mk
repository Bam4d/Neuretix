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
	${OBJECTDIR}/TimePoint.o \
	${OBJECTDIR}/CyclicCacheEvent.o \
	${OBJECTDIR}/CyclicCacheTimePoint.o \
	${OBJECTDIR}/group.o \
	${OBJECTDIR}/axon_event.o \
	${OBJECTDIR}/ControlTimer.o \
	${OBJECTDIR}/neuron.o \
	${OBJECTDIR}/axon.o \
	${OBJECTDIR}/CyclicCache.o \
	${OBJECTDIR}/axonList.o \
	${OBJECTDIR}/CavalcadeMind.o \
	${OBJECTDIR}/SaveLoadCNN.o \
	${OBJECTDIR}/LeakyIntegrator.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

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
LDLIBSOPTIONS=-Wl,-rpath,../CMarkup/dist/Debug/GNU-Linux-x86 -L../CMarkup/dist/Debug/GNU-Linux-x86 -lCMarkup -lpthread -lcppunit

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f2

${TESTDIR}/TestFiles/f2: ../CMarkup/dist/Debug/GNU-Linux-x86/libCMarkup.so

${TESTDIR}/TestFiles/f2: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -shared -o ${TESTDIR}/TestFiles/f2 -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/TimePoint.o: TimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/TimePoint.o TimePoint.cpp

${OBJECTDIR}/CyclicCacheEvent.o: CyclicCacheEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/CyclicCacheEvent.o CyclicCacheEvent.cpp

${OBJECTDIR}/CyclicCacheTimePoint.o: CyclicCacheTimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/CyclicCacheTimePoint.o CyclicCacheTimePoint.cpp

${OBJECTDIR}/group.o: group.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/group.o group.cpp

${OBJECTDIR}/axon_event.o: axon_event.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon_event.o axon_event.cpp

${OBJECTDIR}/ControlTimer.o: ControlTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/ControlTimer.o ControlTimer.cpp

${OBJECTDIR}/neuron.o: neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/neuron.o neuron.cpp

${OBJECTDIR}/axon.o: axon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon.o axon.cpp

${OBJECTDIR}/CyclicCache.o: CyclicCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/CyclicCache.o CyclicCache.cpp

${OBJECTDIR}/axonList.o: axonList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/axonList.o axonList.cpp

${OBJECTDIR}/CavalcadeMind.o: CavalcadeMind.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/CavalcadeMind.o CavalcadeMind.cpp

${OBJECTDIR}/SaveLoadCNN.o: SaveLoadCNN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/SaveLoadCNN.o SaveLoadCNN.cpp

${OBJECTDIR}/LeakyIntegrator.o: LeakyIntegrator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I. -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/LeakyIntegrator.o LeakyIntegrator.cpp

# Subprojects
.build-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/CyclicCacheTestClass.o ${TESTDIR}/tests/CyclicCacheTestRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -lcppunit -lcppunit -lcppunit -lcppunit 


${TESTDIR}/tests/CyclicCacheTestClass.o: tests/CyclicCacheTestClass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CyclicCacheTestClass.o tests/CyclicCacheTestClass.cpp


${TESTDIR}/tests/CyclicCacheTestRunner.o: tests/CyclicCacheTestRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. -I. -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/CyclicCacheTestRunner.o tests/CyclicCacheTestRunner.cpp


${OBJECTDIR}/TimePoint_nomain.o: ${OBJECTDIR}/TimePoint.o TimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/TimePoint.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/TimePoint_nomain.o TimePoint.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/TimePoint.o ${OBJECTDIR}/TimePoint_nomain.o;\
	fi

${OBJECTDIR}/CyclicCacheEvent_nomain.o: ${OBJECTDIR}/CyclicCacheEvent.o CyclicCacheEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CyclicCacheEvent.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CyclicCacheEvent_nomain.o CyclicCacheEvent.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CyclicCacheEvent.o ${OBJECTDIR}/CyclicCacheEvent_nomain.o;\
	fi

${OBJECTDIR}/CyclicCacheTimePoint_nomain.o: ${OBJECTDIR}/CyclicCacheTimePoint.o CyclicCacheTimePoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CyclicCacheTimePoint.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CyclicCacheTimePoint_nomain.o CyclicCacheTimePoint.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CyclicCacheTimePoint.o ${OBJECTDIR}/CyclicCacheTimePoint_nomain.o;\
	fi

${OBJECTDIR}/group_nomain.o: ${OBJECTDIR}/group.o group.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/group.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/group_nomain.o group.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/group.o ${OBJECTDIR}/group_nomain.o;\
	fi

${OBJECTDIR}/axon_event_nomain.o: ${OBJECTDIR}/axon_event.o axon_event.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/axon_event.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon_event_nomain.o axon_event.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/axon_event.o ${OBJECTDIR}/axon_event_nomain.o;\
	fi

${OBJECTDIR}/ControlTimer_nomain.o: ${OBJECTDIR}/ControlTimer.o ControlTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ControlTimer.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ControlTimer_nomain.o ControlTimer.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ControlTimer.o ${OBJECTDIR}/ControlTimer_nomain.o;\
	fi

${OBJECTDIR}/neuron_nomain.o: ${OBJECTDIR}/neuron.o neuron.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/neuron.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/neuron_nomain.o neuron.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/neuron.o ${OBJECTDIR}/neuron_nomain.o;\
	fi

${OBJECTDIR}/axon_nomain.o: ${OBJECTDIR}/axon.o axon.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/axon.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/axon_nomain.o axon.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/axon.o ${OBJECTDIR}/axon_nomain.o;\
	fi

${OBJECTDIR}/CyclicCache_nomain.o: ${OBJECTDIR}/CyclicCache.o CyclicCache.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CyclicCache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CyclicCache_nomain.o CyclicCache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CyclicCache.o ${OBJECTDIR}/CyclicCache_nomain.o;\
	fi

${OBJECTDIR}/axonList_nomain.o: ${OBJECTDIR}/axonList.o axonList.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/axonList.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/axonList_nomain.o axonList.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/axonList.o ${OBJECTDIR}/axonList_nomain.o;\
	fi

${OBJECTDIR}/CavalcadeMind_nomain.o: ${OBJECTDIR}/CavalcadeMind.o CavalcadeMind.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CavalcadeMind.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/CavalcadeMind_nomain.o CavalcadeMind.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CavalcadeMind.o ${OBJECTDIR}/CavalcadeMind_nomain.o;\
	fi

${OBJECTDIR}/SaveLoadCNN_nomain.o: ${OBJECTDIR}/SaveLoadCNN.o SaveLoadCNN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SaveLoadCNN.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SaveLoadCNN_nomain.o SaveLoadCNN.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SaveLoadCNN.o ${OBJECTDIR}/SaveLoadCNN_nomain.o;\
	fi

${OBJECTDIR}/LeakyIntegrator_nomain.o: ${OBJECTDIR}/LeakyIntegrator.o LeakyIntegrator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/LeakyIntegrator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g -I. -fPIC  -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/LeakyIntegrator_nomain.o LeakyIntegrator.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/LeakyIntegrator.o ${OBJECTDIR}/LeakyIntegrator_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f2

# Subprojects
.clean-subprojects:
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CMarkup && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
