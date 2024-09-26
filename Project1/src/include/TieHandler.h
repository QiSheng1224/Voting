#ifndef TIEHANDLER_H
#define TIEHANDLER_H

#include "Entrants.h"
#include <vector>
#include <stdlib.h>

/**
*@brief Handle ties between candidates in an election.
*This function takes a vector of Entrants, and returns a vector of Entrants
*after resolving any ties between the candidates in the input vector.
*@param entrants The vector of Entrants to be processed.
*@return The vector of Entrants after resolving any ties.
*/
std::vector<Entrants> TieHandler(std::vector<Entrants> entrants);

#endif