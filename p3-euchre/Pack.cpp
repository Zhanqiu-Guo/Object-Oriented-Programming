// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Pack.h"
#include <cassert>
#include <iostream>
using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(){
    for (int i = 0; i < 4; i++) {   
        for (int j = 0; j < 6; j++) {
            string rank = RANK_NAMES_BY_WEIGHT[j+7];
            string suit = SUIT_NAMES_BY_WEIGHT[i];
            Card card(rank, suit);
            this->cards[i*6+j] = card;
        } 
    }
    this->next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input){
    string rank, suit, of;
    for (int i = 0; i < PACK_SIZE; ++i){
	   pack_input >> rank >> of >> suit;
	   Card card(rank, suit);
	   this->cards[i] = card;
    }
    this->next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    return this->cards[this->next++];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    this->next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){
    array<Card, PACK_SIZE> temp;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 12; j++){
            temp[2*j+1] = this->cards[j];
            temp[2*j] = this->cards[j+12];
            }
        for (int k = 0; k < PACK_SIZE; k++){
        this->cards[k] = temp[k];
        }
    }
    this->next = 0;
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const{
    if (this->next == PACK_SIZE) return true;
    else return false;
}
