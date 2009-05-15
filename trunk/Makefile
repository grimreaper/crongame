NAME=crontab
CC = llvm-g++
CFLAGS = -g3 -pipe -ansi -Wabi
CFLAGS += -Weffc++ -fno-gnu-keywords -Wstrict-null-sentinel -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -ffor-scope
CFLAGS += -Wall -Wextra
CFLAGS += -Wformat=2 -Wformat-y2k -Wformat-nonliteral -Wformat-security
CFLAGS += -Wunused -Wunused-parameter -Winit-self -Wmissing-include-dirs -Wfloat-equal
CFLAGS += -Wfloat-equal -Wundef -Wshadow -Wcast-qual -Wcast-align -fabi-version=0 -funroll-loops
CFLAGS += -Wunreachable-code -Winline
#CFLAGS += -pthread -isystem /usr/local/include/boost/ -isystem /usr/local/include
#LDFLAGS += -L/usr/local/lib -lboost_filesystem
#SDL_FLAGS != sdl-config --cflags --libs
#SDL_FLAGS +=  -lSDL_mixer
ALLEGRO_FLAGS != allegro-config --cppflags --libs
INCLUDES = -I/usr/local/include -Iinclude/
CFLAGS += $(ALLEGRO_FLAGS) $(INCLUDES) #$(SDL_FLAGS)

#compiling options
.PHONY:     clean

all: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o $(NAME)

clean:
	rm -fv *.o
	rm -fv ./$(NAME)

