////
////  main.cpp
////  Kalah
////
////  Created by Tran on 5/13/19.
////  Copyright © 2019 Tran. All rights reserved.
////
//
#include <iostream>
#include "Board.h"
#include <cassert>
#include "Player.h"
#include "Game.h"

int main()
{
//Test the Board Class
////////////////////////////////////
    Board b(6, 4);
    //Test beans() function
    assert(b.beans(NORTH, 0) == 0);
    assert(b.beans(NORTH, 1) == 4);
    assert(b.beans(NORTH, 2) == 4);
    assert(b.beans(NORTH, 3) == 4);
    assert(b.beans(NORTH, 4) == 4);
    assert(b.beans(NORTH, 5) == 4);
    assert(b.beans(NORTH, 6) == 4);
    assert(b.beans(NORTH, 7) == -1);
    assert(b.beans(NORTH, -1) == -1);
    assert(b.beans(SOUTH, 0) == 0);
    assert(b.beans(SOUTH, 1) == 4);
    assert(b.beans(SOUTH, 2) == 4);
    assert(b.beans(SOUTH, 3) == 4);
    assert(b.beans(SOUTH, 4) == 4);
    assert(b.beans(SOUTH, 5) == 4);
    assert(b.beans(SOUTH, 6) == 4);
    assert(b.beans(SOUTH, 7) == -1);
    assert(b.beans(SOUTH, 8) == -1);
    assert(b.beans(SOUTH, 8) == -1);

    //Test the totalbeans() and set() and beansInPlay function.
    assert(b.beansInPlay(NORTH) == 24);
    assert(b.beansInPlay(SOUTH) == 24);
    assert(b.totalBeans() == 48);
    assert(b.setBeans(NORTH, 1, 20));
    assert(b.beansInPlay(NORTH) == 40);
    assert(b.beansInPlay(SOUTH) == 24);
    assert(!b.setBeans(NORTH, -1, 20));
    assert(!b.setBeans(NORTH, 9, 20));
    assert(b.beans(NORTH, 1) == 20);
    assert(b.totalBeans() == 64);
    assert(b.setBeans(NORTH, 0, 20));
    assert(b.totalBeans() == 84);


    //Test move to Pot Function
    assert(b.moveToPot(Side::NORTH, 1, Side::NORTH));
    assert(b.moveToPot(Side::NORTH, 1, Side::NORTH));
    assert(!b.moveToPot(Side::NORTH, 0, Side::NORTH));
    assert(b.moveToPot(Side::NORTH, 2, Side::SOUTH));
    assert(b.moveToPot(Side::SOUTH, 2, Side::SOUTH));
    assert(!b.moveToPot(Side::SOUTH, 0, Side::SOUTH));

    Board c(6, 4);
    Side endSide;
    int endhole;
    //Test the Sow Function
    assert(c.sow(Side::NORTH, 3, endSide, endhole));
    assert(endhole == 1);
    assert(endSide == Side::SOUTH);
    assert(c.sow(Side::NORTH, 1, endSide, endhole));
    assert(endhole == 4);
    assert(endSide == Side::SOUTH);
    assert(!c.sow(Side::NORTH, 0, endSide, endhole));
    assert(c.setBeans(Side::SOUTH, 1, 20));
    assert(c.sow(Side::SOUTH, 1, endSide, endhole));
    assert(endhole == 6);
    assert(endSide == Side::NORTH);
    assert(c.sow(Side::SOUTH, 1, endSide, endhole));
    assert(endhole == 2);
    assert(endSide == Side::SOUTH);

//Test the Player Class
////////////////////////////////////////
    //Test Human Player
    HumanPlayer david("david");
    assert(david.isInteractive());

    //Test the Bad Player
    Board d(6, 4);
    assert(d.setBeans(Side::SOUTH, 1, 0));
    assert(d.setBeans(Side::SOUTH, 2, 0));
    assert(d.setBeans(Side::SOUTH, 3, 0));
    assert(d.setBeans(Side::SOUTH, 4, 0));
    assert(d.setBeans(Side::SOUTH, 5, 0));
    assert(d.setBeans(Side::SOUTH, 6, 0));
    BadPlayer bad("BadComputer");
    assert(!bad.isInteractive());
    assert(bad.name() == "BadComputer");
    //The bad player should choose the the lowest possible hole that is
    assert(bad.chooseMove(d, Side::SOUTH) == -1);
    assert(bad.chooseMove(d, Side::NORTH) == 1);
    d.sow(Side::NORTH, 1, endSide, endhole);
    assert(bad.chooseMove(d, Side::NORTH) == 2);
    d.sow(Side::NORTH, 2, endSide, endhole);
    assert(bad.chooseMove(d, Side::NORTH) == 1);

    Board e(6, 4);
    assert(e.setBeans(Side::SOUTH, 1, 0));
    assert(e.setBeans(Side::SOUTH, 2, 0));
    assert(e.setBeans(Side::SOUTH, 3, 0));
    assert(e.setBeans(Side::SOUTH, 4, 0));
    assert(e.setBeans(Side::SOUTH, 5, 0));
    assert(e.setBeans(Side::SOUTH, 6, 0));

    //Test Smart Player
    SmartPlayer smart("SmartPlayer");
    assert(!smart.isInteractive());
    assert(smart.chooseMove(e, SOUTH) == -1);
    assert(smart.chooseMove(e, NORTH) == 1);
    e.sow(Side::NORTH, 4, endSide, endhole);

//Test the Game Class
////////////////////////////////////////
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board f(3, 0);
    f.setBeans(SOUTH, 1, 2);
    f.setBeans(NORTH, 2, 1);
    f.setBeans(NORTH, 3, 2);
    Game g(f, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
           g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move();
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    g.move();
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    g.move();
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
    g.move();
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}


