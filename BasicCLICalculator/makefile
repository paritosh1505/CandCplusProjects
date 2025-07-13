result: main.o SimpleEval.o
	g++ main.o SimpleEval.o -o result

main.o: main.cpp
	g++ -c main.cpp

SimpleEval.o: SimpleEval.h SimpleEval.cpp
	g++ -c SimpleEval.cpp

clean:
	rm *.o