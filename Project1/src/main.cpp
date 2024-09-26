#include "Audit.h"
#include "Ballot.h"
#include "CPL.h"
#include "Entrants.h"
#include "IRV.h"
#include "TieHandler.h"
#include <iostream>
#include <fstream>


int main() {

    std::ifstream inFile;
    std::string filename, line;
    // std::vector<Ballot> ballots;
    int mode;

    // Prompt user for file name
    std::cout << "Please Enter a File Name: ";
    std::cin >> filename;
    inFile.open(filename);

    // Keep prompting until a valid filename is given
    while (!inFile) {
        std::cout << "File Not Found." << std::endl;
        std::cout << "Please Enter a File Name: ";
        std::cin >> filename;
        inFile.open(filename);
    }

    getline(inFile, line);  // Reading first line

    if (line == "CPL") {   // CPL
        CPL election = CPL(filename);
        election.TallyVotes();
        // election.TieChecker();
        if (election.TieChecker()) {
            std::vector<Entrants> tiedWinner = TieHandler(election.GetTiedParties());
            election.SetWinner(tiedWinner);
            election.GetWinner();
        }
        else {
            election.GetWinner();
        }
    }
    else if (line == "IR") {   // IR
        IRV election = IRV(filename);
        election.TallyVotes();
        // CHECK FOR 50%
        election.MajorityChecker();
        while (!election.majCheck) {
            if (election.TieChecker() == true){
                std::vector<Entrants> tiedWinner = TieHandler(election.GetTied());
                election.SetWinner(tiedWinner);
                break;
            }
            else {
                election.Eliminate();
            }
            election.MajorityChecker();
        }
        election.GetWinner();
    }

    inFile.close();
    std::cout<<"COMPLETE"<<std::endl;
    return 0;
}
