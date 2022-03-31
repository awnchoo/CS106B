#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "hashmap.h"
#include "vector.h"
#include "queue.h"
#include "random.h"
using namespace std;
void openfile(ifstream& input);
void welcome();
int getN();
int totalwords(int n);
void makemap(ifstream& input,int N,HashMap<Vector<string>,Vector<string>>& map);
void generate(int n,HashMap<Vector<string>,Vector<string>>& map);
int main() {
    welcome();
    ifstream input;
    openfile(input);
    HashMap<Vector<string>,Vector<string>> map;
    int N=getN();
    makemap(input,N,map);
    int n;
    n=totalwords(N);
    while(n){
        generate(n,map);
        n=totalwords(N);
    }
    cout << "Exiting." << endl;
    return 0;
}

void welcome(){
    cout<<"Welcome to CS 106B Random Writer ('N-Grams').\n";
    cout<<"This program makes random text based on a document.\n";
    cout<<"Give me an input file and an 'N' value for groups\n";
    cout<<"of words, and I'll create random text for you.\n";
}
void openfile(ifstream& input){
    string filename;
    cout<<"Input file name?";
    getline(cin,filename);
    if(!fileExists(filename)){
        cout<<"Unable to open that file.  Try again.\n";
        cout<<"Input file name?";
        getline(cin,filename);
    }
    input.open(filename);
}
int getN(){
    cout<<"Value of N?";
    char N;
    N=cin.get();
    while(cin.peek()!='\n'||!isdigit(N)||N<50){

        if(cin.peek()!='\n'||!isdigit(N)){
            cout<<"Illegal integer format. Try again.\n";
            cout<<"Value of N?";
            cin.clear();
            cin.ignore(99,'\n');
            N=cin.get();
        }
        if(N<50){
            cout<<"N must be 2 or greater.\n";
            cout<<"Value of N?";
            cin.clear();
            cin.ignore(99,'\n');
            N=cin.get();
        }
    }
    N=N-48;
    return N;
}
int totalwords(int n){
    cout<<"# of random words to generate (0 to quit)?";
    int size;
    cin>>size;
    while(!cin||size<n){
        if(size==0)
            break;
        cout<<"# of words should be greater than N.\n";
        cout<<"# of random words to generate (0 to quit)?";
        cin>>size;
    }
    return size;
};
void makemap(ifstream& input,int N,HashMap<Vector<string>,Vector<string>>& map){
    Vector<string> window,suffix;
    Queue<string> wrap;
    string word;
    int windowsize = N-1;
    for(int i=0;i<windowsize;i++){
        input>>word;
        window.add(word);
        wrap.enqueue(word);
    }
    while(input>>word){
        suffix.add(word);
        if (map.containsKey(window)) {
             map[window].add(word);
        } else {
            suffix.add(word);
            map.put(window, suffix);
        }
        window.remove(0);
        window.add(word);
        suffix.clear();
    }
    //deal with the wrap
    for(int i=0;i<windowsize;i++){
        if(!wrap.isEmpty()){
            word=wrap.dequeue();
            suffix.add(word);
            if (map.containsKey(window)) {
                 map[window].add(word);
            } else {
                suffix.add(word);
                map.put(window, suffix);
            }
            window.remove(0);
            window.add(word);
            suffix.clear();
        }
    }

};
void generate(int n,HashMap<Vector<string>,Vector<string>>& map){
    cout<<"...";
    string word;
    Vector<string> window=randomKey(map);
    for(int i=0;i<n;i++){
        cout<<window[0]<<" ";
        word=randomElement(map[window]);
        window.remove(0);
        window.add(word);
    }
    cout<<"...\n";

};
