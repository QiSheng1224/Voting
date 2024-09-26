#include "CPL.h"

CPL::CPL(std::string filename) {
    this->filename = filename;

    std::ofstream outfile ("AuditFile.txt");
    outfile << "Closed Party Listing Audit\n" << "-----------------------------------------" << std::endl;
    outfile.close();

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
        }
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

    // TESTING PURPOSES
    // for (auto bal : this->ballot) {
    //     for (auto element : bal) {
    //         std::cout << element << ", ";
    //     }
    //     std::cout<<"Bal Size: "<< bal.GetRank().size() << std::endl;
    //     std::cout << std::endl;
    // }

    // std::cout <<"Num Seats: " << this->numSeats <<"Num Parties: "<< this->numParties << "NUM BALLOTS: " <<this->numBallots << std::endl;

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

    //TESTING PURPOSES
    // for (auto party : this->parties){
    //     std::cout << "Votes Towards " << party.GetName() << ": " << party.GetVotes() << std::endl;
    // }
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
                this->tiedParties.emplace_back(this->parties[j]);
                this->tiedParties.emplace_back(this->parties[i]);
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
    for(int i = 0; i<this->parties.size(); i++){
        if (this->parties[i].GetVotes() > current_highest.GetVotes()){
            current_highest = this->parties[i];
            current_index = i;
        }
    }

    toAppend += "The " + current_highest.GetName() + " party has won!\n";
    this->winner = current_highest.GetName();
    for(int i = 0; i<numSeats; i++){
        if(i < partyCandidates[current_index].size()){
            toAppend += "Seat has been awarded to: " + partyCandidates[current_index][i] + "\n";
        }
    }
    UpdAudit(toAppend);
}

std::vector<Entrants> CPL::GetTiedParties(){
    return this->tiedParties;
}

void CPL::SetWinner(std::vector<Entrants> toUpd){
    this->parties = toUpd;
}