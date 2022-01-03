#Rasmus Andersen   rasmus.andersen00@gmail.com
#Erik Nordahl  eriknordahl23@gmail.com

CPP := g++
CPPFLAGS := -Werror -Wpedantic -Wall -Wextra -std=c++17

all: AV
AV: Main.o av.o
	$(CPP) Main.o av.o -o AV.exe

main.o: Main.cpp
	$(CPP) -c $(CPPFLAGS) Main.cpp 
av.o: av.cpp av.hpp
	$(CPP) -c $(CPPFLAGS) av.cpp av.hpp

clean:
	rm -rf *o AV.exe