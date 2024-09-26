#ifndef ENTRANTS_H
#define ENTRANTS_H

#include <string>

class Entrants{
    public:
        /*
        * @brief Constructor for the Entrants class.
        * @param name The name of the party or candidate.
        */
        Entrants(std::string name);

        /**
        * @brief Returns the name of the party or candidate.
        * @return A string representing the name of the party or candidate.
        */
        std::string GetName();

        /**
        * @brief Sets the name of the party or candidate.
        * @param name A string representing the name of the party or candidate.
        */
        void SetName(std::string name);

        /**
        * @brief Returns the number of votes received by the party or candidate.
        * @return An integer representing the number of votes received.
        */
        int GetVotes();

        /**
        * @brief Adds a vote to the vote count of the party or candidate.
        * @param vote An integer representing the number of votes to add.
        */
        void AddVote(int vote);

        /**
        * @brief Sets a candidate vote to zero.
        */
        void ClearVote();

    private:
        std::string name;
        int votes;
};

#endif