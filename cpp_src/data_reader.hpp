#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef DATA_READER_H
#define DATA_READER_H

class DataReader
{
private:
    const char *filename;
    int number_of_features;
    vector<double> x_samples;
    vector<double> y_samples;

public:
    DataReader(const char *);
    DataReader();
    void read_file();
    void execute();
    vector<double> get_x_samples();
    vector<double> get_y_samples();
    int get_number_of_features();
    ~DataReader();
};

#endif