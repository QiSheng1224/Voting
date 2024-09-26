#include "PO.h"

PO::PO(std::string filename) {
    this->filename = filename;
    
    if (access("AuditFile.txt", F_OK) == 0) {
        // file exists
        std::ofstream outfile("AuditFile.txt", std::ios::app);
        outfile << "-----------------------------------------\n" << std::endl;
        outfile << "-----------------------------------------\n" << std::endl;
        outfile << "Populairty Only Audit\n" << "-----------------------------------------" << std::endl;
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

    std::getline(infile, line); //Skip first line (First Line)
    std::getline(infile, line); // Number of Candidates (Second Line)

    this->numCandidates = std::stoi(line);

    std::getline(infile,line); //The Candidates Names (Third Line)
    std::stringstream iss(line);

    int i = 0;
    while(std::getline(iss, line, ']')) {             // Pushing parties
        if (i == 0){
            line.erase(std::remove(line.begin(), line.end(), '['), line.end());
        }
        else{
            line.erase(0,3); // Strips annoying spaces
        }
        this->parties.emplace_back(Entrants(line));
        i++;
    }

    std::getline(infile, line); // (Fourth Line)
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
        if (cur_ballot.size() < this->parties.size()){ 
            cur_ballot.push_back(0);
        }
        Ballot new_ballot(cur_ballot);

        this->ballot.push_back(new_ballot);
    } // end of while

    infile.close();

}

void PO::UpdAudit(std::string toAppend){
    std::ofstream file(auditFile, std::ios_base::app); // create output file stream with append mode
    file << toAppend; 
    file.close(); 
}

void PO::TallyVotes() {
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

bool PO::TieChecker() {
    int highest_votes = 0;
    for(auto e : this->parties){
        if (e.GetVotes() > highest_votes){
            highest_votes = e.GetVotes();
        }
    }
    for (int j = 0; j<this->parties.size(); j++){
        for (int i = j+1; i<this->parties.size(); i++){
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

std::string PO::GetWinner() {
    std::string toAppend = "";
    Entrants current_highest = this->parties[0];
    int current_index = 0;
    for(int i = 0; i<this->parties.size(); i++){
        if (this->parties[i].GetVotes() > current_highest.GetVotes()){
            current_highest = this->parties[i];
            current_index = i;
        }
    }

    toAppend += "The Candidate(Name, Party): " + current_highest.GetName() + "  has won!\n";
    this->winner = current_highest.GetName();
    UpdAudit(toAppend);
}

std::vector<Entrants> PO::GetTiedParties(){
    return this->tiedParties;
}

void PO::SetWinner(std::vector<Entrants> toUpd){
    this->parties = toUpd;
}

std::vector<Entrants> PO::GetParties() {
    return this->parties;
}