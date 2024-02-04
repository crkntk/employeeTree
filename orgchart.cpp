//
// Created by astro on 1/26/2024.
//

#include "orgchart.h"
#include <cctype>
#include <cstring>

orgchart:: orgchart(const char *maxChildrenPath, unsigned int levelMax){
    //Constructor for Root node
    maxChild = 0; //initialization for maxChild root node doesnt need this so its set to zero
    const char *initPointer;
    maxLevel = levelMax; //This is the max levels allowed on the tree
    maxChildren = new int[levelMax]; //initialization for array of the node level of allowed max children for each node
    int counter = 0;
    children = nullptr;
    char* resultID = new char[3]; //Id of the root node initialization and copying
    strcpy(resultID, "e_\0");
    employeeID = resultID;
    for(initPointer = maxChildrenPath; *initPointer != '\0'; initPointer++){ // parsing to creating the maxChildren per node array
        if(isdigit(*initPointer) && *initPointer != ' '){
            maxChildren[counter] = *initPointer - 48;
            counter++;
        }
    }
    initPointer = nullptr;
    delete(initPointer);
    children =  new orgchart*[maxChildren[0]];
    for(int i = 0; i < maxChildren[0]; i++){ //initializing the children
        children[i] = nullptr;
    }
    resultID = nullptr;
    delete[] (resultID);
}
orgchart::orgchart(unsigned int maxCh, const char *Id, int lenID){
    //Constructor for child nodes
    children = nullptr;
    maxLevel = 0;
    maxChild = maxCh; //Set max children for current node
    employeeID = Id;
    char* resultID = new char[lenID + 1]; //instantiating the id
    strcpy(resultID, Id); // copying id
    employeeID = resultID; //seting id
    children =  new orgchart*[maxChild];
    for(unsigned int i = 0; i< maxCh; i++){ // instantiating children array
        children[i] = nullptr;
    }
    resultID = nullptr;
    delete[] (resultID);
}

bool orgchart::addEmployees(const char *employeeIDPath){
    //This function adds employees starting from root down the path stops when invalid and keeps the past added notes
    const char *initPointer;
    int currLevel = 1; // root node is the zero level so we start at level 1 of the tree
    orgchart* currNode = this; // sets the curr node to parse from current node
    int IDLen = 2; // the length of the id
    char* resultID = new char[IDLen + 1]; // instantiating with the ending character \0
    strcpy(resultID, "e_"); //since root node already made we start with this parse string
    for(initPointer = employeeIDPath+2; *initPointer != '\0'; initPointer++){
        //starts at first id since we already have the root node
        char* teRes = add_char(resultID, *initPointer, IDLen);
      //This frees up memory in case we have our pointer not the same as our result id we want for the node
        if (teRes != resultID) {
            delete[] resultID;
        }
        resultID = teRes;
        IDLen++;
        if(!isdigit(*initPointer) && *initPointer != '_'){ // checks if invalid character so this for loop is stopped
            break;
        }
        if(isdigit(*initPointer) && (maxChildren[currLevel - 1] <= ((int)*initPointer - 48))){ // checks for if its a digit and its max children for node
            break;
        }
        if(maxLevel < currLevel || (((*initPointer != '_' && !isdigit(*initPointer))) && (maxChildren[currLevel - 1] < ((int)*initPointer - 48)))){
            // checks the max level and curent level and if its also not a valid id
        break;
        }
        if(isdigit(*initPointer)) {
            if ((currNode->children[(int) *initPointer - 48] != nullptr)) { //if the node exists
                currNode = currNode->children[(int) *initPointer - 48];
                currLevel++;
                continue;
            }
            if (currNode->children[(int) *initPointer - 48] == nullptr) { //it node doesnt exist it creates it
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
        if(!isdigit(*initPointer) && *initPointer != '_'){ //checks if its not a valid id in the string
            return nullptr;
        }
        if(currNode == NULL || currNode == nullptr){//if the node down the path doesnt exist it exits and return nullptr
            return nullptr;
            break;
        }
        if((*initPointer != '_' && !isdigit(*initPointer))){ //checks again if it has a valid id
            break;
        }
        if(isdigit(*initPointer) && (maxChildren[currLevel-1] <= ((int)*initPointer - 48))){ //checks max children
            return nullptr;
            break;
        }
        else if(isdigit(*initPointer) && (*initPointer != '_')) { //valid id
            if ((currNode->children[(int) *initPointer - 48] != nullptr)) {//if we have a valid node found we go down the tree
                currNode = currNode -> children[(int) *initPointer - 48];
                currLevel++;
            }
            else if (currNode->children[(int) *initPointer - 48] == nullptr) { //if the node doesnt exist we reutrn null ptr
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

    orgchart* currNode = this;//starts at the curren node to iterate
    if(currNode == nullptr || currNode->children == NULL){ //if we have a null node then we exit
        return;
    }
    orgchart* curNode;

    for(int curr = 0; curr != maxChild; curr++){ // Visits and counts each child that is not a null ptr
        if(currNode->children[curr] == nullptr){
            continue;
        }
        else {
            count++;
        }
    }

    for(int curr = 0; curr != maxChild; curr++){ // Visits the children recursively
        curNode = children[curr];
        if(currNode->children[curr] == nullptr){
            continue;
        }
        curNode->countNumOfEmployeesInOrgchart(count);
    }
}
char* orgchart::add_char(char *first, char second, int lenFirst ){
    //This functions copies onto another string
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

