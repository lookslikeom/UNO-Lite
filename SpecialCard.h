#ifndef SPECIALCARD_H
#define SPECIALCARD_H

#include "Card.h"
#include <string>
using namespace std;

class SpecialCard : public Card {
private:
    string type;

public:
    SpecialCard(string c, string v, string t) : Card(c, v) {
        type = t;
    }

    string getType() {
        return type;
    }

    bool isWild() {
        return (type == "Wild" || type == "Draw4");
    }

    void display() {
        if (type == "Wild" || type == "Draw4") {
            cout << "Wild " << type << endl;
        } else {
            cout << getColor() << " " << type << endl;
        }
    }

    void chooseColor(string c) {
        setColor(c);
    }
};

#endif