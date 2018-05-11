#ifndef BOWLING_H
#define BOWLING_H

#include <vector>
#include <cstddef>

class bowling
{
private:

    std::vector<std::pair<int, int> > _pairs;

public:
    
    void add(std::pair<int, int> p);
    std::pair<int, int> const & operator[](size_t index) const;
    size_t size() const;
    int score() const;
};

bool is_strike(std::pair<int, int> p);
bool is_spare(std::pair<int, int> p);

#endif