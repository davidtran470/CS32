//
//  Board.cpp
//  Kalah
//
//  Created by Tran on 5/13/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include "Board.h"
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
:m_nHoles(nHoles)
{
    //Initialize the pots of the two sides
    m_North.push_back(POT);
    m_South.push_back(POT);
    for(int i = 0; i < m_nHoles; i++)
    {
        //If BeanperHole is negative, we add 0 to each hole
        if(nInitialBeansPerHole <= 0)
        {
            m_North.push_back(0);
            m_South.push_back(0);
        }
        //Outwise add the number specified
        m_North.push_back(nInitialBeansPerHole);
        m_South.push_back(nInitialBeansPerHole);
    }
}


int Board::holes() const
{
    return m_nHoles;
}

int Board::beans(Side s, int hole) const
{
    if(!(0 <= hole && hole <= m_nHoles))
        return -1;
    //If side is North, we return from the North Side
    if(s == Side::NORTH)
        return m_North[hole];
    //If side is South, we reutrn from South Side
    return m_South[hole];
}

int Board::beansInPlay(Side s) const
{
    int beans = 0;
    //Go throught the vector to add up all the beans
    for(int i = 1; i <= m_nHoles; i++)
    {
        //If North, add only the North
        if(s == Side::NORTH)
            beans += m_North[i];
        //If North, add only the South
        else
            beans += m_South[i];
    }
    return beans;
}

//Add beans in the pots to the total
//Add beans in every hole to the total
int Board::totalBeans() const
{
    int total = 0;
    for(int i = 0; i < m_nHoles + 1; i++)
    {
        total +=  m_South[i] + m_North[i];
    }
    return total;
}

//Sows the seeds from the
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    //If the hole is invalid or the hole is empty.
    if(!(0 < hole && hole <= m_nHoles) || beans(s,hole) == 0)
        return false;
    
    int nbeans = beans(s, hole);
    empty(s, hole);
    //Indicates which direction we should go, true = South, false = North.
    bool tracker = true;
    
    //Starts the initial Sow either North or South
    if (s == Side::NORTH)
    {
        sowNorth(hole - 1, endHole, nbeans);
        endSide = Side::NORTH;
    }
    else
    {
        sowSouth(hole + 1, endHole, nbeans);
        endSide = Side::SOUTH;
        tracker = false;
    }
    
    //If there are more beans to be sowed, proceed with sowing the pot and the other side.
    while (nbeans > 0)
    {
        //First decided if it is appropriate to sow the pot using the tracker and the inputed side.
        if(tracker && s == Side::NORTH)
        {
            m_North[0] += 1;
            nbeans--;
            if(nbeans == 0)
                endHole = 0;
            endSide = Side::NORTH;
        }
        else if(!tracker && s == Side::SOUTH)
        {
            m_South[0] += 1;
            nbeans--;
            if(nbeans == 0)
                endHole = 0;
            endSide = Side::SOUTH;
        }
        //If there are still more beans, we can sow the opposite side.
        if(nbeans > 0)
        {
            if (tracker)
            {
                sowSouth(1, endHole, nbeans);
                endSide = Side::SOUTH;
                tracker = false;
            }
            else
            {
                sowNorth(m_nHoles, endHole, nbeans);
                endSide = Side::NORTH;
                tracker = true;
            }
        }
    }
    return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    //If invalid, pot, or empty return false
    if(!(0 < hole && hole <= m_nHoles))
        return false;
    int temp = beans(s, hole);
    //Empty the hole
    empty(s, hole);
    //Add to the appropriate pot
    if (potOwner == Side::NORTH)
        m_North[0] += temp;
    else
        m_South[0] += temp;
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    //If bean added is negative, or hole is invalid we return false.
    if(beans < 0 || !(hole >=0 && hole <= m_nHoles))
        return false;
    //Otherwise, set the hole to appropriate amount.
    if (s == Side::NORTH)
        m_North[hole] = beans;
    else
        m_South[hole] = beans;
    return true;
}

//Sows North CounterClockwise
void Board::sowNorth(int hole, int& endHole, int& nbeans)
{
    for(int i = hole; nbeans > 0 && i >= 1; i--)
    {
        m_North[i] += 1;
        nbeans--;
        //Returns endHole if appropriate.
        if(nbeans == 0)
            endHole = i;
    }

}

//Sows South CounterClockwise
void Board::sowSouth(int hole, int& endHole, int& nbeans)
{
    for(int i = hole; nbeans > 0 && i < m_nHoles + 1; i++)
    {
        m_South[i] += 1;
        nbeans--;
        //Returns endHole if appropriate.
        if(nbeans == 0)
            endHole = i;
    }
}

//Empties the specified hole.
void Board::empty(Side s, int hole)
{
    if(s == Side::NORTH)
        m_North[hole] = 0;
    else
        m_South[hole] = 0;
}
