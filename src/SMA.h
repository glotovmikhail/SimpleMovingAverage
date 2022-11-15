#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
std::vector<T> ComputeSMA(const int & window, const std::vector<T> & data)
{
    static_assert(std::is_floating_point<T>::value);

    if (window > data.size())
    {
        std::cout << "Data size is smaller than window.\n";
        return {};
    }

    std::vector<T> sma;
    sma.reserve(data.size() - window);

    // compute initial sma
    long double currentSMA = 0;
    for (size_t i = 0; i < window; ++i)
    {
        currentSMA += static_cast<long double>(data[i]);
    }
    currentSMA /= window;
    sma.push_back(currentSMA);

    // compute other sma values
    for (size_t i = window; i < data.size(); ++i)
    {
        long double diff = (static_cast<long double>(data[i]) - static_cast<long double>(data[i - window])) / window;
        currentSMA += diff;
        sma.push_back(currentSMA);
    }

    return sma;
}