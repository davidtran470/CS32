//
//  History.hpp
//  CSProject2
//
//  Created by Tran on 4/4/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef History_h
#define History_h
#include "globals.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int datasheet[MAXROWS][MAXCOLS]; //Datasheet to keep track of the places that player has killed zombie
};

#endif /* History_hp */
