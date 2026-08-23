#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card {
private:
    string color;
    string value;
protected:
    void setColor(string c) {
        color = c;
    }
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

    virtual void display() {
        cout << color << " " << value << endl;
    }
    
    virtual bool isWild() {
        return false;
    }
    virtual string getType() {
        return "Normal";
    }
  
};

#endif