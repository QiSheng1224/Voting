#ifndef CPL_H
#define CPL_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Entrants.h"
#include "Ballot.h"
#include <sstream>
#include <algorithm>
#include <climits>
#include <unistd.h>


class CPL{
    protected:
        std::vector<Entrants> parties;
        int numParties;
        int numSeats;
        std::string filename;
        std::vector<std::vector<std::string>> partyCandidates;
        std::vector<Entrants> tiedParties;

    private:
        std::string auditFile;
        std::vector<Ballot> ballot;
        std::string winner;
        int numBallots;

    public:
        bool tie;
        
        /**
        * @brief Constructor for the CPL class.
        * @param filename The name of the file containing the election data.
        */
        CPL(std::string filename);

        /**
        * @brief Appends a string to the audit file.
        * @param toAppend The string to append to the audit file.
        */
        void UpdAudit(std::string toAppend);

        /**
        * @brief Tally the votes and determine the winner of the election.
        */
        void TallyVotes();

        /**
        * @brief Checks if there is a tie in the election.
        * @return True if there is a tie, false otherwise.
        */
        bool TieChecker();

        /**
        * @brief Returns the winner of the election.
        * @return A string representing the winning party in the election.
        */
        std::string GetWinner();

        /**
        * @brief Get the TiedParties vector.
        * @return Returns a vector of the parties that are tied.
        */
        std::vector<Entrants> GetTiedParties();
        
        /**
        * @brief Updates parties vector
        * @param toUpd The vectors of entrants to update
        */
        void SetWinner(std::vector<Entrants> toUpd);

        /**
        * @brief Gets the parties to be used.
        * @return Returns the vector of parties.
        */
        std::vector<Entrants> GetParties();
};

#endif