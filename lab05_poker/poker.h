#ifndef POKER_H
#define POKER_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

struct Card{
    std::string rank;
    std::string suit;
};
 
//REQUIRES: hand contains 5 Cards
//MODIFIES: nothing
//EFFECTS: returns true if hand contains exactly one pair, returns false 
//         otherwise
//NOTE: this is a buggy implementation
 bool has_one_pair(const std::vector<Card> &hand);

 #endif // POKER_H