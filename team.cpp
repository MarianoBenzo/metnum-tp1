using namespace std;

class Team {

private:
    int id;
    int wins;
    int loses;

public:
    Team() {
        wins = 0;
        loses = 0;
    }

    int getId() {
        return id;
    }

    int getWins() {
        return wins;
    }

    int getLoses() {
        return loses;
    }

    float getRatingWP() {
        return float(wins) / (float(wins) + float(loses));
    }

    void setId(int team_id) {
        id = team_id;
    }

    void addWin() {
        wins += 1;
    }

    void addLoss() {
        loses += 1;
    }

    void print() {
        cout << "Team " << id << " Wins:" << wins << " Loses:" << loses << endl;
    }
};