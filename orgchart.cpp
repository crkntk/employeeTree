//
// Created by astro on 1/26/2024.
//

#include "orgchart.h"
#include <cctype>
#include <cstring>

orgchart:: orgchart(const char *maxChildrenPath, unsigned int levelMax){
    //Constructor for Root node
    maxChild = 0;
    const char *initPointer;
    maxLevel = levelMax;
    maxChildren = new int[levelMax];
    int counter = 0;
    children = nullptr;
    char* resultID = new char[3];
    strcpy(resultID, "e_\0");
    employeeID = resultID;
    for(initPointer = maxChildrenPath; *initPointer != '\0'; initPointer++){
        if(isdigit(*initPointer) && *initPointer != ' '){
            maxChildren[counter] = *initPointer - 48;
            counter++;
        }
    }
    initPointer = nullptr;
    delete(initPointer);
    children =  new orgchart*[maxChildren[0]];
    for(int i = 0; i < maxChildren[0]; i++){
        children[i] = nullptr;
    }
    resultID = nullptr;
    delete[] (resultID);
}
orgchart::orgchart(unsigned int maxCh, const char *Id, int lenID){
    //Constructor for child nodes
    children = nullptr;
    maxLevel = 0;
    maxChild = maxCh;
    employeeID = Id;
    char* resultID = new char[lenID + 1];
    strcpy(resultID, Id);
    employeeID = resultID;
    children =  new orgchart*[maxChild];
    for(unsigned int i = 0; i< maxCh; i++){
        children[i] = nullptr;
    }
    resultID = nullptr;
    delete[] (resultID);
}

bool orgchart::addEmployees(const char *employeeIDPath){
    //This function adds employees starting from root down the path stops when invalid and keeps the past added notes
    const char *initPointer;
    int currLevel = 1;
    orgchart* currNode = this;
    int IDLen = 2;
    char* resultID = new char[IDLen + 1];
    strcpy(resultID, "e_");
    for(initPointer = employeeIDPath+2; *initPointer != '\0'; initPointer++){
        char* teRes = add_char(resultID, *initPointer, IDLen);
      //This frees up memory in case we have our pointer not the same as our result id we want for the node
        if (teRes != resultID) {
            delete[] resultID;
        }
        resultID = teRes;
        IDLen++;
        if(!isdigit(*initPointer) && *initPointer != '_'){
            break;
        }
        if(isdigit(*initPointer) && (maxChildren[currLevel - 1] <= ((int)*initPointer - 48))){
            break;
        }
        if(maxLevel < currLevel || (((*initPointer != '_' && !isdigit(*initPointer))) && (maxChildren[currLevel - 1] < ((int)*initPointer - 48)))){
        break;
        }
        if(isdigit(*initPointer)) {
            if ((currNode->children[(int) *initPointer - 48] != nullptr)) {
                currNode = currNode->children[(int) *initPointer - 48];
                currLevel++;
                continue;
            }
            if (currNode->children[(int) *initPointer - 48] == nullptr) {
                currNode->children[(int) *initPointer - 48] = new orgchart(maxChildren[currLevel], resultID, IDLen);
                currNode = currNode->children[(int) *initPointer - 48];
                currLevel++;
            }
        }
    }
    // memory deallocation for pointer
    initPointer = nullptr;
    delete initPointer;
    return true;
}

orgchart* orgchart::findEmployee(const char *employeeIDPath){
    //This function finds the employee in employee path and returns null ptr if not found or invalid path
    const char *initPointer;
    orgchart* currNode = this;
    int currLevel = 1;
    for(initPointer = employeeIDPath + 2; *initPointer != '\0'; initPointer++){
        // this loop iterates over the path and starts at first level
        if(!isdigit(*initPointer) && *initPointer != '_'){
            return nullptr;
        }
        if(currNode == NULL || currNode == nullptr){
            return nullptr;
            break;
        }
        if((*initPointer != '_' && !isdigit(*initPointer))){
            break;
        }
        if(isdigit(*initPointer) && (maxChildren[currLevel-1] <= ((int)*initPointer - 48))){
            return nullptr;
            break;
        }
        else if(isdigit(*initPointer) && (*initPointer != '_')) {
            if ((currNode->children[(int) *initPointer - 48] != nullptr)) {
                currNode = currNode -> children[(int) *initPointer - 48];
                currLevel++;
            }
            else if (currNode->children[(int) *initPointer - 48] == nullptr) {
                return nullptr;
            }
        }
    }
    initPointer = nullptr; // memory allocated released
    delete initPointer;
    return currNode;
}
void orgchart::countNumOfEmployeesInOrgchart (unsigned int &count){
    // This function counts the employees under the current node and visits and counts in bfs order

    orgchart* currNode = this;
    if(currNode == nullptr || currNode->children == NULL){
        return;
    }
    orgchart* curNode;

    for(int curr = 0; curr != maxChild; curr++){ // Visits and counts each child
        if(currNode->children[curr] == nullptr){
            continue;
        }
        else {
            count++;
        }
    }

    for(int curr = 0; curr != maxChild; curr++){ // Visits the children
        curNode = children[curr];
        if(currNode->children[curr] == nullptr){
            continue;
        }
        curNode->countNumOfEmployeesInOrgchart(count);
    }
}
char* orgchart::add_char(char *first, char second, int lenFirst ){
    char *result = new char[lenFirst+ 2];
    char endStr[2];
    endStr[0]=second;
    endStr[1]= '\0';
    strcpy(result, first);
    strcat(result, endStr);
    return result;
}

//////change

orgchart::~orgchart() {
    // this is a destructor
    delete[] maxChildren;
    for (int i = 0; i < maxChild; ++i) {
        delete children[i];
    }
    delete[] children;
}

