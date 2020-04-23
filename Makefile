all:
	g++ -std=c++11 -O2 -c ./tournament.cpp -o ./tournament.o
	g++ -std=c++11 -O2 -c ./tp1.cpp -o ./tp1.o
	g++ -std=c++11 -O2 -c ./match.cpp -o ./match.o
	g++ -std=c++11 -O2 -c ./team.cpp -o ./team.o
	g++ -o ./tp ./tournament.o ./tp1.o ./match.o ./team.o
clean:
	rm -f *.o
	rm -f tp
run:
	./tp "nba_2016_scores.dat" "output.out" 0