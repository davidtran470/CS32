//
//  Game.cpp
//  Kalah
//
//  Created by Tran on 5/13/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include "Game.h"

Game::Game(const Board& b, Player* south, Player* north)
:m_b(b), m_south(south), m_north(north), m_turn(true)
{
    if( south == nullptr || north == nullptr)
    {
        cerr << "Error!, you cannot pass a null pointer.";
        exit(1);
    }
}

//Displays the Board
void Game::display() const
{
    unsigned long size = m_north -> name().size() + 11;
    //add spaces before
    unsigned long mid = size + ((m_b.holes()-1)*2) + (m_b.holes()/2) - 1;
    addspace(mid);
    cout << m_north -> name() << endl << endl;
    addspace(size);
    for(int i = 0; i < m_b.holes(); i++)
    {
        cout << "-----";
    }
    cout << endl;
    addspace(size);
    for(int i = 1; i <= m_b.holes(); i++)
    {
        cout << "  " << m_b.beans(Side::NORTH, i) << "  ";
    }
    cout << endl << endl;
    cout << m_north -> name() << "'s Pot";
    cout << "    " << m_b.beans(Side::NORTH, 0);
    for(int i = 0; i < (m_b.holes()*2)*2 + m_b.holes();i++)
    {
        cout << " ";
    }
    cout <<  m_b.beans(Side::SOUTH, 0) << "    ";
    cout << m_south -> name() << "'s Pot";
    cout << endl << endl;
    addspace(size);
    for(int i = 1; i <= m_b.holes(); i++)
    {
        cout << "  " << m_b.beans(Side::SOUTH, i) << "  ";
    }
    cout << endl;
    addspace(size);
    for(int i = 0; i < m_b.holes(); i++)
    {
        cout << "-----";
    }
    cout << endl << endl;
    addspace(mid);
    cout << m_south-> name() << endl;
    cout << endl;
}

//Displays the status of the Game.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    //If neither of the sides are empty, the game is still not over.
    if(!(m_b.beansInPlay(Side::NORTH) == 0 || m_b.beansInPlay(Side::SOUTH) == 0))
        over = false;
    else
    {
        over = true;
        //If North Wins
        if(m_b.beans(Side::NORTH, 0) > m_b.beans(Side::SOUTH, 0))
        {
            hasWinner = true;
            winner = Side::NORTH;
        }
        //If South Wins
        else if(m_b.beans(Side::NORTH, 0) < m_b.beans(Side::SOUTH, 0))
        {
            hasWinner = true;
            winner = Side::SOUTH;
        }
        //If there is a tie
        else
            hasWinner = false;
    }
}

//Makes the move.
bool Game::move()
{
    bool over;
    bool hasWinner;
    Side winner;
    status(over, hasWinner, winner);
    //If the Game is Over
    
    if(over)
    {
        ifover();
        return false;
    }
    //If it is south's turn.
    if(m_turn)
    {
//        movePlayer(m_south, Side::SOUTH);
        int hole = - 1;
        bool temp = sowrules(m_south, Side::SOUTH, hole);
        if(!m_south->isInteractive())
            cout << m_south->name() << " chose to move hole " << hole << "." << endl;
        display();
        if(!temp)
        {
            status(over, hasWinner, winner);
            if(!over)
            {
                cout << "Last bean landed in " << m_south->name() << "'s pot. "<< m_south->name() << " gets one more turn." << endl;
                move();
            }
        }
        status(over, hasWinner, winner);
        if (over)
            ifover();
        m_turn = false;
    }
    //If it is north's turn.
    else
    {
//        movePlayer(m_north, Side::NORTH);
        int hole = - 1;
        bool temp = sowrules(m_north, Side::NORTH, hole);
        display();
        if(!m_north->isInteractive())
            cout << m_north->name() << " chose to move hole " << hole << "." << endl;
        if(!temp)
        {
            status(over, hasWinner, winner);
            if(!over)
            {
                cout << "Last bean landed in " << m_north->name() << "'s pot. "<< m_north->name() << " gets one more turn." << endl;
                move();
            }
        }
        status(over, hasWinner, winner);
        if (over)
            ifover();
        m_turn = true;
    }
    return true;
}

void Game::play()
{
    cout << "           ...............WELCOME TO KULAH...............   " << endl;
    cout << "Press ENTER to create the Board! " << endl;
    //Prompt for player to put in ENTER.
    cin.clear();
    cin.ignore(9999, '\n');
    display();
    bool over;
    bool hasWinner;
    Side winner;
    //Repeatedly call move until the game is over.
    for(;;)
    {
        cout << "Press ENTER to continue. ";
        cin.ignore(9999, '\n');
        move();
        status(over, hasWinner, winner);
        if(over)
            break;
    }
    display();
    cout << "Game is over!" << endl;
    status(over, hasWinner, winner);
    if(hasWinner)
    {
        if(winner == Side::SOUTH)
            cout << m_south->name() << " is the winner!" << endl;
        else
            cout << m_north->name() << " is the winner!" << endl;
        
    }
    else
    {
        cout<< "Tie. There is no winner." << endl;
    }
    
}

int Game::beans(Side s, int hole) const
{
    return m_b.beans(s, hole);
}

//Add space to help with the display.
void Game::addspace(unsigned long size) const
{
    for(unsigned long i = 0; i < size; i++)
    {
        cout << " ";
    }
}

//If the game is over, sweep the board. Move the remaining beans into their respective player's pot.
void Game::ifover()
{
    for(int i = 1; i <= m_b.holes(); i++)
    {
        m_b.moveToPot(Side::SOUTH, i, Side::SOUTH);
        m_b.moveToPot(Side::NORTH, i, Side::NORTH);
    }
}

//Sow the Game with the rules applied, it the player get to go again, return false.
bool Game::sowrules(Player* side, Side s, int& hole)
{
    int holetosow;
    holetosow = side->chooseMove(m_b, s);
    hole = holetosow;
    Side endSide;
    int endHole;
    m_b.sow(s, holetosow, endSide, endHole);
    if(endSide == s)
    {
        //If it is your pot, you get to go again. returns false
        if(endHole == 0)
            return false;
        //Capture
        else if (m_b.beans(s, endHole) == 1 && m_b.beans(opponent(s), endHole) != 0)
        {
            m_b.moveToPot(opponent(s), endHole, s);
            m_b.moveToPot(s, endHole, s);
        }
    }
    return true;
}

