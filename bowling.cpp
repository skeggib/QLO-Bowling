#include "bowling.h"

#include <exception>
#include <algorithm>

bool is_strike(std::pair<int, int> p)
{
    return p.first == 10;
}

bool is_spare(std::pair<int, int> p)
{
    return !is_strike(p) && p.first + p.second == 10;
}

void bowling::add(std::pair<int, int> p)
{
    if (p.first < 0 || p.second < 0)
        throw std::exception();

    if (_pairs.size() < 10)
    {
        if (p.first + p.second > 10)
            throw std::exception();
    }

    if (_pairs.size() >= 10)
    {
        if (is_spare(_pairs[9]) && p.second == 0) { }
        else if (is_strike(_pairs[9])) { }
        else throw std::exception();
    }
    
    _pairs.push_back(p);
}

int bowling::score() const
{
    int sum = 0;        
    for (int i = 0; i < std::min((int)_pairs.size(), 9); ++i)
    {
        auto current = _pairs[i];
        
        if (is_spare(current))
        {
            if (_pairs.size() > i + 1)
            {
                auto next = _pairs[i+1];
                sum += current.first + current.second + next.first;
            }
        }

        else if (is_strike(current))
        {
            if (_pairs.size() > i + 1)
            {
                auto next = _pairs[i+1];
                
                if (!is_strike(next))
                {
                    sum += current.first + next.first + next.second;
                }

                else if (_pairs.size() > i + 2)
                {
                    auto next_next = _pairs[i+2];
                    sum += current.first + next.first + next_next.first;
                }
            }
        }

        else
        {
            sum += current.first + current.second;
        }
    }

    if (_pairs.size() >= 10)
    {
        auto current = _pairs[9];
        if (is_spare(current))
        {
            auto next = _pairs[10];

            if (_pairs.size() >= 11)
                sum += current.first + current.second + next.first;
        }

        else if (is_strike(current))
        {
            auto next = _pairs[10];

            if (_pairs.size() >= 11)
                sum += current.first + current.second + next.first + next.second;
        }

        else
        {
            sum += current.first + current.second;
        }
    }

    return sum;
}