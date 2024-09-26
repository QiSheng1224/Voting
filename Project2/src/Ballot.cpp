#include "Ballot.h"

Ballot::Ballot(std::vector<int> rank){
    this->rank = rank;
}

std::vector<int> Ballot::GetRank() {
    return this->rank;
}

void Ballot::SetRank(std::vector<int> rank) {
   this->rank = rank;
}