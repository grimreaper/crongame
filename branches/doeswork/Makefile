NAME=crontab
CC = llvm-g++
CFLAGS = -O0 -g3 -pipe -ansi -Wabi
CFLAGS += -Weffc++ -fno-gnu-keywords -Wstrict-null-sentinel -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -ffor-scope
CFLAGS += -Wall -Wextra
CFLAGS += -Wformat=2 -Wformat-y2k -Wformat-nonliteral -Wformat-security
CFLAGS += -Wunused -Wunused-parameter -Winit-self -Wmissing-include-dirs -Wfloat-equal
CFLAGS += -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wcast-align -fabi-version=0 -funroll-loops
CFLAGS += -Wunreachable-code -Winline
#CFLAGS += -pthread -isystem /usr/local/include/boost/ -isystem /usr/local/include
#LDFLAGS += -L/usr/local/lib -lboost_filesystem
ALLEGRO_FLAGS != allegro-config --cppflags
ALLEGRO_LINK_FLAGS != allegro-config --libs
INCLUDES = -I/usr/local/include -Iinclude/
CFLAGS += $(ALLEGRO_FLAGS) $(INCLUDES) #$(SDL_FLAGS)
LINK_FLAGS = $(ALLEGRO_LINK_FLAGS)
LDFLAGS += $(ALLEGRO_LINK_FLAGS)

SRCDIR = src
HDRDIR = include
SRCS != find $(SRCDIR) -name "*.cpp"
TSTSRCS = gerror.cpp
HDRS != find $(HDRDIR) -name "*.h"
OBJS= gamefield.o kernel.o brick.o krandom.o gerror.o mtimer.o ball.o paddle.o
TXTFILES = LICENSE
BUILDFILES = Makefile

ALLFILES = $(HDRS) $(SRCS) $(TXTFILES) $(BUILDFILES)

#compiling options
.PHONY:     all clean test test-all

all: $(OBJS) $(SRCDIR)/main.cpp

$(SRCDIR)/main.cpp: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $@ -o $(NAME)

gamefield.o: $(SRCDIR)/gamefield.cpp krandom.o brick.o
kernel.o: $(SRCDIR)/kernel.cpp mtimer.o gamefield.o ball.o paddle.o
brick.o: $(SRCDIR)/brick.cpp
krandom.o: $(SRCDIR)/krandom.cpp
gerror.o: $(SRCDIR)/gerror.cpp
mtimer.o: $(SRCDIR)/mtimer.cpp
ball.o: $(SRCDIR)/ball.cpp paddle.o
paddle.o: $(SRCDIR)/paddle.cpp

clean:
	rm -fv tests/*-test
	rm -fv $(OBJS)
	rm -fv ./$(NAME)

test:
	$(CC) -DTEST $(CFLAGS) $(LDFLAGS) $(SRCDIR)/$(FILE) -o tests/$(FILE)-test

test-all:
	for file in $(TSTSRCS);do $(MAKE) test FILE=$$file; done;

check:
	cppcheck -v -a -s --unused-functions .
	rats -rw3 *
#splint -strict-lib -showcolumn -showfunc -strict *.c

#	$(CC) $(CFLAGS) -c $< -o $@
