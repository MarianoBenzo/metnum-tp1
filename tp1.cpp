#include <iostream>
#include <vector>
#include "string.h"
#include <stdlib.h>
#include <iomanip>
#include <fstream>

using namespace std;

/* ESTRUCTURAS */
struct Match {
	int date;
	int player_1;
	int player_1_points;
	int player_2;
	int player_2_points;

	// Constructor por defecto
	Match(): date(0), player_1(0), player_1_points(0), player_2(0), player_2_points(0) {}
	// Constructor
	Match(int a, int b, int c, int d, int e): date(a), player_1(b), player_1_points(c), player_2(d), player_2_points(e) {}
};

struct Player {
	int player_id;
	int points;
	int wins;
	int loses;

	Player(): player_id(0), points(0), wins(0), loses(0) {}
	Player(int a, int b, int c, int d): player_id(a), points(b), wins(c), loses(d) {}
};

/* VARIABLES GLOBALES */

int matchs_amount;
int players_amount;
vector<Match> matchs;
vector<Player> players;

/* FUNCIONES */

void print_players() {
	for (auto it = players.begin() ; it != players.end(); ++it) {
		Player player = *it;
		cout << "Player " << player.player_id << " Points:" << player.points << " Wins:" << player.wins << " loses:" << player.loses << endl;
	}
}

void print_matchs() {
	for (auto it = matchs.begin() ; it != matchs.end(); ++it) {
		Match match = *it;
		cout << "Match " << match.date << " " << match.player_1 << " vs " << match.player_2 << ": " << match.player_1_points << " " << match.player_2_points << endl;
	}
}

void set_player_data(Match match) {
	players[match.player_1].player_id = match.player_1;
	players[match.player_1].points += match.player_1_points;
	players[match.player_1].loses += match.player_1_points < match.player_2_points ? 1 : 0;
	players[match.player_1].wins += match.player_1_points > match.player_2_points ? 1 : 0;

	players[match.player_2].player_id = match.player_2;
	players[match.player_2].points += match.player_2_points;
	players[match.player_2].loses += match.player_2_points < match.player_1_points ? 1 : 0;
	players[match.player_2].wins += match.player_2_points > match.player_1_points ? 1 : 0;
}

void read_input_params(int argc, char *argv[]) {

	if (argc < 4) {
		cout << "Debe ingresar tres parametros de entrada" <<endl;
		exit(1);
	} 

	string stats_input_path = argv[1];
	string ranking_output_path = argv[2];
	int method = atoi(argv[3]);

	string line;
	ifstream file;
	string delimiter = " ";
	
	file.open(stats_input_path);
	if (!file) {
		cout << "Error al abrir el archivo: " << stats_input_path << endl;
		exit(1);
	}

	getline(file, line);
	int pos = line.find(delimiter);

	players_amount = stoi(line.substr(0, pos));
	matchs_amount = stoi(line.substr(pos, line.length()));

	players = vector<Player> (players_amount+1);

	while (! file.eof()) {
		getline(file, line);
		string token = line;
		int token_end = token.length();

		if (token_end > 0) {
			pos = token.find(delimiter);
			int date = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_1 = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_1_points = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_2 = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_2_points = stoi(token.substr(0, pos));

			Match match = Match(date, player_1, player_1_points, player_2, player_2_points);
			matchs.push_back(match);

			set_player_data(match);
		}
	}

	file.close();
}

int main(int argc, char *argv[]) {

	read_input_params(argc, argv);

	cout << "Players amount: " << players_amount << endl;
	cout << "Matchs amount: " << matchs_amount << endl;

	print_matchs();
	print_players();

	return 0;
}
