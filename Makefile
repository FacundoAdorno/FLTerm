#Makefile for Linux build with mbedTLS crypto backend
HEADERS = src/host.h src/ssh2.h
OBJS = obj/tiny2.o obj/ssh2.o obj/host.o obj/Fl_Term.o obj/Fl_Browser_Input.o

DEBUG_FLAGS= -g -O0
FLTK_DIR = libs/fltk-1.3.11
CFLAGS = -Os -std=c++11 -I${FLTK_DIR} ${shell ${FLTK_DIR}/fltk-config --cxxflags} -I.
LDFLAGS = ${FLTK_DIR}/lib/libfltk.a ${shell ${FLTK_DIR}/fltk-config --ldflags} -lstdc++ -lssh2 -lmbedcrypto

all: tinyTerm2

tinyTerm2: ${OBJS}
	cc -o "$@" ${OBJS} ${LDFLAGS}

obj/%.o: src/%.cxx ${HEADERS}
	${CC} ${DEBUG_FLAGS} ${CFLAGS} -c $< -o $@

clean:
	rm obj/*.o "tinyTerm2"
