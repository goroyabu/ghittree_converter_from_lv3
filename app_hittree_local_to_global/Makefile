COMPILER = g++
CPPFLAGS += `root-config --cflags`
LDLIBS += `root-config --libs`
.PHONY : clean
all : app_hittree_local_to_global
DualCCTransformer.o : DualCCTransformer.cpp
	${COMPILER} -c DualCCTransformer.cpp ${CPPFLAGS} ${LDLIBS}
HittreeConverterOISTCC.o : HittreeConverterOISTCC.cpp
	${COMPILER} -c HittreeConverterOISTCC.cpp ${CPPFLAGS} ${LDLIBS}
app_hittree_local_to_global : main.cpp DualCCTransformer.o HittreeConverterOISTCC.o
	${COMPILER} -o app_hittree_local_to_global main.cpp DualCCTransformer.o HittreeConverterOISTCC.o ${CPPFLAGS} ${LDLIBS}
clean :
	rm -f *~ *.o app_*
