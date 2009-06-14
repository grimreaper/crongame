#!/usr/bin/env sh

compile_it()
{
	g++ $(allegro-config --cppflags) -Iinclude -c src/*
	g++ $(allegro-config --cppflags --libs) -Iinclude *.o -o crongame
}

echo "We are not using the normal make method because when I tested pmake + ubuntu it failed badly.";
echo "if someone provides a fix for me - I'll gladly modify the Makefile and remove this script";
compile_it;