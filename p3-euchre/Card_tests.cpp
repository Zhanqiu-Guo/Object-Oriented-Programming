// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

TEST(test_card_ctor_default) {
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_get_rank_and_suit) {
    Card c;
    ASSERT_EQUAL(c.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
}

TEST(test_is_face_or_ace) {
    Card Jack(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card Ten(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_TRUE(Jack.is_face_or_ace());
    ASSERT_FALSE(Ten.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card Jack_Spades(Card::RANK_JACK, Card::SUIT_SPADES);
    Card Ten_Spades(Card::RANK_TEN, Card::SUIT_SPADES);
    ASSERT_TRUE(Jack_Spades.is_right_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(Jack_Spades.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(Ten_Spades.is_right_bower(Card::SUIT_SPADES));
}

TEST(test_is_left_bower) {
    Card Jack_Diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card Ten_Diamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Jack_Diamonds.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_FALSE(Jack_Diamonds.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_FALSE(Jack_Diamonds.is_left_bower(Card::SUIT_SPADES));
    ASSERT_FALSE(Ten_Diamonds.is_left_bower(Card::SUIT_HEARTS));
}

TEST (test_is_trump) {
    Card Nine_Hearts(Card::RANK_NINE, Card::SUIT_HEARTS);		 
    Card Jack_Diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Nine_Hearts.is_trump(Card::SUIT_HEARTS));
    ASSERT_TRUE(Jack_Diamonds.is_trump(Card::SUIT_HEARTS));
    ASSERT_FALSE(Jack_Diamonds.is_trump(Card::SUIT_SPADES));
}

TEST(test_operator) {
    Card Jack_Diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card Jack_Hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card Nine_Diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_TRUE(Jack_Diamonds > Jack_Hearts);
    ASSERT_FALSE(Jack_Diamonds <= Jack_Hearts);
    ASSERT_TRUE(Nine_Diamonds < Jack_Diamonds);
    ASSERT_FALSE(Nine_Diamonds >= Jack_Diamonds);
    ASSERT_TRUE(Jack_Hearts > Nine_Diamonds);
    ASSERT_TRUE(Jack_Diamonds != Jack_Hearts);
    ASSERT_TRUE(Nine_Diamonds == Nine_Diamonds);
}

TEST(test_ostream) {
    Card Two_Spades(Card::RANK_TWO, Card::SUIT_SPADES);
    ostringstream s;
    s << Two_Spades;
    ostringstream correct;
    correct << "Two of Spades";
    ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_suit_next) {
    string const Spades = Card::SUIT_SPADES;
    ASSERT_EQUAL(Suit_next(Spades), Card::SUIT_CLUBS);
}

TEST(test_card_less_trump) {
    string const trump = Card::SUIT_SPADES;
    Card right_bower(Card::RANK_JACK, trump);
    Card left_bower(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card Queen_Spades(Card::RANK_QUEEN, trump);
    Card Nine_Spades(Card::RANK_NINE, trump);			  
    Card Queen_Hearts(Card::RANK_TEN, Card::SUIT_HEARTS);	 
    Card Nine_Hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card Nine_Clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(left_bower, right_bower, trump));
    ASSERT_TRUE(Card_less(Queen_Spades, right_bower, trump));
    ASSERT_TRUE(Card_less(Queen_Spades, left_bower, trump));
    ASSERT_TRUE(Card_less(Nine_Spades, Queen_Spades, trump));
    ASSERT_TRUE(Card_less(Nine_Hearts, Queen_Hearts, trump)); 
    ASSERT_TRUE(Card_less(Nine_Hearts, Nine_Spades, trump)); 
    ASSERT_TRUE(Card_less(Queen_Hearts, left_bower, trump));
    ASSERT_TRUE(Card_less(Queen_Hearts, right_bower, trump));
    ASSERT_TRUE(Card_less(Nine_Hearts, Nine_Clubs, trump)); 
}

TEST(test_card_less_trump_led_card) {
    Card const led_card1(Card::RANK_ACE, Card::SUIT_SPADES);
    string const trump = Card::SUIT_SPADES;
    Card right_bower(Card::RANK_JACK, trump);
    Card left_bower(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card Queen_Spades(Card::RANK_QUEEN, trump);
    Card Nine_Spades(Card::RANK_NINE, trump);			  
    Card Queen_Hearts(Card::RANK_TEN, Card::SUIT_HEARTS);	 
    Card Nine_Hearts(Card::RANK_NINE, Card::SUIT_HEARTS);
    Card Nine_Clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(left_bower, right_bower, led_card1, trump));
    ASSERT_TRUE(Card_less(Queen_Spades, right_bower, led_card1, trump));
    ASSERT_TRUE(Card_less(Queen_Spades, left_bower, led_card1, trump));
    ASSERT_TRUE(Card_less(Nine_Spades, Queen_Spades, led_card1, trump));
    ASSERT_TRUE(Card_less(Nine_Hearts, Queen_Hearts, led_card1, trump)); 
    ASSERT_TRUE(Card_less(Nine_Hearts, Nine_Spades, led_card1, trump)); 
    ASSERT_TRUE(Card_less(Queen_Hearts, left_bower, led_card1, trump));
    ASSERT_TRUE(Card_less(Queen_Hearts, right_bower, led_card1, trump));
    ASSERT_TRUE(Card_less(Queen_Hearts, right_bower, led_card1, trump));
    ASSERT_TRUE(Card_less(Nine_Hearts, Nine_Clubs, led_card1, trump));

    Card const led_card2(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_TRUE(Card_less(left_bower, right_bower, led_card2, trump));
    ASSERT_TRUE(Card_less(Queen_Spades, right_bower, led_card2, trump));
    ASSERT_TRUE(Card_less(Queen_Spades, left_bower, led_card2, trump));
    ASSERT_TRUE(Card_less(Nine_Spades, Queen_Spades, led_card2, trump));
    ASSERT_TRUE(Card_less(Nine_Hearts, Queen_Hearts, led_card2, trump)); 
    ASSERT_TRUE(Card_less(Nine_Hearts, Nine_Spades, led_card2, trump)); 
    ASSERT_TRUE(Card_less(Queen_Hearts, left_bower, led_card2, trump));
    ASSERT_TRUE(Card_less(Queen_Hearts, right_bower, led_card2, trump)); 
    ASSERT_FALSE(Card_less(Nine_Hearts, Nine_Clubs, led_card2, trump));
}

TEST_MAIN()