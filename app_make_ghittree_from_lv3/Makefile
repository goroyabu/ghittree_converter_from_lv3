COMPILER = g++
CPPFLAGS += `root-config --cflags`
LDLIBS   += `root-config --libs`
.PHONY : clean
all : app_make_ghittree_from_lv3
HittreeLv3Reader.o : HittreeLv3Reader.cpp
	${COMPILER} -c HittreeLv3Reader.cpp ${CPPFLAGS} ${LDLIBS}
GHittreeMaker.o : GHittreeMaker.cpp
	${COMPILER} -c GHittreeMaker.cpp ${CPPFLAGS} ${LDLIBS}
app_make_ghittree_from_lv3 : main.cpp GHittreeMaker.o HittreeLv3Reader.o
	g++ -o app_make_ghittree_from_lv3 main.cpp GHittreeMaker.o HittreeLv3Reader.o ${CPPFLAGS} ${LDLIBS}
clean :
	rm -f *~ *.o app_*
