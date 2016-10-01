CPP = g++
CFLAGS = -Wall -Werror -std=c++11

main: main.cpp BST.o Node.o
	$(CPP) $(CFLAGS) -o main $^

BST.o: BST.h BST.cpp
		$(CPP) $(CFLAGS) -c BST.cpp

Node.o: Node.h Node.cpp
		$(CPP) $(CFLAGS) -c Node.cpp

clean:
	rm -f *.o;
	rm -f main;
	rm -f *~;
