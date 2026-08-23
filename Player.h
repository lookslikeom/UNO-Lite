#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"
using namespace std;

class Player {
private:
    string name;
    vector<Card*> hand;

public:
    Player(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void drawCard(Card* c) {
        hand.push_back(c);
    }

    void showHand() {
        cout << name << "'s hand:" << endl;
        for (int i = 0; i < hand.size(); i++) {
            cout << "  [" << i << "] ";
            hand[i]->display();
        }
    }

    Card* playCard(int index) {
        Card* chosen = hand[index];
        hand.erase(hand.begin() + index);
        return chosen;
    }

    int handSize() {
        return hand.size();
    }
};

#endif