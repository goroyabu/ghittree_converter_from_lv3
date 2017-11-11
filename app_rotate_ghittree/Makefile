TARGET = app_rotate_ghittree
OBJECTS = main.o GHittreeRotation.o DualCCRotation.o

CXX_DEBUG_FLAGS = -pg -O0
CXX_RELEASE_FLAGS = -s -O2

FLAGS = -I${INCLUDEPATH}

ROOTCFLAGS = `root-config --cflags --libs`
ROOTGLIBS  = `root-config --cflags --libs`
LIBS = -lm -lfftw3 -O3

CXX = g++
CXXFLAGS = -O2 -W -Wall ${ROOTCFLAGS} ${FLAGS}
CXXLIBS = ${ROOTGLIBS} ${LIBS}

.PHONY : release
release : CXXFLAGS += ${CXX_RELEASE_FLAGS}
release : all
.PHONY : debug
debug : CXXFLAGS += ${CXX_DEBUG_FLAGS}
debug : all

all : ${TARGET} 

${TARGET} : ${OBJECTS}
	${CXX} -o $@ ${OBJECTS} ${CXXLIBS}

.C.o :
	${CXX} ${CXXFLAGS} -c $< -I.

.PHONY : clean
clean :
	@rm -f ${TARGET} *.o *~
