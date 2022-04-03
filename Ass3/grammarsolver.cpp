/*
 * File: grammarsolver.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "map.h"
#include "random.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
void grammarHelper(Map<string,Vector<string>>& grammar,string symbol,string& result);
void openfile(istream& input,Map<string,Vector<string>>& grammar);
Vector<string> grammarGenerate(istream& input, string symbol,int times) {
    // TODO: write this function
    Map<string,Vector<string>> grammar;
    openfile(input,grammar);
    Vector<string> results;
    for(int i = 0;i<times;i++){
        string result;
        grammarHelper(grammar,symbol,result);
        result=trim(result);
        results.add(result);
    }

    return results;           // This is only here so it will compile
}
void openfile(istream& input,Map<string,Vector<string>>& grammar){
    string line;
    while(getline(input,line)){
        Vector<string> v=stringSplit(line,"::=");
        Vector<string> temp=stringSplit(v[1],"|");
        grammar.add(v[0],temp);
    }
};
void grammarHelper(Map<string,Vector<string>>& grammar,string symbol,string& result){
        if(grammar.containsKey(symbol)){
            string rand = randomElement(grammar[symbol]);
            if(stringContains(rand," ")){
                Vector<string> subsyms=stringSplit(rand," ");
                for(int i =0;i<subsyms.size();i++){
                    grammarHelper(grammar,subsyms[i],result);
                }
            }else{
                grammarHelper(grammar,rand,result);
            }
        }else{
            result+=symbol+" ";
        }
}
