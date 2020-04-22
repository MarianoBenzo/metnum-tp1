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
        vector <tuple<int, float>> ranking;

        for (auto it = teams.begin(); it != teams.end(); ++it) {
            Team team = *it;
            tuple<int, float> teamRating = make_tuple(team.getId(), team.getRatingWP());
            ranking.push_back(teamRating);
        }

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

        cout << "Ranking " << method << ": " << endl;

        vector <tuple<int, float>> ranking = getRanking();
        for (auto it = ranking.begin(); it != ranking.end(); ++it) {
            tuple<int, float> team = *it;
            cout << get<0>(team) << " " << get<1>(team) << endl;
        }
    }
};