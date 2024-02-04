//
// Created by astro on 1/26/2024.
//
#include <iostream>
#include <fstream>
#include "orgchart.h"
#include <cstring>
#include <string>

int parse_max(const char *maxLevelPath){
    //This parses the first lines to get the array of maxes for each level that will be assigned to root node
    const char *initPointer;
    int maxLevel;
    for(initPointer = maxLevelPath; *initPointer != '\0'; initPointer++){
        if(isdigit(*initPointer)){
            maxLevel = *initPointer - 48;
        }
    }
    return maxLevel;
    initPointer = nullptr;
    delete(initPointer);
}

int main(int argc, char **argv){
    char *orgchartFilePath = argv[argc - 2];
    char *testFilePath = argv[argc - 1];
    std::ifstream firstFile(orgchartFilePath);
    std::string line;
    int lineNum;
    int maxL;
    lineNum = 0;
    orgchart *root;
    while (getline(firstFile, line)){ // Constructs the tree by reading in each line in first argument file
        if(lineNum == 0){
            maxL = parse_max(line.c_str());
            lineNum++;
            continue;
        }
        if(lineNum == 1){
            root = new orgchart(line.c_str(), maxL);
            lineNum++;
            continue;
        }
        root->addEmployees(line.c_str());
        lineNum++;
    }
    firstFile.close();
    ifstream secondFile(testFilePath);
    orgchart *currNode;
    while (getline(secondFile, line)){ //processes the second argument file and finds node and counts its employees
        unsigned count = 1;
        currNode = root->findEmployee(line.c_str());
        if(currNode == nullptr || currNode == NULL){
            cout << line.c_str();
        }
        else {
            cout << currNode->employeeID;
        }
        if(currNode == nullptr){
            count = 0;
        }
        else {
            currNode->countNumOfEmployeesInOrgchart(count);
        }
        cout << " " ;
        cout << count;
        cout << "\n";
    }
    //deallocating memory for pointers
    currNode = nullptr;
    delete currNode;
    root = nullptr;
    delete root;
}

