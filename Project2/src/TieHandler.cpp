#include "TieHandler.h"
#include <iostream>
#include <cstdlib>

std::vector<Entrants> TieHandler(std::vector<Entrants> entrants){

        int highest = 0;
        int highest_index = 0;
        std::vector<Entrants> vec;
        srand((unsigned) time(NULL));
        
        std::vector<int> coinFlip(entrants.size() , 0);
        
        for (int i = 0; i < (10 * entrants.size()); i++){
            int random = rand() % entrants.size();
            coinFlip[random] += 1;
        }

        for (int i = 0; i < entrants.size(); i++){
            if(coinFlip[i] > highest){
                highest = coinFlip[i];
                highest_index = i;
            }
        }
        vec.emplace_back(entrants[highest_index]);
        return vec;
}