#ifndef AUDIT_H
#define AUDIT_H

#include <vector>
#include "Entrants.h"

class Audit{
    protected:
        int numOfEntrants;
        int numOfBallots;

        std::string typeOfVote;
        std::string winner;
        std::string date;

        std::vector<Entrants> entrants;

    public:
        /**
        * @brief Prints the audit information.
        */
        void PrintAudit();
        /**
        * @brief Default constructor for the Audit class.
        */
        Audit();

        /**
        * @brief Returns the number of entrants in the election.
        * @return The number of entrants in the election.
        */
        int GetEntrants(){return numOfEntrants;}

        /**
        * @brief Updates the number of entrants in the election.
        * @param num The new number of entrants.
        */
        void UpdEntrants(int num);

        /**
        * @brief Updates the number of ballots cast in the election.
        * @param num The new number of ballots cast.
        */
        void UpdBallot(int num);

        /**
        * @brief Updates the type of vote used in the election.
        * @param type The new type of vote.
        */
        void UpdVote(std::string type);

        /**
        * @brief Updates the winner of the election.
        * @param winner The new winner of the election.
        */
        void UpdWinner(std::string winner);

        /**
        * @brief Updates the date of the election.
        * @param date The new date of the election.
        */
        void UpdDate(std::string date);

        /**
        * @brief Adds an Entrants object to the vector of candidates.
        * @param entrant The Entrants object to add.
        */
        void UpdEntrants(Entrants entrant);
};

#endif