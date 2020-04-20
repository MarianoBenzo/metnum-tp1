#include <iostream>
#include <vector>
#include "string.h"
#include <stdlib.h>
#include <iomanip>
#include <fstream>

using namespace std;

/* ESTRUCTURAS */
struct Player{
	int team_id;
	int points;

	// Constructor por defecto
	Player(): team_id(0), points(0){
	}

	// Constructor
	Player(int a, int b): team_id(a), points(b){
	}
};

/* VARIABLES GLOBALES */

int matchs_amount;
int players_amount;
vector<Player> players;

/* FUNCIONES */

void print_players() {
	for (auto it = players.begin() ; it != players.end(); ++it) {
		Player player = *it;
		cout << "Team id: " << player.team_id << " - Points: " << player.points << endl;
	}
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

	while (! file.eof()) {
		getline(file, line);
		string token = line;
		int token_end = token.length();

		if (token_end > 0) {
			pos = token.find(delimiter);
			int date = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_i = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_i_points = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_j = stoi(token.substr(0, pos));

			token = token.substr(pos + 1, token_end);
			pos = token.find(delimiter);
			int player_j_points = stoi(token.substr(0, pos));

			players.push_back(Player(player_i, player_i_points));
			players.push_back(Player(player_j, player_j_points));
		}
	}

	file.close();
}

int main(int argc, char *argv[]) {

	read_input_params(argc, argv);

	cout << "Players amount: " << players_amount << endl;
	cout << "Matchs amount: " << matchs_amount << endl;
	print_players();

	return 0;
}
