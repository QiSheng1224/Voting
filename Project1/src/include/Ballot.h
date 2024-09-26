#ifndef BALLOT_H
#define BALLOT_H

#include <vector>

class Ballot{
    protected:
    std::vector<int> rank;

    public:
    /**
    * @brief Constructor for the Ballot class.
    * @param rank The vector of integers representing the ranking of candidates on the ballot.
    */
    Ballot(std::vector<int> rank);
    
    /**
    * @brief Returns the vector of integers representing the ranking of candidates on the ballot.
    * @return The vector of integers representing the ranking of candidates on the ballot.
    */
    std::vector<int> GetRank();

    /**
    * @brief Returns a const iterator to the beginning of the rank vector.
    * @return A const iterator to the beginning of the rank vector.
    */
    std::vector<int>::const_iterator begin() const { return rank.begin(); }

    /**
    * @brief Returns a const iterator to the end of the rank vector.
    * @return A const iterator to the end of the rank vector.
    */
    std::vector<int>::const_iterator end() const { return rank.end(); }
};

#endif