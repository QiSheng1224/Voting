#include "CPL.h"

CPL::CPL(std::string filename) {
    this->filename = filename;

    if (access("AuditFile.txt", F_OK) == 0) {
        // file exists
        std::ofstream outfile("AuditFile.txt", std::ios::app);
        outfile << "-----------------------------------------\n" << std::endl;
        outfile << "-----------------------------------------\n" << std::endl;
        outfile << "Closed Party Listing Audit\n" << "-----------------------------------------" << std::endl;
        outfile.close();
    } else {
        // file doesn't exist
        std::ofstream outfile ("AuditFile.txt");
        outfile << "Closed Party Listing Audit\n" << "-----------------------------------------" << std::endl;
        outfile.close();
    }
    

    this->auditFile = "AuditFile.txt";

    std::ifstream infile(filename);
    std::string line; 

    std::getline(infile, line);     //Skip first line
    std::getline(infile, line);     // Number of parties

    this->numParties =  std::stoi(line);

    std::getline(infile, line);     // The parties
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // Strips annoying spaces
    std::stringstream iss(line);

    while(std::getline(iss, line, ',')) {             // Pushing parties
        this->parties.emplace_back(Entrants(line));
    }

    for (int i = 0; i < numParties; i++ ){       // Pushing all the names
        std::getline(infile, line);
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // Strips annoying spaces
        std::stringstream iss(line);
        std::vector<std::string> newVec;
        while(std::getline(iss, line, ',')) {             // Pushing parties
            newVec.push_back(line);
        };
        this->partyCandidates.push_back(newVec);

    }

    std::getline(infile, line);     // Number of seats
    this->numSeats =  std::stoi(line);

    std::getline(infile, line);
    this->numBallots = std::stoi(line);     // Number of ballots

    //Initializes Ballots
    while (std::getline(infile, line)) {
        std::vector<int> cur_ballot;
        std::stringstream iss(line);
        std::string value;

        while (std::getline(iss, value, ',')) {
            if (value.empty()) {
                cur_ballot.push_back(0);
            } else {
                cur_ballot.push_back(std::stoi(value));
            }
        } // end of while

        // Handles the case when the last preference is empty, not read properly
        if (cur_ballot.size() < this->numParties){
            cur_ballot.push_back(0);
        }
        Ballot new_ballot(cur_ballot);

        this->ballot.push_back(new_ballot);
    } // end of while

    infile.close();

}

void CPL::UpdAudit(std::string toAppend){
    std::ofstream file(auditFile, std::ios_base::app); // create output file stream with append mode
    file << toAppend; 
    file.close(); 
}

void CPL::TallyVotes() {
    for (int i = 0; i<numBallots; i++){
        std::vector<int> current = ballot[i].GetRank();
        for (int j = 0; j<current.size(); j++){
            if (current[j] == 1) {    // Tally a vote to person with 1 as preference
                this->parties[j].AddVote(1);
                std::string toAppend = "A vote has been given to " + this->parties[j].GetName() +"\n";
                UpdAudit(toAppend);
            }
        }
    }
    std::string toAppend = "-----------------------------------------\n";
    UpdAudit(toAppend);

}

bool CPL::TieChecker() {
    int highest_votes = 0;
    for(auto e : this->parties){
        if (e.GetVotes() > highest_votes){
            highest_votes = e.GetVotes();
        }
    }
    for (int j = 0; j<this->numParties; j++){
        for (int i = j+1; i<this->numParties; i++){
            if ((this->parties[j].GetVotes() == this->parties[i].GetVotes()) && (this->parties[j].GetVotes() == highest_votes)){
                std::string toAppend = "A tie has occured between " + this->parties[j].GetName() + " & " + this->parties[i].GetName() + "\n" + "-----------------------------------------\n";
                this->tiedParties.emplace_back(this->parties[i]);
                this->tiedParties.emplace_back(this->parties[j]);
                UpdAudit(toAppend);
                this->tie = true;

                std::vector<std::vector<std::string>> newCands;
                newCands.emplace_back(this->partyCandidates[i]);
                newCands.emplace_back(this->partyCandidates[j]);
                this->partyCandidates = newCands;
                return true;
            }
        }
    }
    return false;
}

std::string CPL::GetWinner() {

    std::string toAppend = "";
    Entrants current_highest = this->parties[0];
    int current_index = 0;

    if(this->tie){
        std::vector<std::string> temp;
        int first;
        int second;
        int seats_remain = this->numSeats;
        toAppend += "The " + this->winner + " party has won!\n";
        for (int i = 0; i<tiedParties.size(); i++){
            if(tiedParties[i].GetName() == winner){
                first = i;
            }
            else {
                second = i;
            }
        }
        while (seats_remain > 0 ){
            //Give seats to first party
            for (auto cand : this->partyCandidates[first]) {
                toAppend += "Seat has been awarded to: " + cand + "\n";
                seats_remain--;
                if(seats_remain <= 0){
                    break;
                }
            }

            if(seats_remain <= 0){
                break;
            }
            //Give seats to second party
            for (auto cand : this->partyCandidates[second]) {
                toAppend += "Seat has been awarded to: " + cand + "\n";
                seats_remain--;
                if(seats_remain <= 0){
                    break;
                }
            }

            if(seats_remain <= 0){
                break;
            }
            //Break b/c no more candidates to give seats to
            return this->winner;
            break;
        }

    } 
    else {
        for(int i = 0; i<this->parties.size(); i++){
        if (this->parties[i].GetVotes() > current_highest.GetVotes()){
            current_highest = this->parties[i];
            current_index = i;
            }
        }
        toAppend += "The " + current_highest.GetName() + " party has won!\n";
        this->winner = current_highest.GetName();
        for(int i = 0; i<partyCandidates[current_index].size(); i++){
            if(i < partyCandidates[current_index].size()) {
                // std::cout<< current_index << std::endl;
                toAppend += "Seat has been awarded to: " + partyCandidates[current_index][i] + "\n";
            }
        }
    }

    UpdAudit(toAppend);
    return this->winner;
}

std::vector<Entrants> CPL::GetTiedParties(){
    return this->tiedParties;
}

void CPL::SetWinner(std::vector<Entrants> toUpd){
    this->winner = toUpd[0].GetName();
}

std::vector<Entrants> CPL::GetParties() {
    return this->parties;
}