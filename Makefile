#
# Makefile of "Flag Breaker!"
# STNUMのところを自分のPCログイン名に変えてください
#


STNUM = uemorikaoru

CPP	= gcc
CFLAGS	= -O3 -Wall
INCDIR 	= -I/Users/${STNUM}/local/include/SDL
LIBDIR	= -L/Users/${STNUM}/local/lib
LIBS	= -lncurses -lSDL -lSDL_image -lSDL_net -lSDLmain -lncurses -framework Cocoa

SSRCS = server.c game_lib.c networks.c
SOBJS = ${SSRCS:.c=.o}
CSRCS = client.c game_lib.c networks.c
COBJS = ${CSRCS:.c=.o}


ALL: server client

server: ${SOBJS}
	${CPP} ${CFLAGS} ${INCDIR} -o $@ ${SOBJS} ${LIBDIR} ${LIBS}
client: ${COBJS}
	${CPP} ${CFLAGS} ${INCDIR} -o $@ ${COBJS} ${LIBDIR} ${LIBS}

.c.o:
	${CPP} ${CFLAGS} ${INCDIR} -c $<

.PHONY: clean
clean:
	${RM} *.o *.*~ *~ server client
