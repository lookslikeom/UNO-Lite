#include <iostream>
#include "Card.h"
#include "SpecialCard.h"
#include "Deck.h"
#include "Player.h"
#include "Rules.h"
using namespace std;

int main() {
    Deck deck;
    deck.buildDeck();
    deck.shuffleDeck();

    int numPlayers;
    cout << "How many players are playing? ";
    cin >> numPlayers;

    vector<Player> players;

    for (int i = 0; i < numPlayers; i++) {
        string name;
        cout << "Enter name for player " << (i + 1) << ": ";
        cin >> name;
        players.push_back(Player(name));
    }

    for (int i = 0; i < 5; i++) {
        for (int p = 0; p < numPlayers; p++) {
            players[p].drawCard(deck.dealCard());
        }
    }

    Card* currentCard = deck.dealCard();

    cout << "=====================================" << endl;
    cout << "          UNO LIGHT - START           " << endl;
    cout << "=====================================" << endl;

    int turn = 0;
    int direction = 1;
    bool someoneWon = false;

    while (!someoneWon) {

        if (deck.cardsLeft() == 0) {
            cout << endl << "Deck ran out! Game ends in a draw." << endl;
            break;
        }

        cout << endl << "-------------------------------------" << endl;
        cout << "Card on table: ";
        currentCard->display();
        cout << "-------------------------------------" << endl;

        players[turn].showHand();

        cout << players[turn].getName() << ", pick a card index to play: ";
        int choice;
        cin >> choice;

        Card* attempt = players[turn].playCard(choice);
        int step = 1;

        if (canPlay(attempt, currentCard)) {
            cout << players[turn].getName() << " played: ";
            attempt->display();

            if (attempt->isWild()) {
                string chosenColor;
                cout << "Choose a color (Red/Green/Blue/Yellow): ";
                cin >> chosenColor;
                SpecialCard* wildCard = (SpecialCard*) attempt;
                wildCard->chooseColor(chosenColor);
            }

            currentCard = attempt;

            if (players[turn].handSize() == 0) {
                cout << endl << players[turn].getName() << " WINS!" << endl;
                someoneWon = true;
                break;
            }

            string effect = attempt->getType();

            if (effect == "Skip") {
                step = 2;
                cout << "Next player is skipped!" << endl;
            }
            else if (effect == "Reverse") {
                direction = direction * -1;
                cout << "Direction reversed!" << endl;
            }
            else if (effect == "Draw2") {
                int nextTurn = (turn + direction + 2 * numPlayers) % numPlayers;
                players[nextTurn].drawCard(deck.dealCard());
                players[nextTurn].drawCard(deck.dealCard());
                cout << players[nextTurn].getName() << " draws 2 cards and is skipped!" << endl;
                step = 2;
            }
            else if (effect == "Draw4") {
                int nextTurn = (turn + direction + 2 * numPlayers) % numPlayers;
                for (int k = 0; k < 4; k++) {
                    players[nextTurn].drawCard(deck.dealCard());
                }
                cout << players[nextTurn].getName() << " draws 4 cards and is skipped!" << endl;
                step = 2;
            }

        } else {
            cout << "Invalid move! Card doesn't match. Drawing a card instead." << endl;
            players[turn].drawCard(attempt);
            players[turn].drawCard(deck.dealCard());
        }

        turn = (turn + step * direction + 2 * numPlayers) % numPlayers;
    }

    return 0;
}