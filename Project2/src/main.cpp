#include "Audit.h"
#include "Ballot.h"
#include "CPL.h"
#include "Entrants.h"
#include "IRV.h"
#include "TieHandler.h"
#include <iostream>
#include <fstream>
#include "PO.h"


int main() {

    std::ifstream inFile;
    std::string line, filename;
    std::vector<std::string> filenames;
    int num_files = 0;

    // Prompt user for file name
    std::cout << "\n||When Entering Files, please input one at a time, not all at once. Thank You.||\n";
    while(1) {

        std::cout << "Please Enter a File Name or 'q' to quit or 'd' for done entering files: ";
        std::cin >> filename;
        if(filename == "q"){
            return 1;
        }
        else if (filename == "d"){
            break;
        }
        inFile.open(filename);
        if(!inFile){
            std::cout << "File Not Found." << std::endl;
        } else {
            std::cout << "Sucessfully added: " << filename << std::endl;
            filenames.emplace_back(filename);
        }
        std::cout << std::endl;
        num_files++;
        inFile.close();
    }

    for (std::string filename : filenames){
        inFile.open(filename);
        getline(inFile, line);  // Reading first line

        if (line == "CPL") {   // CPL
            CPL election = CPL(filename);
            election.TallyVotes();
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
                else{
                    if((((double)election.numEliminated / (double)election.numCandidates)) > .5){
                        election.MajorityChecker();
                        break;
                    } else {
                        election.Eliminate();
                    }
                }
                election.MajorityChecker();
            }
            election.GetWinner();
        }
        else if (line == "PO"){ // PO
        PO election = PO(filename);
        election.TallyVotes();
        if(election.TieChecker()) {
                std::vector<Entrants> tiedWinner = TieHandler(election.GetTiedParties());
                election.SetWinner(tiedWinner);
                election.GetWinner();
            }
            else {
                election.GetWinner();
            }

        }

        inFile.close();
    }    
    std::cout<<"COMPLETE"<<std::endl;
    return 0;
}
