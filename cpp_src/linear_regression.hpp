#include <iostream>
#include "data_reader.hpp"
using namespace std;
#define SIZE 100

#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

class LinearRegression
{
private:
    DataReader dataset;
    static const double ALPHA;
    static const double GAMA;
    vector<double> theta;
    void gredient_decesnt();
    double cost_function();
    double hypotesis(vector<double> x);
public:
    LinearRegression();
    void run();
    ~LinearRegression();
};


#endif 