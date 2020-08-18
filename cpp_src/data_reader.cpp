#include <iostream>
#include <vector>
#include "data_reader.hpp"
#include <fstream>
#include <numeric>
#include <string>
#include <unistd.h>
using namespace std;

DataReader::DataReader() {}

DataReader::DataReader(const char *data_filename)
{
    this->filename = (char *)malloc(200 * sizeof(char));
    this->filename = data_filename;
    this->number_of_features = 2;
}

void DataReader::read_file()
{
    string line;
    ifstream myfile(this->filename);
    if (myfile.is_open())
    {
        try
        {
            while (getline(myfile, line))
            {
                int index = line.find(',');
                string x = line.substr(0, index);
                string y = line.substr(index + 1, line.length());
                this->x_samples.push_back(stoi(x));
                this->y_samples.push_back(stoi(y));
            }
        }
        catch (char *excp)
        {
            cout << "Caught " << excp;
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

vector<double> DataReader::get_x_samples()
{
    return this->x_samples;
}

vector<double> DataReader::get_y_samples()
{
    return this->y_samples;
}

int DataReader::get_number_of_features()
{
    return this->number_of_features;
}

void DataReader::execute()
{
    this->read_file();

    double X_min = *min_element(this->x_samples.begin(), this->x_samples.end());
    double X_max = *max_element(this->x_samples.begin(), this->x_samples.end());
    // double Y_min = *min_element(this->y_samples.begin(), this->y_samples.end());
    // double Y_max = *max_element(this->y_samples.begin(), this->y_samples.end());

    for (int i = 0; i < x_samples.size(); i++)
    {
        x_samples[i] = ((double)((double)x_samples[i] - X_min) / (double)(X_max - X_min));
        // y_samples[i] = ((double)((double)y_samples[i] - Y_min) / (double)(X_max - X_min));
    }
}

DataReader::~DataReader()
{
}