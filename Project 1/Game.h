//
//  Game.hpp
//  CSProject2
//
//  Created by Tran on 4/4/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include "Arena.h"
class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    int decodeDirection(char dir);
};
#endif /* Game_h */
