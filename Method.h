#ifndef METHOD_H
#define METHOD_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Method {
public:
    virtual void compute() = 0;
    void print(vector<vector<double>> data, string nameFile, double dx);
};

#endif