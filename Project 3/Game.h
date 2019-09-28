//
//  Game.h
//  Kalah
//
//  Created by Tran on 5/13/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include "Board.h"
#include "Player.h"
#include <iostream>
using namespace std;

class Game
{
    public:
        Game(const Board& b, Player* south, Player* north);
        void display() const;
        void status(bool& over, bool& hasWinner, Side& winner) const;
        bool move();
        void play();
        int beans(Side s, int hole) const;
    
    private:
        Board m_b;
        Player* m_north;
        Player* m_south;
        //Turn is true for south and false for north
        bool m_turn;
        void addspace(unsigned long size) const;
        //Calls funciton if the game is over.
        void ifover();
        //Sows the hole with the rules. Returns false if player gets one more more.
        bool sowrules(Player* side, Side s, int& hole);
};
#endif /* Game_h */
