
#ifndef MYTEST_HPP
#define MYTEST_HPP

/* ************************************************************************** */

#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include "../vector/vector.hpp"

using namespace std;
typedef unsigned long ulong;

void chooseStructureNType();
void initializeHTOpnAdr();
void initializeHTClsAdr();
void sharedMenu();
void intSharedMenu();
void floatSharedMenu();
void stringSharedMenu();
void populateIntVector(lasd::Vector<int>& vec);
void populateFloatVector(lasd::Vector<double>& vec);
void populateStringVector(lasd::Vector<string>& vec);
string getRandomString(int n);
void printIntElement(int& element, void* b);
void printFloatElement(double& element, void* b);
void printStringElement(string& element, void* b);
void multiplyIntLessThan(const int element, const void* n, void* prod);
void sumFloatGreatherThan(const double element, const void* n, void* sum);
void concatenateStrings(const string element, const void* length, void* conc);

/* ************************************************************************** */

#endif
