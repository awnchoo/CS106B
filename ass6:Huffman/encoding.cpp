#include "encoding.h"
#include "pqueue.h"
#include "filelib.h"
Map<int, int> buildFrequencyTable(istream& input) {
    Map<int, int> freqTable;
    char c;
    while((c=input.get())!=EOF){
        int i=static_cast<int>(c);
        if(freqTable.containsKey(i)){
            freqTable[i]++;
        }else{
            freqTable.add(i,1);
        }
    }
    freqTable.add(PSEUDO_EOF,1);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> queue;
    for(auto key:freqTable){
        HuffmanNode* pnode=new HuffmanNode(key,freqTable[key],nullptr,nullptr);
        queue.enqueue(pnode,freqTable[key]);
    }
    while(queue.size()!=1){
        HuffmanNode* newnode = new HuffmanNode();
        int leftPriority=queue.peekPriority();
        newnode->zero = queue.peek();
        queue.dequeue();
        int rightPriority=queue.peekPriority();
        newnode->one = queue.peek();
        queue.dequeue();
        newnode->count=leftPriority+rightPriority;
        queue.enqueue(newnode,newnode->count);
    }
    HuffmanNode* tree =queue.peek();
    return tree;
}
void buildEncodingHelper(Map<int, string>& encodemap,HuffmanNode* encodingTree,string temp);

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    buildEncodingHelper(encodingMap,encodingTree,"");
    return encodingMap;
}
void buildEncodingHelper(Map<int, string>& encodemap,HuffmanNode* encodingTree,string temp){
    if(encodingTree==nullptr){
        return;
    }else{
        if(encodingTree->character!=NOT_A_CHAR){
            encodemap.add(encodingTree->character,temp);
        }
        buildEncodingHelper(encodemap,encodingTree->zero,temp+"0");
        buildEncodingHelper(encodemap,encodingTree->one,temp+"1");
    }
}
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    char c;
    string code="";
    while((c=input.get())!=EOF){
        int key=static_cast<int>(c);
        code+=encodingMap[key];
    }
    code+=encodingMap[PSEUDO_EOF];
    for(unsigned int i=0;i<code.size();i++){
        output.writeBit(code[i]-'0');
    }
}
int decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree);
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    char c;
    while(!input.fail()){
        c=decodeDataHelper(input,encodingTree);
        if(c==-1){
            break;
        }
        output.put(c);
    }
}
int decodeDataHelper(ibitstream& input, HuffmanNode* encodingTree){
    if(encodingTree->character!=NOT_A_CHAR){
        return encodingTree->character;
    }else{
        if(input.fail()){
            return -1;
        }
        if(input.readBit()==0){
            return decodeDataHelper(input,encodingTree->zero);
        }else{
            return decodeDataHelper(input,encodingTree->one);
        }
    }
}
void compress(istream& input, obitstream& output) {
    Map<int, int> freqTable=buildFrequencyTable(input);
    HuffmanNode*tree= buildEncodingTree(freqTable);
    Map<int, string> encodemap= buildEncodingMap(tree);
    output<<freqTable;
    rewindStream(input);
    encodeData(input,encodemap,output);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int,int> freqTable;
    input>>freqTable;
    HuffmanNode*tree= buildEncodingTree(freqTable);
    decodeData(input,tree,output);
}

void freeTree(HuffmanNode* node) {
    if(node!=nullptr){
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
