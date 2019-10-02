//
//  Compressor.hpp
//  CompressionOppression
//
//  Created by Tran on 5/30/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef Compressor_h
#define Compressor_h
#include <iostream>
#include <fstream>
using namespace std;
void createDiff(istream& fold, istream& fnew, ostream& fdiff);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);
bool getInt(istream& inf, int& n);
bool getCommand(istream& inf, char& cmd, int& length, int& offset);


#endif /* Compressor_h */
