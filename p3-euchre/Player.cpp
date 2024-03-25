// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Player.h"
#include <string>
#include <vector>
#include "algorithm"
#include <cassert>
#include <iostream>
using namespace std;

class Human : public Player{
private:
    string name;
    vector<Card> hand;
    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
            cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }
public:
    //constructor
    Human(const string &n) {
        name = n;
    };
    
    //EFFECTS returns player's name
    virtual const string & get_name() const override{
        return name;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) override{
        assert(hand.size() <= MAX_HAND_SIZE);
        hand.push_back(c);
        sort(hand.begin(), hand.end());
    }
    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump (const Card &upcard, bool is_dealer,
                             int round, std::string &order_up_suit) const override{
        assert(round == 1 || round ==2);
        string input;
        bool mt = true;
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        cin>>input;
        
        if(input == "Spades" || input == "Hearts" ||
           input == "Clubs" || input == "Diamonds"){
            order_up_suit = string(input);
            mt = true;
        }
        else if(input == "pass"){
            mt = false;
        }
        return mt;
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard (const Card &upcard) override{
        print_hand();
        int num;
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        cin >> num;
        for(int i = 0; i<5;i++){
            if(num == i)
                hand[i] = upcard;
        }
        sort(hand.begin(), hand.end());
    }
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card (const std::string &trump) override{
        print_hand();
        int input;
        Card placeHolder;
        cout << "Human player " << name << ", please select a card:\n";
        cin>>input;
        placeHolder = hand[input];
        hand.erase(hand.begin() + input);
        sort(hand.begin(), hand.end());
        return placeHolder;
    }
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card (const Card &led_card, const std::string &trump) override{
        print_hand();
        int input;
        Card placeHolder;
        cout << "Human player " << name << ", please select a card:\n";
        cin>>input;
        placeHolder = hand[input];
        hand.erase(hand.begin() + input);
        sort(hand.begin(), hand.end());
        return placeHolder;
    }
    
    // Maximum number of cards in a player's hand
    static const int MAX_HAND_SIZE = 5;
    
    // Needed to avoid some compiler errors
    virtual ~Human() {}
};

class Simple : public Player{
private:
    string name;
    //vector<Card> currentCards;
    vector<Card> hand;
public:
    //constructor
    Simple(const string &n) {
        name = n;
    };
    
    //EFFECTS returns player's name
    virtual const string & get_name() const override{
        return name;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    virtual void add_card(const Card &c) override{
        assert(hand.size() <= MAX_HAND_SIZE);
        hand.push_back(c);
    }
    
    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    virtual bool make_trump (const Card &upcard, bool is_dealer,
                             int round, std::string &order_up_suit) const override{
        assert(round == 1 || round ==2);
        int sofar = 0;
        bool mt = true;
        if(round == 1){
            for(int i = 0; i <5; ++i){
                if(hand[i].is_face_or_ace() &&
                   hand[i].is_trump(upcard.get_suit()))
                    sofar++;
            }
            if(sofar >= 2){
                order_up_suit = upcard.get_suit();
                mt = true;
            }
            else
                mt = false;
        }
        if(round == 2){
            for(int i = 0; i <5; ++i){
                if(hand[i].is_face_or_ace()
                   && hand[i].is_trump(Suit_next(upcard.get_suit())))
                    sofar++;
            }
            if(sofar >= 1 && is_dealer == false){
                order_up_suit = Suit_next(upcard.get_suit());
                mt = true;
            }
            else if(sofar == 0 && is_dealer == false)
                mt = false;
            else if(is_dealer == true){
                order_up_suit = Suit_next(upcard.get_suit());
                mt = true;
            }
        }
        return mt;
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    virtual void add_and_discard (const Card &upcard) override{
        //hand.push_back(upcard);
        //sort(hand.begin(), hand.end());
        for(int j = 1; j < hand.size(); j++){
            Card key = hand[j];
            int i = j-1;
            
            while(i >= 0 && Card_less(key, hand[i], upcard.get_suit())){
                hand[i+1] = hand[i];
                i--;
            }
            hand[i+1] = key;
        }
        
        if(Card_less(hand[0], upcard, upcard.get_suit()))
        {hand[0] = upcard;}
    }
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    virtual Card lead_card (const std::string &trump) override{
        Card temp;
        sort(hand.begin(), hand.end());
        for(int j = 1; j < hand.size(); j++){
            Card key = hand[j];
            int i = j-1;
            
            while(i >= 0 && Card_less(key, hand[i], trump)){
                hand[i+1] = hand[i];
                i--;
            }
            hand[i+1] = key;
        }
        
        int sofar = 0;
        Card placeHolder;
        for(int i = 0; i < hand.size(); ++i){
            if(hand[i].get_suit(trump) == trump)
                sofar += 1;
        }
        if(sofar == hand.size()){
            placeHolder = hand[hand.size() - 1];
            hand.erase(hand.begin() + hand.size() - 1);
        }
        else if(sofar != hand.size() && sofar != 0){
            for(int i = 0; i < hand.size(); i++){
                if(hand[i].get_suit() == trump){
                    placeHolder = hand[i - 1];
                    hand.erase(hand.begin() + i - 1);
                    break;
                }
            }
        }
        else if(sofar == 0){
            placeHolder = hand[hand.size() - 1];
            hand.erase(hand.begin() + hand.size() - 1);
        }
        return placeHolder;
    }
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    virtual Card play_card (const Card &led_card, const std::string &trump) override{
        Card temp;
        for(int j = 1; j < hand.size(); j++){
            Card key = hand[j];
            int i = j-1;
            
            while(i >= 0 && Card_less(key, hand[i], led_card, trump)){
                hand[i+1] = hand[i];
                i--;
            }
            hand[i+1] = key;
        }
        
        int sofar = 0;
        int forTrump = 0;
        Card placeHolder;
        for(int i = 0; i < hand.size(); ++i){
            if(hand[i].get_suit(trump) == led_card.get_suit()){
                sofar += 1;
            }
        }
        for(int j = 0; j < hand.size(); ++j){
            if(hand[j].get_suit(trump) == trump){
                forTrump += 1;
            }
        }
        if(sofar != 0 && forTrump != 0 && trump == led_card.get_suit()){
            placeHolder = hand[hand.size() - 1];
            hand.erase(hand.begin() + hand.size() - 1);
        }
        else if(sofar != 0 && forTrump != 0){
            for(int i = 0; i < hand.size(); i++){
                if(hand[i].get_suit(trump) == trump){
                    placeHolder = hand[i - 1];
                    hand.erase(hand.begin() + i - 1);
                    break;
                }
            }
        }
        else if(sofar != 0 && forTrump ==0){
                    placeHolder = hand[hand.size() - 1];
                    hand.erase(hand.begin() + hand.size() - 1);
                }
        else if(sofar == 0){
            placeHolder = hand[0];
            hand.erase(hand.begin());
        }
        return placeHolder;
    }
    
    // Maximum number of cards in a player's hand
    static const int MAX_HAND_SIZE = 5;
    
    // Needed to avoid some compiler errors
    virtual ~Simple() {}
};


Player * Player_factory(const std::string &name,
                        const std::string &strategy) {
    // We need to check the value of strategy and return
    // the corresponding player type.
    if (strategy == "Simple") {
        // The "new" keyword dynamically allocates an object.
        return new Simple(name);
    }
    if (strategy == "Human") {
        // The "new" keyword dynamically allocates an object.
        return new Human(name);
    }
    else
        assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p){
    os<<p.get_name();
    return os;
}
