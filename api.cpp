#include "api.h"

#include <exception>

void bowling::add(std::pair<int, int> p)
{
    if (p.first < 0 || p.second < 0)
        throw std::exception();
    if (p.first + p.second > 10)
        throw std::exception();
    if (_pairs.size() >= 10)
        throw std::exception();
    _pairs.push_back(p);
}

int bowling::score() const
{
    int sum = 0;
    for (auto pair:_pairs)
        sum += pair.first + pair.second;
    return sum;
}