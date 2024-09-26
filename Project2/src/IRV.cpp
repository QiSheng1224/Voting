#include "IRV.h"

IRV::IRV(std::string filename){
    this->filename = filename;
    this->numEliminated = 0;
    this->majCheck = false;

    if (access("AuditFile.txt", F_OK) == 0) {
        // file exists
        std::ofstream outfile("AuditFile.txt", std::ios::app);
        outfile << "-----------------------------------------\n" << std::endl;
        outfile << "-----------------------------------------\n" << std::endl;
        outfile << "Instant Runoff Audit\n" << "-----------------------------------------" << std::endl;
        outfile.close();
    } else {
        // file doesn't exist
        std::ofstream outfile ("AuditFile.txt");
        outfile << "Instant Runoff Audit\n" << "-----------------------------------------" << std::endl;
        outfile.close();
    }

    this->AuditFile = "AuditFile.txt";

    // Open the input file
    std::ifstream infile(filename);
    std::string line; 

    std::getline(infile, line);
    std::getline(infile, line);
    this->numCandidates = std::stoi(line);  // Number of Candiddates
    std::getline(infile, line);

    line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // Strips annoying spaces
    std::stringstream iss(line);

    while(std::getline(iss, line, ',')) {             // Pushing candidates
        this->candidates.emplace_back(Entrants(line));
    }

    std::getline(infile, line);
    this->numBallots = std::stoi(line);     // Number of ballots

    //Initializes Ballots
    while (std::getline(infile, line)) {
        std::vector<int> cur_rank;
        std::stringstream iss(line);
        std::string value;

        while (std::getline(iss, value, ',')) {
            if (value.empty()) {
                cur_rank.push_back(0);
            } else {
                cur_rank.push_back(std::stoi(value));
            }
        } // end of while

        // Handles the case when the last preference is empty, not read properly
        if (cur_rank.size() < this->numCandidates){
            cur_rank.push_back(0);
        }
        Ballot new_ballot(cur_rank);

        this->ballot.push_back(new_ballot);
    } // end of while

    infile.close();
}

void IRV::UpdAudit(std::string toAppend){
    std::ofstream file(AuditFile, std::ios_base::app); // create output file stream with append mode
    file << toAppend; 
}

void IRV::TallyVotes(){
    for (int i = 0; i<numBallots; i++){
        std::vector<int> current = ballot[i].GetRank();
        for (int j = 0; j<current.size(); j++){
            if((this->candidates[j].GetName() != "ELIMINATED") && (current[j] == 1)){    // Tally a vote to person with 1 as preference
                this->candidates[j].AddVote(1);
                std::string toAppend = "A vote has been given to " + this->candidates[j].GetName() +"\n";
                UpdAudit(toAppend);
            }
        }
    }
    std::string toAppend = "-----------------------------------------\n";
    UpdAudit(toAppend);

}


bool IRV::TieChecker(){
    int max_votes = 0;
    std::vector<Entrants> top_candidates;

    for (auto& candidate : this->candidates) {
        int votes = candidate.GetVotes();
        if (votes > max_votes) {
            top_candidates.clear();
            top_candidates.push_back(candidate);
            max_votes = votes;
        } else if (votes == max_votes) {
            top_candidates.push_back(candidate);
        }
    }
    if(top_candidates.size() > 1) { //There are at least 2 top candidates, so must be a tie
    // If there is a tie among the top candidates
        std::string toAppend = "There is a tie among the top candidates: ";
        for (auto candidate : top_candidates) {
            toAppend += candidate.GetName() + ", ";
            toAppend += "votes: " + std::to_string(candidate.GetVotes()) + " | ";
            this->tiedCandidates.push_back(candidate);
        }
        toAppend += "\n";
        UpdAudit(toAppend);
        this->majCheck = false;
        return true;
    }
    return false;
}

void IRV::Eliminate(){  // Redistribute is built in here
    
    int lowestIndex = 0;
    int lowest_score = INT_MAX;
    int numVote = 0;
    for (int i = 0; i < this->candidates.size(); i++){
        if((this->candidates[i].GetName() != "ELIMINATED") && (this->candidates[i].GetVotes() < lowest_score)){
            lowestIndex = i;
            lowest_score = this->candidates[i].GetVotes();
        }
    }
    
    for(auto& one_ballot : this->ballot){ // add '&' to reference one_ballot
        std::vector<int> temp = one_ballot.GetRank();
        if(temp[lowestIndex] == 1){
            temp[lowestIndex] = -1;
        }  
        for (int i = 0; i < temp.size(); i++){
            if(temp[i] != 0 && temp[lowestIndex] == -1){
                temp[i] -= 1;
            }
        } 
        one_ballot.SetRank(temp); // add this line to save changes back to one_ballot
    }                              

    for (auto& candidate : this->candidates){
        candidate.ClearVote();
    }
    std::string toAppend = "The candidate: " + this->candidates[lowestIndex].GetName() + " has been eliminated.\n" + "-----------------------------------------\n";
    UpdAudit(toAppend);
    //misc/IRVTEST.csv
    this->candidates[lowestIndex].SetName("ELIMINATED");
    this->numEliminated++;
    TallyVotes();
}

void IRV::MajorityChecker(){
    int goal = (numBallots / 2) + 1;
    int max_votes = 0;
    std::vector<Entrants> top_candidates;

    // Find the candidates with the most votes
    for (auto& candidate : this->candidates) {
        int votes = candidate.GetVotes();
        if (votes > max_votes) {
            top_candidates.clear();
            top_candidates.push_back(candidate);
            max_votes = votes;
        } else if (votes == max_votes) {
            top_candidates.push_back(candidate);
        }
    }

    if (top_candidates.size() == 1 && max_votes >= goal) {
        // If there is only one candidate with the most votes
        if (max_votes >= goal) {
            // If the top candidate has a majority
            this->winner = top_candidates[0].GetName();
            std::string toAppend = "The candidate " + this->winner + " has a majority with " + std::to_string(max_votes) + " votes.\n" + "-----------------------------------------\n";
            UpdAudit(toAppend);
            this->majCheck = true;
        }
    }
    else if (((double)this->numEliminated / (double)this->numCandidates) > .5) {
        std::cout<<"Exited: Because more than half of the canadidates were eliminated." << std::endl;
        this->winner = top_candidates[0].GetName();
        std::string toAppend = "The candidate " + this->winner + " has the most votes with " + std::to_string(max_votes) + " votes.\n" + "-----------------------------------------\n";
        UpdAudit(toAppend);
        this->majCheck = true;
    }
    else if (this->tie == true){
        // If there is a tie among the top candidates
        std::string toAppend = "There is a tie among the top candidates: ";
        for (auto candidate : top_candidates) {
            toAppend += candidate.GetName() + ", ";
            toAppend += "votes: " + std::to_string(candidate.GetVotes()) + " | ";
            this->tiedCandidates.push_back(candidate);
        }
        toAppend += "\n";
        UpdAudit(toAppend);
        this->majCheck = false;
    }
}

std::string IRV::GetWinner(){
    
    std::string toAppend = "-----------------------------------------\n";
    UpdAudit(toAppend);
    toAppend = "The Candidate: " + this->winner+ " has won.\n" + "Congradulations!\n";
    UpdAudit(toAppend);
    return this->winner;
}

void IRV::SetWinner(std::vector<Entrants> toUpd){
    this->winner = toUpd[0].GetName();
}

std::vector<Entrants> IRV::GetTied(){
    return this->tiedCandidates;
}


std::vector<Entrants> IRV::GetCandidates() {
    return this->candidates;
}

int IRV::GetNumBallots() const {
    return this->numBallots;
}


std::string IRV::getFilename() const {
    return this->filename;
}