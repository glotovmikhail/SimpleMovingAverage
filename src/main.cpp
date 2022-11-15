#include <numeric>
#include <cmath>
#include <limits>
#include <string.h>

#include "TestHelper.h"
#include "SMA.h"


int main() {

    std::cout << "Do you want to check correctness of the function? [Y/any]\n";
    char userAnswer;
    size_t k;
    std::string datatype;
    int datasize = 0;
    std::vector<double> vd;
    std::vector<float> vf;

    std::vector<double> answers;

    std::cin >> userAnswer;
    if (userAnswer == 'Y')
    {
        std::cout << "Enter window size:\n";
        std::cin >> k;

        while (datatype.compare("float") && datatype.compare("double"))
        {
            std::cout << "Enter data type (float/double):\n";
            std::cin >> datatype;
        }

        while (datasize < k)
        {
            std::cout << "Enter data size (no less than " << k << "):\n";
            std::cin >> datasize;
        }

        std::cout << "Enter data values:\n";
        if (!datatype.compare("float"))
        {
            for (int i = 0; i < datasize; ++i)
            {
                float val;
                std::cin >> val;
                vf.push_back(val);
            }
        }
        else
        {
            for (int i = 0; i < datasize; ++i)
            {
                double val;
                std::cin >> val;
                vd.push_back(val);
            }
        }

        std::cout << "Enter correct values of SMA (size - k):\n";

        for (int i = 0; i < datasize - k + 1; ++i)
        {
            double val;
            std::cin >> val;
            answers.push_back(val);
        }

        if (!datatype.compare("float"))
        {
            std::vector<float> floatAns(answers.begin(), answers.end());
            TestHelper::CompareAnswers(ComputeSMA(k, vf), floatAns);
        }
        else
        {
            TestHelper::CompareAnswers(ComputeSMA(k, vd), answers);
        }
    }

    TestHelper helper;
    helper.RunMeasurementTest();
    helper.ShowMeasurements();
    helper.ExportMeasurements();

    std::cout << "Enter any symbol to finish:";
    char a;
    std::cin >> a;
    return 0;
}
