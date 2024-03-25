// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
//EFFECTS Initializes Card to the Two of Spades
Card::Card() : rank(Card::RANK_TWO), suit(Card::SUIT_SPADES){}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in)
: rank(rank_in), suit(suit_in){
    assert(rank_in == RANK_TWO || rank_in == RANK_THREE || rank_in == RANK_FOUR
        || rank_in == RANK_FIVE || rank_in == RANK_SIX || rank_in == RANK_SEVEN
        || rank_in == RANK_EIGHT || rank_in == RANK_NINE || rank_in == RANK_TEN
        || rank_in == RANK_JACK || rank_in == RANK_QUEEN
        || rank_in == RANK_KING || rank_in == RANK_ACE);
    assert(suit_in == SUIT_SPADES || suit_in == SUIT_HEARTS
        || suit_in == SUIT_CLUBS || suit_in == SUIT_DIAMONDS);
}

//EFFECTS Returns the rank
std::string Card::get_rank() const{
    return this->rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const{
    return this->suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const{
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS 
        || trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    if (this->is_left_bower(trump)) return trump;
    else return get_suit();
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const{
    if (this->get_rank() == RANK_JACK || this->get_rank() == RANK_QUEEN
        || this->get_rank() == RANK_KING || this->get_rank() == RANK_ACE){
        return true;
    }
    else return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const{
    assert(trump == SUIT_SPADES || trump == SUIT_HEARTS
        || trump == SUIT_CLUBS || trump == SUIT_DIAMONDS);
    if (this->get_rank() == RANK_JACK && this->get_suit() == trump){
        return true;
    }
    else return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const{
    if (this->get_rank() == RANK_JACK){
        if ((trump == SUIT_CLUBS && this->get_suit() == SUIT_SPADES)
            || (trump == SUIT_DIAMONDS && this->get_suit() == SUIT_HEARTS)
            || (trump == SUIT_HEARTS && this->get_suit() == SUIT_DIAMONDS)
            || (trump == SUIT_SPADES && this->get_suit() == SUIT_CLUBS)){
            return true;
        }
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const{
    if (this->get_suit() == trump ||this->is_left_bower(trump)){
        return true;
    } 
    else return false;
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
    int lhs_rank, rhs_rank;
    for (int i = 0; i < NUM_RANKS; i++){
	   if (lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) lhs_rank = i;
	   if (rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i]) rhs_rank = i;
    }
    if (lhs_rank < rhs_rank) return true;
    else if (lhs_rank > rhs_rank) return false;
    else {
        int lhs_suit, rhs_suit;
        for (int i = 0; i < NUM_SUITS; i++){
            if (lhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) lhs_suit = i;
            if (rhs.get_suit() == SUIT_NAMES_BY_WEIGHT[i]) rhs_suit = i;
        }
        if (lhs_suit < rhs_suit) return true;
        else return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
    if (lhs < rhs || lhs == rhs) return true;
    else return false;
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    if (lhs <= rhs) return false;
    else return true;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    if (lhs < rhs) return false;
    else return true;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()){
	   return true;
    } else return false; 
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    if (lhs == rhs) return false;
    else return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    int suit_rank;
    for (int i = 0; i < NUM_SUITS; i++){
        if (suit == SUIT_NAMES_BY_WEIGHT[i]){
            suit_rank = i;
	   }
    }
    return SUIT_NAMES_BY_WEIGHT[(suit_rank + 2) % 4];
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less_helper(const Card &a, const Card &b, const std::string &trump){
    if (a.is_right_bower(trump)) return false;
    else if (b.is_right_bower(trump)) return true;
    else if (a.is_left_bower(trump)) return false;
    else if (b.is_left_bower(trump)) return true;
    else if (a.is_trump(trump) && !b.is_trump(trump)) return false;
    else if (b.is_trump(trump) && !a.is_trump(trump)) return true;
    else return a < b;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if (a.is_trump(trump) || b.is_trump(trump)) {
        return Card_less_helper(a, b, trump);
    }
    else return a < b;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if ((a.is_trump(trump) || b.is_trump(trump))) {
        return Card_less_helper(a, b, trump);
    }
    else if (a.get_suit() == led_card.get_suit() && 
        !(b.get_suit() == led_card.get_suit())) return false;
    else if (b.get_suit() == led_card.get_suit() && 
        !(a.get_suit() == led_card.get_suit())) return true;
    return a < b;
}