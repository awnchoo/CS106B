#include "Boggle.h"
#include "shuffle.h"
#include "random.h"
#include "bogglegui.h"
// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    BoggleDict=dictionary;
    BoggleText.resize(4,4);
    BoggleGUI::initialize(4,4);
    if(boardText.empty()){
        shuffle(CUBES,16);
        int p=0;
        for(int i =0;i<BoggleText.numRows();i++){
            for(int j=0;j<BoggleText.numCols();j++){
                BoggleText[i][j]=CUBES[p][randomInteger(0,5)];
                BoggleGUI::labelCube(i,j,BoggleText[i][j],false);
                p++;
            }
        }
    }else{
        int p=0;
        BoggleGUI::labelAllCubes(boardText);
        for(int i =0;i<BoggleText.numRows();i++){
            for(int j=0;j<BoggleText.numCols();j++){
                BoggleText[i][j]=boardText[p];
                p++;
            }
        }
    }

}

char Boggle::getLetter(int row, int col) {
    if(!BoggleText.inBounds(row,col))
        throw int();
    return BoggleText[row][col];
}

bool Boggle::checkWord(string word) {
    word=toLowerCase(word);
    if(word.size()<4||Words.contains(word)||!BoggleDict.contains(word)){
        return false;
    }else{
        return true;
    }
}

bool Boggle::humanWordSearch(string word) {
    Grid<char> marked;
    marked.resize(4,4);
    word=toUpperCase(word);
    string temp="";
    for(int i=0;i<marked.numRows();i++){
        for(int j=0;j<marked.numCols();j++){
           if(HumanSearchHelper(word,i,j,marked,temp))
              return true;
        }
    }
    return false;
}
bool Boggle::HumanSearchHelper(const string word,int row,int col,Grid<char>& marked,string temp){
    if(!marked.inBounds(row,col)){
        return false;
    }else if(marked[row][col]=='1'){
        return false;
    }else{
        string s(1,BoggleText[row][col]);
        temp+=s;
        if(temp==word.substr(0,temp.size())){
            if(word.size()==temp.size()){
                BoggleGUI::setHighlighted(row,col,true);
                HumanScore++;
                HumanWords.add(word);
                Words.add(word);
                BoggleGUI::recordWord(word,BoggleGUI::HUMAN);
                marked[row][col]='0';
                return true;
            }
            marked[row][col]='1';
            BoggleGUI::setHighlighted(row,col,true);

            for(int i=row-1;i<=row+1;i++){
                for(int j=col-1;j<=col+1;j++){
                        if(HumanSearchHelper(word,i,j,marked,temp))
                            return true;
                }
            }
            marked[row][col]='0';
            BoggleGUI::setHighlighted(row,col,false);
            return false;
        }
        return false;
   }
};
int Boggle::getScoreHuman() {
    return HumanScore;
}

Set<string> Boggle::computerWordSearch() {
    Set<string> result;
    Grid<char> marked;
    marked.resize(4,4);
    string temp="";
    for(int i=0;i<marked.numRows();i++){
        for(int j=0;j<marked.numCols();j++){
           ComSearchHelper(i,j,marked,temp,result);
        }
    }
    return result;
}
void Boggle::ComSearchHelper(int row,int col,Grid<char>& marked,string temp,Set<string>& result){
    if(marked.inBounds(row,col)&&marked[row][col]!='1'){
        string s(1,BoggleText[row][col]);
        temp+=s;
            if(checkWord(temp)){
                ComputerScore++;
                ComputerWords.add(temp);
                result.add(temp);
                Words.add(temp);
                BoggleGUI::recordWord(temp,BoggleGUI::COMPUTER);
            }
            marked[row][col]='1';
            for(int i=row-1;i<=row+1;i++){
                for(int j=col-1;j<=col+1;j++){
                     ComSearchHelper(i,j,marked,temp,result);
                }
            }
            marked[row][col]='0';
   }
};
int Boggle::getScoreComputer() {
    return ComputerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    for(int i=0;i<boggle.BoggleText.numRows();i++){
        for(int j = 0;j<boggle.BoggleText.numCols();j++){
            cout<<boggle.BoggleText[i][j];
        }
        cout<<endl;
    }
    return out;
}
Set<string> Boggle::gethumanwords(){
    return HumanWords;
};
