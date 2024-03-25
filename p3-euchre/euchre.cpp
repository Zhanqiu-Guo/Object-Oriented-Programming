// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <cassert>
#include "Pack.h"
#include "Card.h"
#include "Player.h"
using namespace std;


class Game {
private:
    Pack pack;
	vector<Player*> players;
    bool shuffle_choice;
	Card upcard;
	int dealer_index;
    int goal_score;
	int team1_score = 0;
    int team2_score = 0;
	int team1_tricks;
	int team2_tricks;
	int order_up_index;
	string trump;

public:
    Game(Pack pack_in, vector <Player*> player_in, bool choice, int goal_score)
		:pack(pack_in), players(player_in), shuffle_choice(choice),
		goal_score(goal_score){}

// team1_score(0), team2_score(0), dealer_index(0)
    void deal() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
				(this->players[(this->dealer_index + i + 1)%4])->
					add_card(this->pack.deal_one());
			}
            if (i % 2 == 0) {
                (this->players[(this->dealer_index + i + 1)%4])->
					add_card(this->pack.deal_one());
            }
		}
		for (int i = 4; i < 8; i++) {
            for (int j = 0; j < 2; j++) {
				(this->players[(this->dealer_index + i + 1)%4])->
					add_card(this->pack.deal_one());
			}
            if (i % 2 != 0) {
                (this->players[(this->dealer_index + i + 1)%4])->
					add_card(this->pack.deal_one());
            }
		}
		this->upcard = this->pack.deal_one();
		cout << this->upcard << " turned up" << endl;
	}

	void set_trump() {
		bool order_up = false;
		int player_index = (this->dealer_index + 1) % 4;
		int turn = 0;
		while (turn < 8 && !order_up) {
			int round = 1 + turn / 4;
			order_up = this->players[player_index]->
				make_trump(upcard, (player_index == this->dealer_index), 
				round, this->trump);
			if (order_up) {
				cout << this->players[player_index]->get_name() << 
					" orders up " << this->trump << endl;
				this->order_up_index = player_index;
				if (round == 1) {
					this->players[this->dealer_index]->add_and_discard(upcard);
				}
				this->dealer_index = (this->dealer_index + 1) % 4;
				break;
				
			} else {
				cout << this->players[player_index]->get_name() << " passes" << endl;
			}
			player_index = (player_index + 1) % 4;
			turn += 1;
		}
	}


    void get_trick_winner() {
		for (int i = 0; i < 5; i++) {
			int leader = this->dealer_index;
			int winner_index = leader;
			Card lead = (this->players[leader])->lead_card(this->trump);
			Card biggest_card = lead;
			cout << lead << " led by " << (this->players[leader])->get_name() << endl;
			for (int j = 1; j < 4; j++) {
				Card curr_card = (this->players[(leader + j) % 4])->play_card(lead, this->trump);
				cout << curr_card << " played by " << 
					(this->players[(leader + j) % 4])->get_name() << endl;
				if (Card_less(biggest_card, curr_card, lead, this->trump)) {
					biggest_card = curr_card;
					winner_index = (leader + j) % 4;
				}
			}
			this->dealer_index = winner_index;
			if (winner_index == 0 || winner_index == 2) this->team1_tricks += 1;
			else this->team2_tricks += 1; 
			cout << (this->players[winner_index])->get_name() << " takes the trick";

			cout << endl << endl;
		}
	}

    void update_score() {
		if (this->team1_tricks > this->team2_tricks) {
			cout << (this->players[0])->get_name() << " and " 
				<< (this->players[2])->get_name() << " win the hand" << endl;
			if (this->order_up_index == 0 || this->order_up_index == 2) {
				if (this->team1_tricks == 3 || this->team1_tricks == 4) {
					this->team1_score += 1;
				} else {
					this->team1_score += 2;
					cout << "march!" << endl;
				}
			} else {
				this->team1_score += 2;
				cout << "euchred!" << endl;
			}
		} else {
			cout << (this->players[1])->get_name() << " and "
				<< (this->players[3])->get_name() << " win the hand" << endl;
			if (this->order_up_index == 1 || this->order_up_index == 3) {
				if (this->team2_tricks == 3 || this->team2_tricks == 4) {
					this->team2_score += 1;
				} else {
					this->team2_score += 2;
					cout << "march!" << endl;
				}
			} else {
				this->team2_score += 2;
				cout << "euchred!" << endl;
		    }
	    }
    }

	void play_game() {
		int hand = 0;
		while (this->team1_score < this->goal_score && this->team2_score < this->goal_score) {
			this->pack.reset();
			this->team1_tricks = 0;
			this->team2_tricks = 0;
			this->dealer_index = hand % 4;
			cout << "Hand " << hand << endl;
			cout << (this->players[this->dealer_index])->get_name() << " deals" << endl;
			if (shuffle_choice == true) pack.shuffle();
			this->deal();
			this->set_trump();
			this->get_trick_winner();
			this->update_score();
			cout << (this->players[0])->get_name() << " and " << (this->players[2])->get_name();
			cout << " have " << this->team1_score << " points" << endl;
			cout << (this->players[1])->get_name() << " and " << (this->players[3])->get_name();
			cout << " have " << this->team2_score << " points" << endl;
			cout << endl;
			hand += 1;
		}
		determine_win();
	}

	void determine_win() {
		if (this->team1_score > this->team2_score) {
			cout << players[0]->get_name() << " and " << players[2]->get_name();
			cout << " win!" << endl;
		} else {
			cout << players[1]->get_name() << " and " << players[3]->get_name();
			cout << " win!" << endl;
		}
	}

    ~Game() {
		for (size_t i = 0; i < 4; ++i) {
			delete this->players[i];
		}
    }
};

int main(int argc, char **argv) {
    // Read command line args and check for errors
    if (!(argc == 12 || atoi(argv[3]) > 1 || atoi(argv[3]) > 100 ||
    string(argv[2]) == "shuffle" || string(argv[2]) == "noshuffle" ||
    string(argv[5]) == "Simple" || string(argv[5]) == "Human" ||
	string(argv[7]) == "Simple" || string(argv[7]) == "Human" ||
	string(argv[9]) == "Simple" || string(argv[9]) == "Human" ||
	string(argv[11]) == "Simple" || string(argv[11]) == "Human")) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    ifstream pack_in;
    pack_in.open(argv[1]);
    if (!pack_in.is_open()) {
        cout << "Error opening " << argv[1] << endl;
        return 1;
    }
    for (int i = 0; i < argc; i++) {
		cout << argv[i] << " ";
	}
	cout << endl;
    bool shuffle_choice = (string(argv[2]) == "shuffle");
    int goal_score = atoi(argv[3]);
    vector <Player*> players;
    Player* player0 = Player_factory(argv[4], argv[5]);
    Player* player1 = Player_factory(argv[6], argv[7]);
    Player* player2 = Player_factory(argv[8], argv[9]);
    Player* player3 = Player_factory(argv[10], argv[11]);
	players.push_back(player0);
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);

	Game *game = new Game(pack_in, players, shuffle_choice, goal_score);
    game->play_game();
    delete game;
    return 0;
}
