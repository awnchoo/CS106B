//  life.cpp
//
//  Created by Jian Zhong on 5/29/20.
//  Copyright © 2020 Jian Zhong. All rights reserved.
//***********************************************************************

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
#include "gevents.h"
using namespace std;
int row=0,col=0;
bool inputfile(ifstream& input,string & filename);
bool InitializeColony(Grid<char>& colony,ifstream& input,LifeGUI & life);
bool InitializeLife(LifeGUI & life);
void menu(char& c,Grid<char>&,Grid<char>&,const bool&,LifeGUI& life);
void wrappingindicator(bool & wrapping);
void animate(Grid<char>& colony,Grid<char>& subcol,const int frames,const bool wrapping,LifeGUI& life);
int main() {
    LifeGUI life;
    ifstream input;
    string filename;
    bool wrapping;
    char c;
    inputfile(input,filename);
    InitializeLife(life);
    Grid<char> colony(row,col);
    Grid<char> subcol(row,col);
    InitializeColony(colony,input,life);
    wrappingindicator(wrapping);
    menu(c,colony,subcol,wrapping,life);
    for(int i = 0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<colony[i][j];
        }
        cout<<endl;
    }
    cout << "Have a nice Life!" << endl;
    return 0;
}
bool inputfile(ifstream& input,string & filename){
    cout<<"Grid input file name? ";
    getline(cin,filename);
    while(!fileExists(filename)){
      cout<<"File doesn't exits. Try again"<<endl;
      getline(cin,filename);
    }
    openFile(input,filename);
    input>>row>>col;
    return true;
};
bool InitializeLife(LifeGUI & life){
    life.resize(row,col);
    return true;
}
bool InitializeColony(Grid<char>& colony,ifstream& input,LifeGUI & life){
        for(int i = 0;i<row;i++){
            for(int j=0;j<col;j++){
                input>>colony[i][j];
                life.drawCell(i,j,colony[i][j]=='X');
            }
        }

    return true;
};
void wrappingindicator(bool & wrapping){
    cout<<"Should the simulation wrap around the grid(y/n)?"<<endl;
    char ch;
    cin>>ch;
    if(toupper(ch)=='Y'){
        wrapping=true;
    }else{
        wrapping=false;
    }
};
void menu(char& c,Grid<char>& colony,Grid<char>& subcol,const bool & wrapping,LifeGUI& life){
    int frames;
    cout<<"a)nimate, t)ick, q)uit? ";
    cin>>c;
    if(!cin||toupper(c)!='A'||toupper(c)!='T'||toupper(c)!='Q'){
        cout<<"Input wrong. Try again. ";
    }
    switch(c){
    case'a':
    case'A':
        cout << "How many frames? ";
        cin >> frames;
        while(!isdigit(frames)){
            cout<<"Input wrong. Try again. ";
            cin>>frames;
        }
        animate(colony,subcol,frames,wrapping,life);
        menu(c,colony,subcol,wrapping,life);
        break;
    case't':
    case'T':
        animate(colony,subcol,1,wrapping,life);
        menu(c,colony,subcol,wrapping,life);
        break;
    case'q':
    case'Q':
        break;
    }
};
void animate(Grid<char>& colony,Grid<char>& subcol,const int frames,const bool wrapping,LifeGUI& life){

}
