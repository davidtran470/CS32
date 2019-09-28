//
//  Player.cpp
//  Kalah
//
//  Created by Tran on 5/13/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include "Player.h"


Player::Player(std::string name)
:m_name(name)
{}

std::string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
{
    //Defaults to false because most players are computer players.
    return false;
}

Player::~Player()
{}

HumanPlayer::HumanPlayer(std::string name)
:Player(name)
{
}

//Human is an interactive player.
bool HumanPlayer::isInteractive() const
{
    return true;
}

//HumanPlayer implementation of chooseMove.
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    //If there are no moves possible.
    if(b.beansInPlay(s) == 0)
        return -1;
    int move;
    //Contiuously prompt until valid user input is reached.
    for(;;)
    {
        cout << name() << " 's turn. Please enter a valid move. " ;
        cin >> move;
        if(move >= 1 && move <= b.holes() && b.beans(s, move) != 0)
        {
            return move;
        }
        cin.clear(); //This corrects the stream.
        cin.ignore(); //Ignores leftover
    }
}

HumanPlayer::~HumanPlayer()
{}

BadPlayer::BadPlayer(std::string name)
:Player(name)
{}

//Bad Player implementation of chooseMove() function. BadPlayer
//will choose the leftmost possible move for both sides.
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    //If no moves are possible
    if(b.beansInPlay(s) == 0)
        return -1;
    int move = 1;
    while(move <= b.holes())
    {
        if(b.beans(s, move) != 0)
            break;
        move++;
    }
    return move;
}

BadPlayer::~BadPlayer()
{}

SmartPlayer::SmartPlayer(std::string name)
:Player(name)
{}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    AlarmClock ac(1900);
    //If the game has ended
    if(!aremovesleft(b, s))
        return -1;
    
    //Track the hole number and the value
    int bestvalue = -INT_MAX;
    int bestmove = -1;
    //Iterate through all the possible moves.
    for(int i = 1; i <= b.holes(); i++)
    {
        //If it is a possible move.
        if(b.beans(s, i) != 0)
        {
            int value;
            //Create new board so that current board is not manipulated
            Board temp = b;
            //If we get to go again.
            if(!sowwithrules(temp, i, s))
                value = minimax(temp, true, s, 7, ac);
            //If we don't get to go again.
            else
               value = minimax(temp, false, opponent(s), 7, ac);
            //Determine which path maximizes the value
            if(value >= bestvalue)
            {
                bestvalue = value;
                bestmove = i;
            }
        }
    }
    return bestmove;
}

//Evaluates how good the position is for the player
double SmartPlayer::evaluate(Board b, Side s) const
{
    //Check if the game is won, which player has won.
    if(!aremovesleft(b, s))
    {
        //Sweep the board, so that remaining seeds go to pots
        for(int i = 1; i <= b.holes(); i++)
        {
            b.moveToPot(Side::SOUTH, i, Side::SOUTH);
            b.moveToPot(Side::NORTH, i, Side::NORTH);
        }
        //If the player wins, return INT_MAX,
        if(b.beans(s, 0) > b.beans(opponent(s), 0))
            return INT_MAX;
        //If opponent wins, this is bad for player, return -INT_MAX,
        else if (b.beans(opponent(s), 0) > b.beans(s, 0))
            return -INT_MAX;
        //If there is a tie. This neither good nor bad for the player.
        else
            return 0;
    }
    double score = 0;
    //If the player has the majority of beans, this means a victory for that player.
    if(b.beans(s, 0) > (b.totalBeans()/2))
        score +=  b.totalBeans()*2;
    
    //If opponent has the majority of beans, this means a victory for the opponent.
    if (b.beans(opponent(s), 0) > (b.totalBeans()/2))
        score -= -b.totalBeans()*2;
    
    //Adjust the score by the heuristic: greater difference of beans in pot is good for the player.
    score += b.beans(s, 0) - b.beans(opponent(s), 0);
    //Adjust the score by the heuristic: greater differenec moves between the player and opponent is good
    for(int i = 0; i <= b.holes(); i++)
    {
        if (b.beans(s, i) != 0)
            score += .25;
        if(b.beans(opponent(s), i) != 0)
            score -= .25;
    }
    
    //As the game progresses, it becomes increasingly important to have a good amount of moves
    //Add more weight to this heuristic.
    if(b.beansInPlay(s) + b.beansInPlay(opponent(s)) < b.totalBeans()/4)
    {
        for(int i = 0; i <= b.holes(); i++)
        {
            if (b.beans(s, i) != 0)
                score += .75;
            if(b.beans(opponent(s), i) != 0)
                score -= .75;
        }
    }
            
    return score;
}

//Minimax function considers the possible paths of the board and returns
//the maximum or minimum value of the given board.
int SmartPlayer::minimax(Board b, bool isMax, Side s, int depth, AlarmClock & ac) const
{
    //If is the maximer
    int score;
    if(isMax)
        score = evaluate(b, s);
    //If not the maximer, we have to evaluate the maximer's side.
    else
        score = evaluate(b, opponent(s));
    
    //Terminating condition is when there are no moves left.
    if(!aremovesleft(b, s))
        return score;
    //If timer runs out before depth is reached
    if(ac.timedOut())
        return score;
    //If the depth we want is reached, stop the recursion.
    if(depth == 0)
        return score;


    //If this is the Maximizer's move
    if(isMax)
    {
        int bestvalue = -INT_MAX;
        //Iteratate through all possible moves(holes)
        for(int i = 1; i <= b.holes(); i++)
        {
            //If it is a possible move.
            if(b.beans(s, i) != 0)
            {
                Board temp = b;
                //If the player gets to repeat his move
                if(!sowwithrules(b, i, s))
                {
                    //We are only concerned with maximum value of the possible extra moves that player can make.
                    int temp = minimax(b, isMax, s, depth - 1, ac);
                    bestvalue = max(bestvalue, temp);
                }
                //The player's turn has ended.
                else
                {
                    //Recursion to get the best value that the minimum player has to offer.
                    bestvalue = max(bestvalue, minimax(b, !isMax, opponent(s), depth - 1, ac));
                }
                //Reset the board
                b = temp;
            }
        }
        return bestvalue;
    }

   //If this is the Minimizer's move
    else
    {
        int bestvalue = INT_MAX;
        //Iteratate through all possible moves(holes)
        for(int i = 1; i <= b.holes(); i++)
        {
            //If it is a possible move.
            if(b.beans(s, i) != 0)
            {
                Board temp = b;
                //If the player gets to repeat his move
                if(!sowwithrules(b, i, s))
                {
                    //We are only concerned with minimum value of the possible extra moves that player can make.
                    int temp = minimax(b, isMax, s, depth - 1, ac);
                    bestvalue = min(bestvalue, temp);
                }
                //The player's turn has ended.
                else
                {
                    //Minimizer wants to get the minimum value.
                    bestvalue = min(bestvalue, minimax(b, !isMax, opponent(s), depth - 1, ac));
                }
                //Reset the board
                b = temp;
            }
        }
        return bestvalue;
    }
}

//Checks if there are moves left in the game.
bool SmartPlayer::aremovesleft (const Board& b, Side s) const
{
    if(b.beansInPlay(s) == 0)
        return false;
    return true;
}

//Function to sow the seeds with the appropriate rules applied. If player gets to go again, turn is not finished: return false.
bool SmartPlayer::sowwithrules(Board& b, int hole, Side s) const
{
    Side endSide;
    int endHole;
    b.sow(s, hole, endSide, endHole);
    if(endSide == s)
    {
        //If it is your pot, you get to go again. returns false
        if(endHole == 0)
            return false;
        //Capture
        else if (b.beans(s, endHole) == 1 && b.beans(opponent(s), endHole) != 0)
        {
            b.moveToPot(opponent(s), endHole, s);
            b.moveToPot(s, endHole, s);
        }
    }
    return true;
}

SmartPlayer::~SmartPlayer()
{}





