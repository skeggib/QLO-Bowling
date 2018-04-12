#ifndef BOWLING_H
#define BOWLING_H

#include <vector>

class bowling
{
private:

    std::vector<std::pair<int, int> > _pairs;

public:
    
    void add(std::pair<int, int> p);
    int score() const;
};

#endif