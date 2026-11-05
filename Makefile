#Makefile for Linux build with mbedTLS crypto backend
HEADERS = src/host.h src/ssh2.h src/theme.h src/json.hpp
OBJS = obj/tiny2.o obj/ssh2.o obj/host.o obj/Fl_Term.o obj/Fl_Browser_Input.o

PREFIX ?=
THEME_DIR ?= $(PREFIX)/usr/local/share/flterm/color_themes
BIN_DIR ?= $(PREFIX)/usr/local/bin

DEBUG_FLAGS= -g -O0
FLTK_DIR = libs/fltk-1.3.11
CFLAGS = -Os -std=c++11 -DTHEME_DIR=\"$(THEME_DIR)\" -I${FLTK_DIR} ${shell ${FLTK_DIR}/fltk-config --cxxflags} -I.
LDFLAGS = ${FLTK_DIR}/lib/libfltk.a ${shell ${FLTK_DIR}/fltk-config --ldflags} -lstdc++ -lssh2 -lmbedcrypto

all: tinyTerm2

tinyTerm2: ${OBJS}
	cc -o "$@" ${OBJS} ${LDFLAGS}

obj/%.o: src/%.cxx ${HEADERS}
	${CC} ${DEBUG_FLAGS} ${CFLAGS} -c $< -o $@

install: tinyTerm2
	mkdir -p $(BIN_DIR)
	mkdir -p $(THEME_DIR)
	cp tinyTerm2 $(BIN_DIR)/flterm
	cp themes/*.json $(THEME_DIR)/

clean:
	rm -f obj/*.o

clean-install: clean
	rm -rf "./build/"
