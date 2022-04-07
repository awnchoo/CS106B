#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"

using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    Set<string> gethumanwords();
    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    int HumanScore=0;
    int ComputerScore=0;
    Grid<char> BoggleText;
    Lexicon BoggleDict;
    Set<string> HumanWords;
    Set<string> ComputerWords;
    Set<string> Words;

    bool HumanSearchHelper(const string word,int row,int col,Grid<char>& marked,string temp);
    void ComSearchHelper(int row,int col,Grid<char>& marked,string temp,Set<string>& result);
};

#endif // _boggle_h
