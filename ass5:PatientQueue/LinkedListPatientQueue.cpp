
#include "LinkedListPatientQueue.h"
#include "strlib.h"
LinkedListPatientQueue::LinkedListPatientQueue() {
    head=nullptr;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    LinkedListPatientQueue::clear();
}

void LinkedListPatientQueue::clear() {
    PatientNode* curP=head;
    PatientNode* delP=nullptr;
    while(curP!=nullptr){
        delP=curP;
        curP=curP->next;
        delete delP;
    };
    head=nullptr;
}

string LinkedListPatientQueue::frontName() {
    if(isEmpty()){
        throw "no patient now.";
    }else
        return head->name;
}

int LinkedListPatientQueue::frontPriority() {
    if(isEmpty()){
        throw "no patient now.";
    }else
        return head->priority;   // this is only here so it will compile
}

bool LinkedListPatientQueue::isEmpty() {

    return head==nullptr;   // this is only here so it will compile
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    PatientNode* newpatient = new PatientNode(name,priority);
    PatientNode* curP=head;
    if(head==nullptr){
        head=newpatient;
    }else if(head->priority>priority){
        newpatient->next=head->next;
        head=newpatient;
    }
    else{
        while(curP->next!=nullptr&&(curP->next)->priority<=priority){
            curP=curP->next;
        }
        newpatient->next=curP->next;
        curP->next=newpatient;
    }

}

string LinkedListPatientQueue::processPatient() {
    if(head==nullptr)
        throw "no patient now.";
    string name=head->name;
    PatientNode* delP=head;
    head=head->next;
    delete delP;
    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    PatientNode* curP=head;
    PatientNode* delP=nullptr;
    if(head==nullptr){
        throw "no patient now";
    }
    while(curP->name!=name){
        delP=curP;
        curP=curP->next;
        if(curP==nullptr){
            throw "no such patient";
        }
    }
    delP->next=curP->next;
    delete curP;
    newPatient(name,newPriority);
}

string LinkedListPatientQueue::toString() {
    string output="{";
    PatientNode* curP=head;
    while(curP!=nullptr){
        output+=integerToString(curP->priority,10);
        output+=":";
        output+=curP->name;
        output+=", ";
        curP=curP->next;
    }
    output+="}";
    return output;
}
