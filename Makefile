all:
	g++ -std=c++11 tp1.cpp -o tp1
clean:
	rm -f tp1.o tp1
run:
	./tp1 "nba_2016_scores.dat" "output.out" 1