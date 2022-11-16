#pragma once

#include <vector>
#include <iostream>
#include <numeric>
#include <cmath>
#include <limits>

class TestHelper
{
public:
    TestHelper();

public:
    void RunMeasurementTest();
    void ShowMeasurements();
    void ExportMeasurements();

private:
    void GenerateDoubles();
    void GenerateFloates();

private:
    void WindowSizeMeasurementTest();
    void TypeMeasurementTest();

public:
    template <typename T>
    static bool CompareAnswers(const std::vector<T> & first, const std::vector<T> & second)
    {
        if (first.size() != second.size())
        {
            return false;
        }

        for (size_t i = 0; i < first.size(); ++i)
        {
            if (std::fabs(first[i] - second[i]) > std::numeric_limits<T>::epsilon())
            {
                std::cout << "Result of the funtion is incorrect.\n";
                std::cout << "Different answers: diff = " << first[i] - second[i] << ", At = " << i << "\n";
                std::cout << "First = " << first[i] << ", Second = " << second[i] << "\n";
                return false;
            }
        }

        std::cout << "Result of the function is correct.\n";
        return true;
    }

public:
    static double randomD(double min, double max)
    {
        double ran = (double) rand() / RAND_MAX;
        return min + ran * (max - min);
    }
    
private:
    template <typename T>
    std::vector<T> GenerateVector()
    {
        std::vector<T> v;
        for (int i = 0; i < totalValues; ++i)
        {
            v.push_back(TestHelper::randomD(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max()));
        }

        return v;
    }
private:
    const int totalValues = 10000000;
    std::vector<double> double_data;
    std::vector<float>  float_data;

    std::vector<int> windowSizeMeasurements;
    std::vector<int> windowSizeMeasurementsFloat;
    std::vector<int> typeMeasurements;
};