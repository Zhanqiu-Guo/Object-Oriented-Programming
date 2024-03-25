// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_simple_player_make_trump) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  string trump;
  bool orderup = alice->make_trump(
    ace_spades,
    true,
    1,
    trump
  );

  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete alice;
}

TEST(test_simple_player_make_trump_1) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

  Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
  string trump;
  bool orderup = alice->make_trump(
    ace_spades,
    true,
    1,
    trump
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete alice;
}

TEST(test_simple_player_make_trump_2) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

  Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
  string trump;
  bool orderup = alice->make_trump(
    ten_clubs,
    true,
    1,
    trump
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_CLUBS);

  delete alice;
}

TEST(test_simple_player_make_trump_3) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));

  Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
  string trump;
  bool orderup = alice->make_trump(
    ten_clubs,
    false,
    2,
    trump
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete alice;
}

TEST(test_simple_player_make_trump_4) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

  Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
  string trump;
  bool orderup = alice->make_trump(
    ten_clubs,
    false,
    2,
    trump
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete alice;
}

TEST(test_simple_player_make_trump_5) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

  Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
  string trump;
  bool orderup = alice->make_trump(
    ten_clubs,
    false,
    2,
    trump
  );

  ASSERT_FALSE(orderup);
  //ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete alice;
}

TEST(test_simple_player_make_trump_6) {
  Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    alice->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
    alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));

  Card ten_clubs(Card::RANK_TEN, Card::SUIT_CLUBS);
  string trump;
  bool orderup = alice->make_trump(
    ten_clubs,
    true,
    2,
    trump
  );

  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, Card::SUIT_SPADES);

  delete alice;
}

TEST(test_add_discard_card) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));

    bob->add_and_discard(
                         Card(Card::RANK_TWO, Card::SUIT_SPADES) // upcard
                         );

    Card played = bob->play_card(Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card two_spades (Card::RANK_TWO, Card::SUIT_SPADES);
  ASSERT_EQUAL(played, two_spades); //check led card

  delete bob;
}

TEST(test_add_discard_card_1) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));

    bob->add_and_discard(
                         Card(Card::RANK_TWO, Card::SUIT_SPADES) // upcard
                         );

    Card played = bob->play_card(Card(Card::RANK_THREE, Card::SUIT_SPADES), Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card two_spades (Card::RANK_TWO, Card::SUIT_SPADES);
  ASSERT_EQUAL(played, two_spades); //check led card

  delete bob;
}

TEST(test_add_discard_card_2) {
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));

    bob->add_and_discard(
                         Card(Card::RANK_TWO, Card::SUIT_CLUBS) // upcard
                         );

    Card played = bob->play_card(Card(Card::RANK_THREE, Card::SUIT_SPADES), Card::SUIT_CLUBS);

  // Verify the card Bob selected to lead
  Card nine_clubs (Card::RANK_NINE, Card::SUIT_CLUBS);
  ASSERT_EQUAL(played, nine_clubs); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_SPADES));

    //Bob adds a card to his hand and discards one card
    bob->add_and_discard(
                         Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
                         );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card king_clubs(Card::RANK_KING, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led, king_clubs); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    //Bob adds a card to his hand and discards one card
    bob->add_and_discard(
                         Card(Card::RANK_NINE, Card::SUIT_SPADES) // upcard
                         );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_SPADES);

  // Verify the card Bob selected to lead
  Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, ace_hearts); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

    //Bob adds a card to his hand and discards one card
    bob->add_and_discard(
                         Card(Card::RANK_NINE, Card::SUIT_HEARTS)// upcard
                         );

  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
  ASSERT_EQUAL(card_led, ace_hearts); //check led card

  delete bob;
}


TEST(test_simple_player_lead_card_3) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));

    //Bob adds a card to his hand and discards one card
    
    bob->add_and_discard(
                         Card(Card::RANK_ACE, Card::SUIT_HEARTS)// upcard
                         );

     
  // Bob leads
  Card card_led = bob->lead_card(Card::SUIT_HEARTS);

  // Verify the card Bob selected to lead
  Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
  ASSERT_EQUAL(card_led, nine_clubs); //check led card

  delete bob;
}
 
TEST(test_simple_player_lead_card_4) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Card card_led = bob->lead_card(Card::SUIT_SPADES);
    ASSERT_EQUAL(card_led,Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    delete bob;
}

TEST(test_simple_player_lead_card_5) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_NINE, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    Card card_led = bob->lead_card(Card::SUIT_HEARTS);
    ASSERT_EQUAL(card_led, Card(Card::RANK_TEN, Card::SUIT_CLUBS));
    delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_HEARTS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_NINE, Card::SUIT_HEARTS));
  delete bob;
}

TEST(test_simple_player_play_card_1) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_KING, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));

  // Bob plays a card
  Card nine_diamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    "Hearts"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_ACE, Card::SUIT_DIAMONDS));
  delete bob;
}

TEST(test_simple_player_play_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  bob->add_card(Card(Card::RANK_QUEEN, Card::SUIT_HEARTS));

  // Bob plays a card
  Card nine_spade(Card::RANK_NINE, Card::SUIT_SPADES);
  Card card_played = bob->play_card(
  nine_spade,  // Nine of Diamonds is led
    "Spades"        // Trump suit
  );

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
  delete bob;
}

TEST(test_simple_player_play_card_3) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_TEN, Card::SUIT_HEARTS));
    bob->add_card(Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    Card lead(Card(Card::RANK_TEN, Card::SUIT_SPADES));
    Card card_played = bob->play_card(lead,Card::SUIT_SPADES);
    ASSERT_EQUAL(card_played, Card(Card::RANK_JACK, Card::SUIT_CLUBS));
    delete bob;
}

TEST(test_simple_player_play_card_4) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(Card::RANK_FIVE, Card::SUIT_SPADES));
    bob->add_card(Card(Card::RANK_SIX, Card::SUIT_CLUBS));
    bob->add_card(Card(Card::RANK_SEVEN, Card::SUIT_DIAMONDS));
    bob->add_card(Card(Card::RANK_EIGHT, Card::SUIT_HEARTS));
    Card lead(Card(Card::RANK_FIVE, Card::SUIT_HEARTS));
    Card card_played = bob->play_card(lead,Card::SUIT_DIAMONDS);
    ASSERT_EQUAL( card_played, Card(Card::RANK_EIGHT, Card::SUIT_HEARTS));
    delete bob;
}


TEST_MAIN()
