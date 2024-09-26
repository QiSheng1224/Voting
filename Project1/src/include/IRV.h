#ifndef IRV_H
#define IRV_H

#include "Ballot.h"
#include "Entrants.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <climits>

class IRV{
    protected:
        bool popularity;
        bool majority;

    private:
        std::string AuditFile;
        int numCandidates;
        int numBallots;
        std::vector<Ballot> ballot;
        std::vector<Entrants> candidates;
        std::string winner;
        std::string filename;
        std::vector<Entrants> tiedCandidates;


    public:
        bool tie;
        bool majCheck;

        /**
        * @brief Constructor for the IRV class.
        * @param filename A string representing the name of the file containing the election data.
        */
        IRV(std::string filename);

        /**
        * @brief Appends a string to the audit file.
        * @param toAppend A string to be appended to the audit file.
        */
        void UpdAudit(std::string toAppend);

        /**
        * @brief Tally the votes in the election.
        */
        void TallyVotes();

        /**
        * @brief Eliminate the candidate with the fewest votes.
        */
        void Eliminate();

        /**
        * @brief Check if there is a majority winner in the election.
        */
        void MajorityChecker();

        /**
        * @brief Check if there is a candidate with the most first-choice votes in a popularity contest.
        */
        void CheckPopularity();

        /**
        * @brief Check if a tie has occurred.
        * @return A boolean indicating whether a tie has occurred.
        */
        bool TieChecker();

        /**
        * @brief Returns the name of the winning candidate or party.
        * @return A string representing the name of the winning candidate or party.
        */
        std::string GetWinner();

        /**
        * @brief Updates parties vector.
        */
        void SetWinner(std::vector<Entrants> toUpd);

        /**
        * @brief Gets the vector of tied candidates.
        */
        std::vector<Entrants> GetTied();
};

#endif