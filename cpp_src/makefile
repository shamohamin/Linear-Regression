
run.out: main.o data_reader.o linear_regression.o
	g++ main.o data_reader.o linear_regression.o -o run.out

data_reader.o: data_reader.cpp
	g++ -c data_reader.cpp

main.o: main.cpp
	g++ -c main.cpp

linear_regression.o: linear_regression.cpp
	g++ -c linear_regression.cpp

clean:
	rm -rf *.o *.out

