#include "bowling.h"

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
    for (int i = 0; i < _pairs.size(); ++i)
    {
        sum += _pairs[i].first + _pairs[i].second;
        if (i > 0)
        {
            if (_pairs[i-1].first == 10)
                sum += _pairs[i].first + _pairs[i].second;
            else if (_pairs[i-1].first + _pairs[i-1].second == 10)
                sum += _pairs[i].first;
        }
    }
    return sum;
}