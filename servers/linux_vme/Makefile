#
# File:
#    Makefile
#
# Description:
#    Makefile for the coda primary and secondary readout lists 
#    running on an Intel-based controller running Linux
#
#
# $Date: 2012-11-26 15:25:27 -0500 (Mon, 26 Nov 2012) $
# $Rev: 10911 $
#
# Uncomment DEBUG line for debugging info ( -g and -Wall )
DEBUG=1
#


LINUXVME_LIB	= ${LINUXVME_HOME}/lib
LINUXVME_INC	= ${LINUXVME_HOME}/include


# DEFs for compiling primary readout lists
CC			= gcc
AR                      = ar
RANLIB                  = ranlib


CFLAGS			+= -w -I${LINUXVME_INC} -I. -I/usr/include -I${CODA}/common/include\
			  -L${LINUXVME_LIB} -L. -DJLAB
CFLAGS			+= -lrt -lpthread -ljvme -lti  $(ROLLIBS)


# DEFs for compiling CODA readout lists

CODA_INCS		= -I.  -I${LINUXVME_INC} -I/usr/include/mysql
#-I${CODA}/common/include

CODA_LIBDIRS            = -L. -L${LINUXVME_LIB} -L/usr/lib/mysql -DLinux_vme


CODA_LIBS		= -ljvme -lti -ltd -lts -lsd -lctp -lfadc -ldsc2 -ltdc1190 -lf1tdc \
 			 -lssp -ldl  -DJLAB -lrt -lpthread -lmysqlclient

CODA_DEFS		= -DLINUX -DDAYTIME=\""`date`"\"

CODA_CFLAGS		=  -w -fpic  ${CODA_INCS} ${CODA_LIBDIRS} \
			  ${CODA_LIBS} ${CODA_DEFS}


ifdef DEBUG
CODA_CFLAGS		+= -Wall -g
endif


all:	DiagGuiServer	


DiagGuiServer.o: DiagGuiServer.c
	 ${CC}  ${CODA_CFLAGS} -c  DiagGuiServer.c  -ldl -lpthread -lrt

CrateMsgServer.o: CrateMsgServer.c
	 ${CC}  ${CODA_CFLAGS} -c  CrateMsgServer.c  -ldl -lpthread -lrt

DiagGuiServer: DiagGuiServer.o  CrateMsgServer.o
	 ${CC} -o DiagGuiServer  DiagGuiServer.o CrateMsgServer.o ${CODA_CFLAGS}


clean distclean:
	@rm -f DiagGuiServer
