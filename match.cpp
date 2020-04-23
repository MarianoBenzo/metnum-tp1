#include <iostream>
using namespace std;

class Match {

private:
    int date;
    int team_1;
    int team_1_score;
    int team_2;
    int team_2_score;

public:
    Match(int d, int t1, int t1_score, int t2, int t2_score) {
        date = d;
        team_1 = t1;
        team_1_score = t1_score;
        team_2 = t2;
        team_2_score = t2_score;
    }

    int getDate() {
        return date;
    }

    int getTeam1() {
        return team_1;
    }

    int getTeam1Score() {
        return team_1_score;
    }

    int getTeam2() {
        return team_2;
    }

    int getTeam2Score() {
        return team_2_score;
    }

    void print() {
        cout << "Match " << date << " " << team_1 << " vs " << team_2 << ": " << team_1_score << " " << team_2_score
             << endl;
    }
};