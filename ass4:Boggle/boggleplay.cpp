#include "lexicon.h"
#include "Boggle.h"
#include "bogglegui.h"
#include "simpio.h"
using namespace std;
void getText(string& BoardText);
void humanturn(Boggle& Bog);
void computerturn(Boggle& Bog);
void playOneGame(Lexicon& dictionary) {
       string BoardText;

       getText(BoardText);
       Boggle Bog(dictionary,BoardText);
       humanturn(Bog);
       computerturn(Bog);
       if(Bog.getScoreComputer()<=Bog.getScoreHuman()){
           cout<<"You win!";
       }else{
           cout<<"Ha ha ha, I destroyed you. Better luck next\ntime, puny human!";
       }
}
void getText(string& BoardText){
    cout<<"Enter 16 char or Empty to generate a random board:";
    BoardText="";
    getline(cin,BoardText);
    while(BoardText.size()!=0&&BoardText.size()!=16){
        cout<<"Enter 16 char or Empty:";
        BoardText="";
        getline(cin,BoardText);
    }
};
void humanturn(Boggle& Bog){
    string word="";
    cout<<"It's your turn!"<<endl;
    cout<<Bog;
    cout<<"Type a word (or Enter to stop):";
    getline(cin,word);
    while(word!=""){
        if(Bog.checkWord(word)&&Bog.humanWordSearch(word)){
            BoggleGUI::setStatusMessage(word);
            cout<<"You found a new word!" <<word<<endl;
        }else{
            cout<<"Invalid word. Try again."<<endl;
        }
        cout<<"Type a word (or Enter to stop):";
        word="";
        getline(cin,word);
    }
    cout<<"Your words:"<<Bog.gethumanwords()<<endl;
    cout<<"Your score:"<<Bog.getScoreHuman()<<endl;
    BoggleGUI::setScore(Bog.getScoreHuman(),BoggleGUI::HUMAN);
};
void computerturn(Boggle& Bog){
    cout<<"It's my turn!"<<endl;
    cout<<"My words:"<<Bog.computerWordSearch()<<endl;
    cout<<"My score:"<<Bog.getScoreComputer()<<endl;
};
