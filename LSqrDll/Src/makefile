# makefile for C++ version of LSQR.
#
# 02 Aug 2007: Debugged on Red Hat Linux and tested out OK.
# 13 May 2003: First conversion of C to C++ for gcc by J.A.Tomlin
# 08 Sep 1999: First C version from James W. Howse <jhowse@lanl.gov>

CC = g++
CFLAGS = -g
CLIBS = -lm
#USRLIBDIR = ${HOME}/lib/SunOS_5.x
#LIBSRCHDIR = -L${USRLIBDIR}
#USRINCDIR = ${HOME}/include
#INCSRCHDIR = -I${USRINCDIR}

PROG = testit
 
TEST_SRCS = Model.cpp \
	    test_prog.cpp \
	    test_lsqr.cpp 
LSQR_SRCS = Lsqr.cpp 

TEST_INCS = Lsqr.hpp Model.hpp test_lsqr.hpp
LSQR_INCS = LsqrTypes.hpp
 
TEST_OBJS = ${TEST_SRCS:.cpp=.o}
LSQR_OBJS = ${LSQR_SRCS:.cpp=.o}
COBJS = ${TEST_OBJS}  ${LSQR_OBJS}

.SUFFIXES:

.SUFFIXES: .o .cpp

.cpp.o:
	${CC} ${CFLAGS} ${INCSRCHDIR} -c $<

${PROG}: ${COBJS}
	${CC} ${CFLAGS} -o ${PROG} ${COBJS} ${LIBSRCHDIR} ${CLIBS}

${TEST_OBJS} : ${TEST_INCS}
${COBJS} : ${LSQR_INCS}

debug:
	make "CFLAGS=-g -ftrap=division"

profile:
	make "CFLAGS=-G -g -ftrap=division"

clean:
	rm *.o ${PROG} 
