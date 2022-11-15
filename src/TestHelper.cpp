#include "TestHelper.h"
#include "SMA.h"

#include <chrono>
#include <fstream>

TestHelper::TestHelper()
{
    windowSizeMeasurements.reserve(6);
    windowSizeMeasurementsFloat.reserve(6);
    typeMeasurements.reserve(2);
    GenerateDoubles();
    GenerateFloates();
}

void TestHelper::RunMeasurementTest()
{
    WindowSizeMeasurementTest();
    TypeMeasurementTest();
}

void TestHelper::ShowMeasurements()
{
    std::cout << "Window size measurement on double values:\n";
    std::cout << "Window size:\t\tValue:\n";
    for (size_t i = 0; i < windowSizeMeasurements.size(); ++i)
    {
        std::cout << (int) pow(2, i+2) << "\t\t\t" << windowSizeMeasurements[i] << "\n";
    }

    std::cout << "Window size measurement on float values:\n";
    std::cout << "Window size:\t\tValue:\n";
    for (size_t i = 0; i < windowSizeMeasurementsFloat.size(); ++i)
    {
        std::cout << (int) pow(2, i+2) << "\t\t\t" << windowSizeMeasurementsFloat[i] << "\n";
    }

    std::cout << "Type measurement (float/double):\n";
    std::cout << "Type:\t\tValue:\n";
    std::cout << "double\t\t" << typeMeasurements[0] << "\n";
    std::cout << "float\t\t" << typeMeasurements[1] << "\n";
}

void TestHelper::ExportMeasurements()
{
    std::ofstream file;
    file.open("results.csv");
    file << "Window size measurements\n";
    file << "4," << windowSizeMeasurements[0] << ",\n";
    file << "8," << windowSizeMeasurements[1] << ",\n";
    file << "16," << windowSizeMeasurements[2] << ",\n";
    file << "32," << windowSizeMeasurements[3] << ",\n";
    file << "64," << windowSizeMeasurements[4] << ",\n";
    file << "128," << windowSizeMeasurements[5] << ",\n";
    file << "Window size measurements (float)\n";
    file << "4," << windowSizeMeasurementsFloat[0] << ",\n";
    file << "8," << windowSizeMeasurementsFloat[1] << ",\n";
    file << "16," << windowSizeMeasurementsFloat[2] << ",\n";
    file << "32," << windowSizeMeasurementsFloat[3] << ",\n";
    file << "64," << windowSizeMeasurementsFloat[4] << ",\n";
    file << "128," << windowSizeMeasurementsFloat[5] << ",\n";
    file << "Type measurements\n";
    file << "double," << typeMeasurements[0] <<",\n";
    file << "float," << typeMeasurements[1];
    file.close();
}

void TestHelper::GenerateDoubles()
{
    double_data = GenerateVector<double>();
}

void TestHelper::GenerateFloates()
{
    float_data = GenerateVector<float>();
}

void TestHelper::WindowSizeMeasurementTest()
{
    for (size_t windowSize = 4; windowSize <= 128; windowSize *= 2)
    {
        auto start = std::chrono::high_resolution_clock::now();
        ComputeSMA(windowSize, double_data);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> total = end-start;
        windowSizeMeasurements.push_back(totalValues / total.count());
    }

    for (size_t windowSize = 4; windowSize <= 128; windowSize *= 2)
    {
        auto start = std::chrono::high_resolution_clock::now();
        ComputeSMA(windowSize, float_data);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> total = end-start;
        windowSizeMeasurementsFloat.push_back(totalValues / total.count());
    }
}

void TestHelper::TypeMeasurementTest()
{
    auto start = std::chrono::high_resolution_clock::now();
    ComputeSMA(64, double_data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total = end-start;

    typeMeasurements.push_back(totalValues / total.count());

    start = std::chrono::high_resolution_clock::now();
    ComputeSMA(64, float_data);
    end = std::chrono::high_resolution_clock::now();
    total = end-start;

    typeMeasurements.push_back(totalValues / total.count());
}
