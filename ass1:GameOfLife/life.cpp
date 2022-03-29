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
void setcolony_y(Grid<char>& colony,Grid<char>& subcol,LifeGUI& life);
void setcolony_n(Grid<char>& colony,Grid<char>& subcol,LifeGUI& life);
void printcol(Grid<char>&);
void welcome();


int main() {
    LifeGUI life;
    ifstream input;
    string filename;
    bool wrapping;
    char c=0;
    welcome();
    inputfile(input,filename);
    InitializeLife(life);
    Grid<char> colony(row,col);
    Grid<char> subcol(row,col);
    InitializeColony(colony,input,life);
    wrappingindicator(wrapping);
    menu(c,colony,subcol,wrapping,life);
    cout << "Have a nice Life!" << endl;
    return 0;
}

bool inputfile(ifstream& input,string & filename){
    cout<<"Grid input file name? ";
    getline(cin,filename);
    while(!fileExists(filename)){
      cout<<"Unable to open that file.  Try again. "<<endl;
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
    cout<<"Should the simulation wrap around the grid(y/n)?";
    char ch;
    cin>>ch;
    if(toupper(ch)=='Y'){
        wrapping=true;
    }else{
        wrapping=false;
    }
};
void menu(char& c,Grid<char>& colony,Grid<char>& subcol,const bool & wrapping,LifeGUI& life){
    int frames=0;
    printcol(colony);
    cout << "\nA)inmate, T)ick, Q)uit? ";
    cin >> c;
        while (!cin || (cin.peek() != '\n')) {
            cout << "Invalid input, try again.\n";
            cin.clear();
            cin.ignore(999, '\n');
            cout << "\nA)inmate, T)ick, Q)uit? ";
            cin >> c;
        }

    switch(c){
    case'a':
    case'A':
        cout << "How many frames? ";

        while(!(cin>>frames)){
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
    default:
        cout<<"Invalid choice; please try again."<<endl;
        menu(c,colony,subcol,wrapping,life);
        break;
    }
};

void animate(Grid<char>& colony,Grid<char>& subcol,const int frames,const bool wrapping,LifeGUI& life){
    for(int i =0;i<frames;i++){
        if(wrapping){
            setcolony_y(colony,subcol,life);
        }else{
            setcolony_n(colony,subcol,life);
        }
        pause(500);
        if(frames!=1)
        clearConsole();
    }
}

void setcolony_y(Grid<char>& colony,Grid<char>& subcol,LifeGUI& life){
    int neighbours=0;
    for(int i = 0;i<row;i++){
        for(int j=0;j<col;j++){
            for(int m=i-1;m<=i+1;m++){
                for(int n=j-1;n<=j+1;n++){
                    if(colony[(m+row)%row][(n+col)%col]=='X')
                        neighbours++;
                }
            }
            neighbours=neighbours-(colony[i][j]=='X');

            if(neighbours<=1||neighbours>=4){
                subcol[i][j]='-';
            }else if(neighbours==2){
                subcol[i][j]=colony[i][j];
            }else if(neighbours==3){
                subcol[i][j]='X';
            }
            life.drawCell(i,j,subcol[i][j]=='X');
            neighbours=0;
        }
    }
    colony=subcol;
};
void setcolony_n(Grid<char>& colony,Grid<char>& subcol,LifeGUI& life){
    int neighbours=0;
    for(int i = 0;i<row;i++){
        for(int j=0;j<col;j++){
            for(int m=i-1;m<=i+1;m++){
                for(int n=j-1;n<=j+1;n++){
                    if(n>=0&&n<col&&m>=0&&m<row)
                       if(colony[m][n]=='X')
                          neighbours++;
                }
            }
            neighbours=neighbours-(colony[i][j]=='X');

            if(neighbours<=1||neighbours>=4){
                subcol[i][j]='-';
            }else if(neighbours==2){
                subcol[i][j]=colony[i][j];
            }else if(neighbours==3){
                subcol[i][j]='X';
            }
            life.drawCell(i,j,subcol[i][j]=='X');
            neighbours=0;
        }
    }
    colony=subcol;
};
void printcol(Grid<char>& colony){
    for(int i = 0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<colony[i][j];
        }
        cout<<endl;
    }
};
void welcome(){
    cout<<"Welcome to the CS 106B Game of Life,"<<endl;
    cout<<"a simulation of the lifecycle of a bacteria colony."<<endl;
    cout<<"Cells (X) live and die by the following rules:"<<endl;
    cout<<"- A cell with 1 or fewer neighbors dies."<<endl;
    cout<<"- Locations with 2 neighbors remain stable."<<endl;
    cout<<"- Locations with 3 neighbors will create life."<<endl;
    cout<<"- A cell with 4 or more neighbors dies."<<endl;
};
