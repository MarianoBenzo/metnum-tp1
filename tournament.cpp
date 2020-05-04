#include <cmath>
#include <stdio.h>
#include <vector>

#ifndef TEAM_C
#define TEAM_C
#include "team.cpp"
#endif

#ifndef MATCH_C
#define MATCH_C
#include "match.cpp"
#endif

using namespace std;

class Tournament {

private:
    int method;
    int matches_amount;
    int teams_amount;
    vector <Match> matches;
    vector <Team> teams;
    string ranking_output_file;

public:
    Tournament(int m, int ma, int ta, vector <Match> ms, string output_file) {
        method = m;
        matches_amount = ma;
        teams_amount = ta;
        matches = ms;
        ranking_output_file = output_file;
        teams = vector<Team>(teams_amount);

        for (auto it = matches.begin(); it != matches.end(); ++it) {
            Match match = *it;
            int team_1_index = match.getTeam1() - 1;
            int team_2_index = match.getTeam2() - 1;

            teams[team_1_index].setId(match.getTeam1());
            teams[team_2_index].setId(match.getTeam2());

            if (match.getTeam1Score() < match.getTeam2Score()) {
                teams[team_1_index].addLoss();
                teams[team_2_index].addWin();
            } else {
                teams[team_1_index].addWin();
                teams[team_2_index].addLoss();
            };
        }
    }

    int getMatchesAmount() {
        return matches_amount;
    }

    int getTeamsAmount() {
        return teams_amount;
    }

    vector <Match> getMatches() {
        return matches;
    }

    vector <Team> getTeams() {
        return teams;
    }

    vector <tuple<int, double>> getRanking() {
        switch (method) {
            case 0:
                return getRankingCMM();
            case 1:
                return getRankingWP();
            default:
                return getRankingWP();
        }
    }

    vector <tuple<int, double>> getRankingCMM() {

        double eps = 0.00000000000001;

        vector <vector <double>> C;

        // Inicializo C con caso base (sin matches)
        for (int i = 0; i < teams_amount; i++) {
            vector<double> column;
            for (int j = 0; j < teams_amount; j++) {
                if(i == j) {
                    column.push_back(2);
                } else {
                    column.push_back(0);
                }
            }
            C.push_back(column);
        }

        // Lleno C
        for (auto it = matches.begin(); it != matches.end(); ++it) {
            Match match = *it;
            int team_1_index = match.getTeam1() - 1;
            int team_2_index = match.getTeam2() - 1;

            C[team_1_index][team_1_index] += 1;
            C[team_2_index][team_2_index] += 1;

            C[team_1_index][team_2_index] -= 1;
            C[team_2_index][team_1_index] -= 1;
        }

        // Lleno b
        vector <double> b;
        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            double b_team = 1 + ((team.getWins() - team.getLoses()) / 2.0);
            b.push_back(b_team);
        }

        // Hago eliminacion gaussiana en C
        for (int i = 0; i < C.size() - 1; i++) {
            for (int j = i + 1; j < C.size(); j++) {
                double m = double(C[j][i]) / double(C[i][i]);
                for (int k = i; k < C.size() + 1; k++) {
                    if( k == C.size()) {
                        b[j] = abs(b[j] - (m * b[i])) < eps ? 0 : b[j] - (m * b[i]);
                    } else {
                        C[j][k] = abs(C[j][k] - (m * C[i][k])) < eps ? 0 : C[j][k] - (m * C[i][k]);
                    }
                }
            }
        }

        // Calculo r
        vector <double> r = vector<double>(teams_amount);
        for (int i = r.size() - 1; i >= 0; i--) {
            double numerator = b[i];
            for (int j = i + 1; j < r.size(); j++) {
                numerator = abs(numerator - (C[i][j] * r[j])) < eps ? 0 : numerator - (C[i][j] * r[j]);
            }
            r[i] = numerator / C[i][i];
        }

        vector <tuple<int, double>> ranking;

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            int team_index = team.getId() - 1;
            tuple<int, double> teamRating = make_tuple(team.getId(), r[team_index]);
            ranking.push_back(teamRating);
        }

        return ranking;
    }

    vector <tuple<int, double>> getRankingWP() {
        vector <tuple<int, double>> ranking;

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            tuple<int, double> teamRating = make_tuple(team.getId(), team.getRatingWP());
            ranking.push_back(teamRating);
        }

        return ranking;
    }

    void print() {

        cout << "Matches amount: " << matches_amount << endl;

        for (auto it = matches.begin(); it != matches.end(); ++it) {
            Match match = *it;
            match.print();
        }

        cout << "Teams amount: " << teams_amount << endl;

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            team.print();
        }

        cout << "Ranking Ordenado" << method << ": " << endl;

        vector <tuple<int, double>> ranking = getRanking();
        sort(ranking.begin(), ranking.end(),
             [](const tuple<int, double> &a, const tuple<int, double> &b) -> bool {
                 return std::get<1>(a) > std::get<1>(b);
             });

        for (auto it = ranking.begin(); it != ranking.end(); ++it) {
            tuple<int, double> team = *it;
            cout << get<0>(team) << "\t" << get<1>(team) << endl;
        }
    }

    void printRanking() {
        vector <tuple<int, double>> ranking = getRanking();
        for (auto it = ranking.begin(); it != ranking.end(); ++it) {
            tuple<int, double> team = *it;
            cout << get<1>(team) << endl;
        }
    }

    void writeRankingOutput() {
        FILE *fp = fopen(ranking_output_file.c_str(), "w");
        vector <tuple<int, double>> ranking = getRanking();

        if (fp != NULL) {
            for(int i = 0; i < ranking.size(); i++){
                fprintf (fp, "%f\n", get<1>(ranking[i]));
            }
        } else {
            cout << "Error al abrir el archivo: " << ranking_output_file << endl;
            exit(1);
        }

        fclose(fp);
    }
};