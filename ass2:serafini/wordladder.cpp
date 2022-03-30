// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "filelib.h"
#include "queue.h"

using namespace std;
void welcome();
void readindic(Lexicon & words);
bool getword(const int i,string & w);
void validtect(Lexicon & words,const string w1,const string w2);
bool wordladder(Lexicon & words,const string w1,const string w2);
void findneighbours(Vector<string> &v,Lexicon& words,string w1);
int main() {
    welcome();
    Lexicon words;
    string w1,w2;
    readindic(words);
    while(getword(1,w1)&&getword(2,w2))
        validtect(words,w1,w2);
    cout << "Have a nice day." << endl;
    return 0;
}

void welcome(){
    cout<<"Welcome to CS 106B Word Ladder."<<endl;
    cout<<"Please give me two English words, and I will change the"<<endl;
    cout<<"first into the second by changing one letter at a time."<<endl<<endl;
};
void readindic(Lexicon & words){
    string file;
    cout<<"Dictionary file name?";
    getline(cin,file);
    while(!fileExists(file)){
        cout<<"Unable to open that file.  Try again."<<endl;
        cin>>file;
    }
    words.addWordsFromFile(file);
};
bool getword(const int i,string & w){
    cout<<"Word #"<<i<<" (or Enter to quit):";
    getline(cin,w);
    if(w.empty()){
        return false;
    }else{
        w=toLowerCase(w);
        return true;
    }
};
void validtect(Lexicon & words,const string w1,const string w2){
    if(w1.length()!=w2.length()){
        cout<<"The two words must be the same length."<<endl;
    }
    else if(w1==w2){
        cout<<"The two words must be different."<<endl;
    }
    else if(!words.contains(w1)||!words.contains(w2)){
        cout<<"The two words must be found in the dictionary."<<endl;
    }
    else{
        wordladder(words,w1,w2);
    }
}
bool wordladder(Lexicon & words,const string w1,const string w2){
    Queue<Stack<string>> queue;
    Stack<string> s;
    s.push(w1);
    queue.enqueue(s);
    Set<string> usedwords;
    usedwords.add(w1);
    while(!queue.isEmpty()){
        Stack<string> stack=queue.dequeue();
        Vector<string> neighbours;
        string now=stack.peek();
        findneighbours(neighbours,words,now);
        for(int i=0;i<neighbours.size();i++){
            string neighbour=neighbours[i];
            if(!usedwords.contains(neighbour)){
                if(neighbour==w2){
                    stack.add(neighbour);
                    while(!stack.isEmpty())
                        cout<<stack.pop()<<" ";
                    cout<<endl;
                    return true;
                }else{
                    auto newstack=stack;
                    newstack.push(neighbour);
                    queue.enqueue(newstack);
                    usedwords.add(neighbour);
                }
            }
        }
    }
    cout<<"no way"<<endl;
    return true;
}

void findneighbours(Vector<string> &v,Lexicon& words,string w1){
    string w=w1;
    for(unsigned int i=0;i<w.length();i++){
        char c=w[i];
        w1=w;
        for(char ch='a';ch<='z';ch++){
            if(ch!=c){
                w1[i]=ch;
                if(words.contains(w1)){
                    v.add(w1);
                }
            }
        }
    }
};
