# Generic OpenMPI Makefile
# Ostermann - Mar 15, 2022
CXX=mpicxx -Wall -Werror -O3

TARGET=hamcycle

CCSOURCES=${wildcard *.cc}
HEADERS=${wildcard *.h}
OBJECTS=${CCSOURCES:.cc=.o}

all: ${TARGET}

${TARGET}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${TARGET}

${OBJECTS}: ${HEADERS}

test: ${TARGET}
	-./test.star5
	-./test.s6_1
	-./test.s6_2
	-./test.s6_4
	-./test.s8_2
	-./test.s8_3
	-./test.s8_4
	-./test.s10_4
	-./test.s12_4
	-./test.bl10
	-./test.bl12


clean:
	rm -f  *.o ${TARGET} test.*.*
