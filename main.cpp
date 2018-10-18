#include "bowling.h"

#include <iostream>
#include <algorithm>

void display_bowling(bowling const & b);

int main()
{
    bowling b;

    std::cout << std::endl;
    std::cout << "# -------------------------------------------------- #" << std::endl;
    std::cout << "# -----                                        ----- #" << std::endl;
    std::cout << "# ---          BOWLING SCORE CALCULATOR          --- #" << std::endl;
    std::cout << "# -----                                        ----- #" << std::endl;
    std::cout << "# -------------------------------------------------- #" << std::endl;
    std::cout << std::endl;

    int v1, v2;
    for (int i = 0; i < 10; ++i)
    {
        v1 = -1;
        do
        {
            std::cout << "Tour n. " << (i+1) << ",  premier lancer : ";
            std::cin >> v1;
            if (v1 < 0 || v1 > 10)
                std::cout << "Il doit y avoir une erreur..." << std::endl;
        } while (!(v1 >= 0 && v1 <= 10));

        v2 = -1;
        if (v1 < 10)
        {
            std::cout << "Il reste " << (10-v1) << " quilles." << std::endl;
            do
            {
                std::cout << "Tour n. " << (i+1) << ", deuxieme lancer : ";
                std::cin >> v2;
            if (v2 < 0 || v2 > 10 - v1)
                std::cout << "Il doit y avoir une erreur..." << std::endl;
            } while (!(v2 >= 0 && v2 <= 10 - v1));
        }

        if (v2 == -1)
            v2 = 0;

        b.add({v1, v2});

        std::cout << std::endl;
        display_bowling(b);
        std::cout << std::endl;
    }

    if (is_spare(b[9]))
    {
        v1 = -1;
        do
        {
            std::cout << "Lancer bonus : ";
            std::cin >> v1;
            if (v1 < 0 || v1 > 10)
                std::cout << "Il doit y avoir une erreur..." << std::endl;
        } while (!(v1 >= 0 && v1 <= 10));

        b.add({v1, 0});

        std::cout << std::endl;
        display_bowling(b);
        std::cout << std::endl;
    }

    if (is_strike(b[9]))
    {
        v1 = -1;
        do
        {
            std::cout << "Premier lancer bonus   : ";
            std::cin >> v1;
            if (v1 < 0 || v1 > 10)
                std::cout << "Il doit y avoir une erreur..." << std::endl;
        } while (!(v1 >= 0 && v1 <= 10));

        v2 = -1;
        do
        {
            std::cout << "Deuxieme lancer bonus : ";
            std::cin >> v2;
            if (v1 < 0 || v1 > 10)
                std::cout << "Il doit y avoir une erreur..." << std::endl;
        } while (!(v1 >= 0 && v1 <= 10));

        b.add({v1, v2});

        std::cout << std::endl;
        display_bowling(b);
        std::cout << std::endl;
    }

    return 0;
}

void display_bowling(bowling const & b)
{
    int n = 75;
    std::cout << "|" << std::string(n - 2, '-') << "|" << std::endl;

    std::cout << "|";
    for (int i = 0; i < 9; ++i)
        std::cout << "   " << (i+1) << "  |";
    std::cout << "    10    |" << std::endl;

    std::cout << "|";
    for (int i = 0; i < 9; ++i)
        std::cout << "------" << "|";
    std::cout << "----------|" << std::endl;

    std::cout << "| ";
    for (int i = 0; i < std::min((int)b.size(), 9); ++i)
    {
        std::cout << b[i].first << " ";
        if (is_strike(b[i]))
            std::cout << "-";
        else if (is_spare(b[i]))
            std::cout << " /";
        else
            std::cout << " " << b[i].second;
        std::cout << " | ";
    }
    if (b.size() >= 10)
    {
        if (is_strike(b[9]))
        {
            std::cout << "10 ";
            if (b.size() >= 11)
            {
                if (b[10].first > 9)
                    std::cout << b[10].first;
                else
                    std::cout << " " << b[10].first;
                std::cout << " ";
                if (b[10].second > 9)
                    std::cout << b[10].second;
                else
                    std::cout << " " << b[10].second;
            }
            else
                std::cout << "     ";
        }

        else if (is_spare(b[9]))
        {
            std::cout << b[9].first << "  /  ";
            if (b.size() >= 11)
            {
                if (b[10].first > 9)
                    std::cout << b[10].first;
                else
                    std::cout << " " << b[10].first;
            }
            else
                std::cout << "  ";
        }

        else
        {
            std::cout << b[9].first << "  " << b[9].second << "    ";
        }

        std::cout << " |";
    }
    if (b.size() <= 9)
        for (int i = 0; i < 9 - b.size(); ++i)
            std::cout << "     | ";
    if (b.size() < 10)
        std::cout << "         |";
    std::cout << " -> Score = " << b.score();
    std::cout << std::endl;

    std::cout << "|" << std::string(n - 2, '-') << "|" << std::endl;
}