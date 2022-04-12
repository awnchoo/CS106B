
#include "VectorPatientQueue.h"
int VectorPatientQueue::highestIndex(){
    int highestPriority=patients[0].priority;
    int Index=0;
    for(int i=0;i<patients.size();i++){
        if(patients[i].priority<highestPriority){
            highestPriority=patients[i].priority;
            Index=i;
        }
    }
    return Index;
}
VectorPatientQueue::VectorPatientQueue() {
    patients={};
}

VectorPatientQueue::~VectorPatientQueue() {}

void VectorPatientQueue::clear() {
    patients.clear();
}

string VectorPatientQueue::frontName() {
    if(patients.isEmpty())
        throw "no patient now.";
    return patients[highestIndex()].name;
}
int VectorPatientQueue::frontPriority() {
    if(patients.isEmpty())
        throw "no patient now.";
    return patients[highestIndex()].priority;
}

bool VectorPatientQueue::isEmpty() {
    return patients.isEmpty();
}

void VectorPatientQueue::newPatient(string name, int priority) {
    struct patient newpatient = {name,priority};
    patients.add(newpatient);
}

string VectorPatientQueue::processPatient() {
    if(patients.isEmpty()){
        throw "no patient now.";
    }else{
        int index=highestIndex();
        string name=patients[index].name;
        patients.remove(index);
        return name;
    }
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    int index=-1;
    for(int i=0;i<patients.size();i++){
        if(patients[i].name==name){
            index=i;
            patients[i].priority=newPriority;
        }
    }
    if(index==-1){
        throw "the patient do not exits";
    }
}

string VectorPatientQueue::toString() {
    string output="{";
    for(int i=0;i<patients.size();i++){
        output+=integerToString(patients[i].priority,10);
        output+=":";
        output+=patients[i].name;
        output+=", ";
    }
    output+="}";
    return output;
}
