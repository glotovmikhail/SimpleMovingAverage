#pragma once

#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
std::vector<T> ComputeSMA(size_t window, const std::vector<T> & data)
{
    static_assert(std::is_floating_point<T>::value);

    if (data.empty())
    {
        std::cout << "Data is empty.\n";
        return {};
    }

    if (window > data.size())
    {
        std::cout << "Data size is smaller than window.\n";
        return {};
    }

    std::vector<T> sma(data.size() - window, 0.0);

    // compute initial SMA value
    T currentSMA = 0;
    {
        T currentSum = data[0];

        for (size_t i = 1; i < window; ++i)
        {
            if (currentSum == 0 || std::isfinite(currentSum + data[i])) // check for possible overflow
            {
                currentSum += data[i];
            }
            else
            {
                currentSMA += (currentSum / window) + (data[i] / window); // compute separately if there is an overflow
                currentSum = 0;
            }
        }

        if (currentSum != 0)
        {
            currentSMA += (currentSum / window);
        }

        sma[0] = (currentSMA);
    }

    // compute other sma values
    for (size_t i = window; i < data.size(); ++i)
    {
        if (std::isfinite(data[i] - data[i - window]))
        {
            T diff = (data[i] - data[i - window]) / window;
            currentSMA += diff;
        }
        else
        {
            currentSMA += (data[i] / window) - (data[i - window] / window);
        }

        sma[i - window + 1] = currentSMA;
    }

    return sma;
}