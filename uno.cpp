#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
//Single Card class
class Card {
private:
    string color;
    string value;

public:
    Card(string c, string v) {
        color = c;
        value = v;
    }

    string getColor() {
        return color;
    }

    string getValue() {
        return value;
    }

    void display() {
        cout << color << " " << value << endl;
    }
};

// Deck Class
class Deck {
private:
    vector<Card> cards;

public:
    void buildDeck() {
        string colors[4] = {"Red", "Green", "Blue", "Yellow"};

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j <= 9; j++) {
                string value = to_string(j);
                Card newCard(colors[i], value);
                cards.push_back(newCard);
            }
        }
    }

    void shuffleDeck() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
    }
    
// an example of abstraction

    Card dealCard() {
        Card top = cards.back();  
        cards.pop_back();
        return top;
    }

    int cardsLeft() {
        return cards.size();
    }
};
// by the end of this we can show no of cards in the deck and also left after dealing , whole shuffling process, drawing process also goes hand in hand 
//polymorphism also like each player has different number of cards and and they can play different cards under the same class
// deck inherits card class and player inherits deck class and this is a composition at the same time

class Player {
private:
    string name;
    vector<Card> hand;

public:
    Player(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void drawCard(Card c) {
        hand.push_back(c);
    }

    void showHand() {
        cout << name << "'s hand:" << endl;
        for (int i = 0; i < hand.size(); i++) {
            cout << "  [" << i << "] ";
            hand[i].display();
        }
    }

    Card playCard(int index) {
        Card chosen = hand[index];
        hand.erase(hand.begin() + index);
        return chosen;
    }

    int handSize() {
        return hand.size();
    }
};
// players can have different number of cards and can play different cards under the same class, demonstrating polymorphism. The Deck class inherits from the Card class, and the Player class inherits from the Deck class, showcasing composition as well. 
bool canPlay(Card played, Card current) {
    if (played.getColor() == current.getColor()) {
        return true;
    }
    if (played.getValue() == current.getValue()) {
        return true;
    }
    return false;
}
//tells if the played card can be played on the current card based on color or value matching
int main() {
    Deck deck;
    deck.buildDeck();
    deck.shuffleDeck();

    Player p1("Jai/Lakshita");
    Player p2("Om ;)");
    Player* players[2] = {&p1, &p2};

    for (int i = 0; i < 5; i++) {
        p1.drawCard(deck.dealCard());
        p2.drawCard(deck.dealCard());
    }

    Card currentCard = deck.dealCard();

    cout << "=====================================" << endl;
    cout << "          UNO LIGHT - START           " << endl;
    cout << "=====================================" << endl;

    int turn = 0;

    while (p1.handSize() > 0 && p2.handSize() > 0) {

        if (deck.cardsLeft() == 0) {
            cout << endl << "Deck ran out! Game ends in a draw." << endl;
            break;
        }

        Player* current = players[turn];

        cout << endl << "-------------------------------------" << endl;
        cout << "Card on table: ";
        currentCard.display();
        cout << "-------------------------------------" << endl;

        current->showHand();

        cout << current->getName() << ", pick a card index to play: ";
        int choice;
        cin >> choice;

        Card attempt = current->playCard(choice);

        if (canPlay(attempt, currentCard)) {
            cout << current->getName() << " played: ";
            attempt.display();
            currentCard = attempt;
        } else {
            cout << "Invalid move! Card doesn't match. Drawing a card instead." << endl;
            current->drawCard(attempt);
            current->drawCard(deck.dealCard());
        }

        turn = (turn + 1) % 2;
    }

    cout << endl << "=====================================" << endl;

    if (p1.handSize() == 0) {
        cout << p1.getName() << " WINS! " << endl;
    } else if (p2.handSize() == 0) {
        cout << p2.getName() << " WINS! " << endl;
    }

    cout << "=====================================" << endl;

    return 0;
} 
//is the complete uno that i have built, atlast only functions have been called and objects, different classes have been created . last chunk is the game logic using everything that has been created in the previous classes and functions.
// many things to be improved: special cards, better ui, more players