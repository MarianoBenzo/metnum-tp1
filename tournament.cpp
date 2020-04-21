using namespace std;

class Tournament {

private:
    int matches_amount;
    int teams_amount;
    vector <Match> matches;
    vector <Team> teams;

public:
    Tournament(int ma, int ta, vector <Match> ms) {
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

    void print() {

        cout << "Teams amount: " << teams_amount << endl;
        cout << "Matches amount: " << matches_amount << endl;

        for (auto it = matches.begin(); it != matches.end(); ++it) {
            Match match = *it;
            match.print();
        }

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            team.print();
        }
    }
};