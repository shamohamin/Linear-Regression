#include "linear_regression.hpp"
#include "data_reader.hpp"
#include "config.hpp"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iomanip>
using namespace std;

const double LinearRegression::ALPHA = 0.9;
const double LinearRegression::GAMA = 0.01;

LinearRegression::LinearRegression()
{
    srand(time(0));
    dataset = DataReader(DATASET_FILE_PATH);
    dataset.execute();
    for (int i = 0; i < dataset.get_number_of_features(); i++)
    {
        double r = (rand() / (double)(RAND_MAX)) + 1;
        theta.push_back(rand());
    }
}

void LinearRegression::gredient_decesnt()
{
    vector<double> X_SAMPLES = dataset.get_x_samples();
    vector<double> Y_SAMPLES = dataset.get_y_samples();
    double diff_value = 0.0;
    vector<double> x;
    x.push_back(1);
    vector<double> sim;

    for (int i = 0; i < theta.size(); i++)
    {
        diff_value = 0.0;
        double x_product = 1;
        for (int j = 0; j < X_SAMPLES.size(); j++)
        {
            if (i != 0)
            {
                x_product = X_SAMPLES[j];
            }
            x.push_back(X_SAMPLES[j]);
            diff_value += (((-this->hypotesis(x) + Y_SAMPLES[j])) * x_product);
            x.pop_back();
        }
        sim.push_back(((ALPHA * (-(1.0 / X_SAMPLES.size())) * diff_value)));
    }

    for (int i = 0; i < theta.size(); i++)
    {
        if (i == 0)
        {
            theta[i] = theta[i] - sim[i];
        }
        else
        {
            theta[i] = (theta[i] * (1 - ((double)(ALPHA * GAMA) / X_SAMPLES.size()))) - sim[i];
        }
    }
}

double LinearRegression::cost_function()
{
    vector<double> X_SAMPLES = dataset.get_x_samples();
    vector<double> Y_SAMPLES = dataset.get_y_samples();
    double diff_value = 0.0;
    double thetas = 0.0;
    vector<double> x;
    x.push_back(1);

    for (int i = 0; i < X_SAMPLES.size(); i++)
    {
        x.push_back(X_SAMPLES[i]);
        double predict_value = (this->hypotesis(x) - Y_SAMPLES[i]);
        diff_value += (predict_value * predict_value);
        x.pop_back();
    }

    for (int i = 0; i < theta.size(); i++)
    {
        thetas += theta[i] * theta[i];
    }

    return ((1.0 / (2 * X_SAMPLES.size())) * (diff_value + (GAMA * thetas)));
}

double LinearRegression::hypotesis(vector<double> x)
{
    double value = 0.0;
    for (int i = 0; i < x.size(); i++)
    {
        value += theta[i] * x[i];
    }
    return value;
}

void LinearRegression::run()
{
    double min_cost = 1000000.0;
    int itr = 0;

    while (1)
    {
        double cost = cost_function();
        if (cost <= min_cost)
        {
            min_cost = cost;
        }
        gredient_decesnt();
        if (itr == 10000)
        {
            break;
        }
        itr++;
    }
    cout << fixed;
    cout << setprecision(10);
    cout << theta[0] << ":" << theta[1] << ":" << min_cost;
}

LinearRegression::~LinearRegression()
{
}