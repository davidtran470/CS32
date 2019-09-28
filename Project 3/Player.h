//
//  Player.h
//  Kalah
//
//  Created by Tran on 5/13/19.
//  Copyright © 2019 Tran. All rights reserved.
//


#ifndef Player_h
#define Player_h
#include "Side.h"
#include "Board.h"
#include <string>
#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};

class Player
{
    public:
        Player(std::string name);
        std::string name() const;
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const = 0;
        virtual ~Player();
    private:
        string m_name;
    };

class HumanPlayer: public Player
{
    public:
        HumanPlayer(std::string name);
        virtual bool isInteractive() const;
        virtual int chooseMove(const Board& b, Side s) const;
        virtual ~HumanPlayer();
};

class BadPlayer: public Player
{
    public:
        BadPlayer(std::string name);
        virtual int chooseMove(const Board& b, Side s) const;
        virtual ~BadPlayer();
};

class SmartPlayer: public Player
{
    public:
        SmartPlayer(std::string name);
        virtual int chooseMove(const Board& b, Side s) const;
        virtual ~SmartPlayer();
    private:
        //Evaluates the position on the board based on the given heuristics
        double evaluate(Board b, Side s) const;
        //Tranverses all the possible moves and returns the max or min value depending on if the player is the maximizer or the minimizer
        int minimax(Board b, bool isMax, Side s, int depth, AlarmClock & ac) const;
        //Decides if there are moves left
        bool aremovesleft (const Board& b, Side s) const;
        //Sows the seeds with the rules applied
        //If Player gets to go again, function will return false;
        bool sowwithrules(Board& b, int hole, Side s) const;
};


#endif /* Player_h */
