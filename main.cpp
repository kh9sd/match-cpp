#include "match.h"
#include <iostream>
#include <vector>
#include <variant>
#include <string>

int main()
{
    std::vector<std::variant<char,
                             long,
                             float,
                             int,
                             double,
                             long long>> // (1)
        vecVariant = {5,
                      '2',
                      5.4,
                      100ll,
                      2011l,
                      3.5f,
                      2017};

    for (auto v : vecVariant)
    { // (3)
        std::cout << std::visit(
                         Overload{
                             // (2)
                             [](char)
                             { return "char"; },

                             [](int)
                             { return "int"; },

                             [](unsigned int)
                             { return "unsigned int"; },

                             [](long int)
                             { return "long int"; },

                             [](long long int)
                             { return "long long int"; },

                             [](auto)
                             { return "unknown type"; },
                         },
                         v)
                  << '\n';
    }

    std::cout << '\n';

    std::vector<std::variant<std::vector<int>,
                             double,
                             std::string>>
        vecVariant2 = {1.5,
                       std::vector<int>{1, 2, 3, 4, 5},
                       "Hello "};

    for (auto v : vecVariant2)
    {
        std::visit(
            Overload{
                [](std::vector<int> &myVec)
                {
                    for (auto v : myVec)
                        std::cout << v << " ";
                    std::cout << '\n';
                },

                [](auto &arg)
                { std::cout << arg << '\n'; },
            },
            v);
    }

    std::cout << '\n';
}
