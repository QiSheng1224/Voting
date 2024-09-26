#include "Entrants.h"
#include <iostream>

Entrants::Entrants(std::string name){
    this->name = name;
    this->votes = 0;
}

std::string Entrants::GetName(){
    return this->name;
}

void Entrants::SetName(std::string name){
    this->name = name;
}

int Entrants::GetVotes(){
    return this->votes;
}

void Entrants::AddVote(int vote){
    this->votes += vote;
}

void Entrants::ClearVote(){
    this->votes = 0;
    std::cout << "Current Vote for " << this->name << " is " << this->votes << std::endl;

}

