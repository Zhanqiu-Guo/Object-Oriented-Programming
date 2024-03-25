#include <string>
#include <vector>
#include "unit_test_framework.h"
#include "poker.h"
using namespace std;


TEST(test_basic_hand){
    vector<Card> hand;
    Card c1{"Ace","Spades"};
    Card c2{"Ace", "Clubs"};
    Card c3{"Jack", "Hearts"};
    Card c4{"Five", "Diamonds"};
    Card c5{"Four", "Clubs"};

    hand.push_back(c1);
    hand.push_back(c2);
    hand.push_back(c3);
    hand.push_back(c4);
    hand.push_back(c5);

    ASSERT_TRUE(has_one_pair(hand));
}

//add your tests here
TEST(test_SHCCC){
    vector<Card> hand;
    Card c1{"Ace","Spades"};
    Card c2{"Ace", "Clubs"};
    Card c3{"Jack", "Hearts"};
    Card c4{"Five", "Clubs"};
    Card c5{"Four", "Clubs"};

    hand.push_back(c1);
    hand.push_back(c2);
    hand.push_back(c3);
    hand.push_back(c4);
    hand.push_back(c5);

    ASSERT_FALSE(has_one_pair(hand));
}

TEST(test_SCCHH){
    vector<Card> hand;
    Card c1{"Ace","Spades"};
    Card c2{"Ace", "Clubs"};
    Card c3{"Jack", "Hearts"};
    Card c4{"Five", "Hearts"};
    Card c5{"Four", "Clubs"};

    hand.push_back(c1);
    hand.push_back(c2);
    hand.push_back(c3);
    hand.push_back(c4);
    hand.push_back(c5);

    ASSERT_FALSE(has_one_pair(hand));
}

TEST(test_CCCHH){
    vector<Card> hand;
    Card c1{"Ace","Clubs"};
    Card c2{"Ace", "Clubs"};
    Card c3{"Jack", "Hearts"};
    Card c4{"Five", "Hearts"};
    Card c5{"Four", "Clubs"};

    hand.push_back(c1);
    hand.push_back(c2);
    hand.push_back(c3);
    hand.push_back(c4);
    hand.push_back(c5);

    ASSERT_FALSE(has_one_pair(hand));
}

TEST(test_SCCCH){
    vector<Card> hand;
    Card c1{"Ace","Clubs"};
    Card c2{"Ace", "Clubs"};
    Card c3{"Jack", "Spades"};
    Card c4{"Five", "Hearts"};
    Card c5{"Four", "Clubs"};

    hand.push_back(c1);
    hand.push_back(c2);
    hand.push_back(c3);
    hand.push_back(c4);
    hand.push_back(c5);

    ASSERT_FALSE(has_one_pair(hand));
}


TEST_MAIN()