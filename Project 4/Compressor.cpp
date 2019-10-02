//
//  Compressor.cpp
//  CompressionOppression
//
//  Created by Tran on 5/30/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include "Compressor.h"
#include "HashTable.h"
void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    string oldstr;
    string newstr;
    char s;
    
    //Stores the data in the input stream into a string for both the old and the new input streams.
    while(fold.get(s))
        oldstr += s;
    while(fnew.get(s))
        newstr += s;

    //Create the Hashtable to house the old values
    HashTable table;
    
    //Depending on the size of the oldstr choose the appropriate Sequence length
    if(oldstr.size() <= 1000)
        SEQUENCE_LENGTH = 8;
    else
        SEQUENCE_LENGTH = 16;
    
    //Put the value of the old file into the hash table.
    for(int i = 0; i  + SEQUENCE_LENGTH < oldstr.size(); i++)
    {
        string temp = oldstr.substr(i, SEQUENCE_LENGTH);
        table.additem(temp, i);
    }

    //Search the values of the new file and see if we can find it in the hashtable of the old file.
    int j = 0;
    while(j < newstr.size())
    {
        int L = 0;
        int offset = table.find(newstr.substr(j, SEQUENCE_LENGTH), oldstr, newstr, j, L);
        //If we find the N-sequence string in the hashtable of the old file.
        if(offset != -1)
        {
            fdiff << "C" << L << "," << offset;
            j += L;
        }
        //Else the the N-sequence string was not found in the hashtable of the old file.
        else
        {
            //Temporarily holds the strings
            int size = 0;
            string holder;
            holder += newstr.at(j);
            int temp = j + 1;
            L = 1;
            while(temp < newstr.size() && table.find(newstr.substr(temp, SEQUENCE_LENGTH), oldstr, newstr, temp, size) == -1)
            {
                holder += newstr.at(temp);
                L++;
                temp++;
            }
            fdiff << "A" << L << ":" << holder;
            j += L;
        }
    }

}
//
//
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    int length;
    int offset;
    char cmd;
    string oldstr;
    char s;
    while(fold.get(s))
        oldstr += s;
    //Get the commands using a while loop. Stops if the we reach a invalid state
    while(getCommand(fdiff, cmd, length, offset))
    {
        switch(cmd)
        {
            //If we have reached the end of the file return
            case 'x':
            {
                return true;
                break;
            }
            case 'A':
            {
                char holder;
                for(int i = 0; i < length; i++)
                {
                    //If it hasn't reached the end, add the character to the new file.
                    if(fdiff.get(holder))
                    {
                        cout << holder;
                        fnew << holder;
                    }
                    //If it was reached the end without the loop terminating.
                    else
                        return false;
                }
                break;
            }
            case 'C':
            {
                //Check that the offset and the length are the appropriate values.
                if((offset >= 0 && offset < oldstr.length()) && offset + length <= oldstr.length())
                {
                    cout << oldstr.substr(offset, length);
                    fnew << oldstr.substr(offset, length);
                }
                //If not return false
                else
                    return false;
                break;
            }
        }
    }
    cout << endl;
    //Return false if we do not meet the end.
    return false;
}

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

//Gets the command and its corresponding values via pass-by-reference. Returns false, if it fails.
bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
        case '\r':
        case '\n':
            return true;
    }
    return false;
}
