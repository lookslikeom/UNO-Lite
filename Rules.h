#ifndef RULES_H
#define RULES_H

#include "Card.h"

bool canPlay(Card* played, Card* current) {
    if (played->isWild()) {
        return true;
    }
    if (played->getColor() == current->getColor()) {
        return true;
    }
    if (played->getValue() == current->getValue()) {
        return true;
    }
    return false;
}

#endif