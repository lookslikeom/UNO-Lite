#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <ctime>
#include "Card.h"
#include "SpecialCard.h"

using namespace std;

class Deck {
private:
    vector<Card*> cards;

public:
   void buildDeck() {
        string colors[4] = {"Red", "Green", "Blue", "Yellow"};

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j <= 9; j++) {
                Card* newCard = new Card(colors[i], to_string(j));
                cards.push_back(newCard);
            }

            cards.push_back(new SpecialCard(colors[i], "", "Skip"));
            cards.push_back(new SpecialCard(colors[i], "", "Reverse"));
            cards.push_back(new SpecialCard(colors[i], "", "Draw2"));
        }

        for (int w = 0; w < 4; w++) {
            cards.push_back(new SpecialCard("", "", "Wild"));
            cards.push_back(new SpecialCard("", "", "Draw4"));
        }
    }
    void shuffleDeck() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
    }

    Card* dealCard() {
        Card* top = cards.back();
        cards.pop_back();
        return top;
    }

    int cardsLeft() {
        return cards.size();
    }
};

#endif