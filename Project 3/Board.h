//
//  Board.h
//  Kalah
//
//  Created by Tran on 5/13/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef Board_h
#define Board_h
#include "Side.h"
#include "vector"
#include <iostream>
using namespace std;

class Board
{
    public:
        Board(int nHoles, int nInitialBeansPerHole);
        int holes() const;
        int beans(Side s, int hole) const;
        int beansInPlay(Side s) const;
        int totalBeans() const;
        bool sow(Side s, int hole, Side& endSide, int& endHole);
        bool moveToPot(Side s, int hole, Side potOwner);
        bool setBeans(Side s, int hole, int beans);
    private:
        int m_nHoles;
    //Vectors act as containers for the Game
        vector<int> m_South;
        vector<int> m_North;
    //Helper functions for the sow function
        void sowNorth(int hole, int& endHole, int& nbeans);
        void sowSouth(int hole, int& endHole, int& nbeans);
        void empty(Side s, int hole);
};


#endif /* Board_h */
