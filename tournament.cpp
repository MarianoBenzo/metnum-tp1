#include <cmath>

using namespace std;

class Tournament {

private:
    int method;
    int matches_amount;
    int teams_amount;
    vector <Match> matches;
    vector <Team> teams;

public:
    Tournament(int m, int ma, int ta, vector <Match> ms) {
        method = m;
        matches_amount = ma;
        teams_amount = ta;
        matches = ms;
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

    vector <tuple<int, float>> getRanking() {
        switch (method) {
            case 0:
                return getRankingCMM();
            case 1:
                return getRankingWP();
            default:
                return getRankingWP();
        }
    }

    vector <tuple<int, float>> getRankingCMM() {

        float eps = 0.000001;

        vector <vector <float>> C;

        // Inicializo C con caso base (sin matches)
        for (int i = 0; i < teams_amount; i++) {
            vector<float> column;
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
        vector <float> b;
        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            float b_team = 1 + ((team.getWins() - team.getLoses()) / 2.0);
            b.push_back(b_team);
        }

        // Hago eliminacion gaussiana en C
        for (int i = 0; i < C.size() - 1; i++) {
            for (int j = i + 1; j < C.size(); j++) {
                float m = float(C[j][i]) / float(C[i][i]);
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
        vector <float> r = vector<float>(teams_amount);
        for (int i = r.size() - 1; i >= 0; i--) {
            float numerator = b[i];
            for (int j = i + 1; j < r.size(); j++) {
                numerator = abs(numerator - (C[i][j] * r[j])) < eps ? 0 : numerator - (C[i][j] * r[j]);
            }
            r[i] = numerator / C[i][i];
        }

        vector <tuple<int, float>> ranking;

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            int team_index = team.getId() - 1;
            tuple<int, float> teamRating = make_tuple(team.getId(), r[team_index]);
            ranking.push_back(teamRating);
        }
/*
        // Print C
        cout << "C: " << endl;
        for (int i = 0; i < C.size(); i++) {
            for (int j = 0; j < C[i].size(); j++)
                cout << C[i][j] << "\t";
            cout << endl;
        }

        // Print b
        cout << "b: " << endl;
        for (auto it = b.begin(); it != b.end(); ++it) {
            float b_team = *it;
            cout << b_team << endl;
        }

        // Print r
        cout << "r: " << endl;
        for (auto it = r.begin(); it != r.end(); ++it) {
            float r_team = *it;
            cout << r_team << endl;
        }
*/
        return ranking;
    }

    vector <tuple<int, float>> getRankingWP() {
        vector <tuple<int, float>> ranking;

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            tuple<int, float> teamRating = make_tuple(team.getId(), team.getRatingWP());
            ranking.push_back(teamRating);
        }

        sort(ranking.begin(), ranking.end(),
             [](const tuple<int, float> &a, const tuple<int, float> &b) -> bool {
                 return std::get<1>(a) > std::get<1>(b);
             });

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

        vector <tuple<int, float>> ranking = getRanking();
        sort(ranking.begin(), ranking.end(),
             [](const tuple<int, float> &a, const tuple<int, float> &b) -> bool {
                 return std::get<1>(a) > std::get<1>(b);
             });

        for (auto it = ranking.begin(); it != ranking.end(); ++it) {
            tuple<int, float> team = *it;
            cout << get<0>(team) << "\t" << get<1>(team) << endl;
        }
    }

    void printRanking() {
        vector <tuple<int, float>> ranking = getRanking();
        for (auto it = ranking.begin(); it != ranking.end(); ++it) {
            tuple<int, float> team = *it;
            cout << get<1>(team) << endl;
        }
    }
};