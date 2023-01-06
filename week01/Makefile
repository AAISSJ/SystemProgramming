TARGET=hello
CXX=gcc
OBJECTS=main.o plus.o minus.o
hello:main.o plus.o minus.o
	gcc -Wall -o w3.out main.o plus.o minus.o
main.o: main.c
	$(CXX) -Wall -c main.c 
plus.o: plus.c
	$(CXX) -Wall -c plus.c
minus.o: minus.c
	$(CXX) -Wall -c minus.c
clean:
	rm $(OBJECTS) w3.out
	rm *.txt
