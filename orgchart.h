//
// Created by astro on 1/26/2024.
//

#ifndef PROJECTS_ORGCHART_H
#define PROJECTS_ORGCHART_H
#include <iostream>
#include <cstring>
using namespace std;
class orgchart {
public:
    orgchart(const char *maxChildrenPath, unsigned int levelMax);
    orgchart(unsigned int maxChild, const char *Id, int lenID);
    orgchart **children;
    int maxLevel;
    const char* employeeID;
    int maxChild;

    bool addEmployees(const char *employeeIDPath);

    orgchart *findEmployee(const char *employeeIDPath);

    void countNumOfEmployeesInOrgchart(unsigned int &count);

    int *maxChildren;

    char *add_char(char *first, char second, int lenFirst);
    ~orgchart();
};

#endif //PROJECTS_ORGCHART_H
