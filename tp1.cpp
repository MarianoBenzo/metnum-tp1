#include <iostream>
#include <vector>
#include "string.h"
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include "team.cpp"
#include "match.cpp"
#include "tournament.cpp"

using namespace std;

Tournament read_input_params(int argc, char *argv[]) {

    if (argc < 4) {
        cout << "Debe ingresar tres parametros de entrada" << endl;
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

    int teams_amount = stoi(line.substr(0, pos));
    int matches_amount = stoi(line.substr(pos, line.length()));

    vector <Match> matches;// = vector<Match> (matches_amount + 1);

    while (!file.eof()) {
        getline(file, line);
        string token = line;
        int token_end = token.length();

        if (token_end > 0) {
            pos = token.find(delimiter);
            int date = stoi(token.substr(0, pos));

            token = token.substr(pos + 1, token_end);
            pos = token.find(delimiter);
            int team_1 = stoi(token.substr(0, pos));

            token = token.substr(pos + 1, token_end);
            pos = token.find(delimiter);
            int team_1_score = stoi(token.substr(0, pos));

            token = token.substr(pos + 1, token_end);
            pos = token.find(delimiter);
            int team_2 = stoi(token.substr(0, pos));

            token = token.substr(pos + 1, token_end);
            pos = token.find(delimiter);
            int team_2_score = stoi(token.substr(0, pos));

            Match match = Match(date, team_1, team_1_score, team_2, team_2_score);

            matches.push_back(match);
        }
    }

    file.close();

    return Tournament(matches_amount, teams_amount, matches);
}

int main(int argc, char *argv[]) {

    Tournament tournament = read_input_params(argc, argv);

    tournament.print();

    return 0;
}
