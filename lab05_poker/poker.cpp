#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "poker.h"
using namespace std;
 
//REQUIRES: hand contains 5 Cards
//MODIFIES: nothing
//EFFECTS: returns true if hand contains exactly one pair, returns false 
//         otherwise
//NOTE: this is a buggy implementation
bool has_one_pair(const vector<Card> &hand){
    assert(hand.size() == 5);
    for(size_t i = 0; i < hand.size(); ++i){
        int count_occur = 0;
        for(size_t j = i; j < hand.size(); ++j){
            if(hand[i].rank == hand[j].rank){
                ++count_occur;
            }  
        }
        if (count_occur > 2){
            return false;
        }  
    }
    return true;
}
