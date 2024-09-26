#include "Audit.h"

Audit::Audit(){
    numOfEntrants = 0;
    numOfBallots = 0;
    typeOfVote = "";
    winner = "";
    date = "";
}

void Audit::UpdEntrants(int num) {
    numOfEntrants = num;
}

void Audit::UpdBallot(int num) {
    numOfBallots = num;
}

void Audit::UpdVote(std::string type) {
    typeOfVote = type;
}

void Audit::UpdWinner(std::string winner) {
    winner = winner;
}

void Audit::UpdDate(std::string date) {
    date = date;
}

void Audit::UpdEntrants(Entrants entrant) {
    entrants.push_back(entrant);
}