# Employee Tree
Implemented a tree data structure to store and retrieve the organization chart information, as
well as write code for testing your implementation.
1) Tree operations:
a. Add employees identified along an employee ID path to the organization chart,
see below for elaboration and examples.
b. Find an employee in the organization chart based on an employee ID path.
c. Count number of employees in the organization chart starting from an
employee ID path.
2) Test code (see program execution and required output below):
a. Read an org chart file that has the information of levels and employee ID paths
to build an org chart.
b. Read another file containing employee ID paths, and for each employee ID path
read, count, and print the number of employees starting from it in the org
chart.


To compile code, simply type make at the prompt. For the C++ version, make
will execute compilation similar to the following if you do not have any errors:
g++ -std=c++11 -Wall -g3 -c orgchart.cpp
g++ -std=c++11 -Wall -g3 -c countOrgEmployees.cpp
g++ -o countEmployees orgchart.o countOrgEmployees.o
