//
//  History.cpp
//  CSProject2
//
//  Created by Tran on 4/4/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    int r, c;
    for (r = 0; r < nRows; r++)
        for (c = 0; c < nCols; c++)
            datasheet[r][c] = 0;
}

bool History::record(int r, int c)
{
    if(r <= 0  ||  c <= 0  ||  r > m_rows  ||  c > m_cols)
    {
        return false;
    }
    else
    {
        datasheet[r - 1][c - 1] += 1;
        return true;
    }
}

void History::display() const
{
    // Position (row,col) of the arena coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            grid[r][c] = '.';
    
    // Indicate each location (and amount of times) where the player killed a zombie
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            const int& data = datasheet[r][c];
            char& gridChar = grid[r][c];
            switch (data)
            {
                case 0:
                    break;
                default:
                    if(data >= 26)
                    {
                        gridChar = 'Z';
                    }
                    else
                    {
                        gridChar = 'A' + (data - 1);
                    }
                    break;  // '1' through '25'
            }
        }
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
}
