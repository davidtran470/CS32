
#include <iostream>
#include <sstream>  // for istringstream and ostringstream
#include <string>
#include <cassert>
#include "Compressor.h"
#include "HashTable.h"
using namespace std;

void runtest(string oldtext, string newtext)
{
    istringstream oldFile(oldtext);
    istringstream newFile(newtext);
    ostringstream diffFile;
    createDiff(oldFile, newFile, diffFile);
    string result = diffFile.str();
    cout << "The diff file length is " << result.size()
    << " and its text is " << endl;
    cout << result << endl;

    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the stream
    istringstream diffFile2(result);
    ostringstream newFile2;
    assert(applyDiff(oldFile, diffFile2, newFile2));
    assert(newtext == newFile2.str());
}

int main()
{
    runtest("There's a bathroom on the right.",
            "There's a bad moon on the rise.");
    runtest("ABCDEFGHIJBLAHPQRSTUVPQRSTUV",
            "XYABCDEFGHIJBLETCHPQRSTUVPQRSTQQELF");
    cout << "All tests passed" << endl;
    }
