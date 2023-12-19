//
// Created by kevin on 10/24/2022.
//
#include "../catch.hpp"
#include "../../match.h"

#include <concepts>

#include <variant>
#include <vector>

TEST_CASE("ValveRedline test condition", "[unit]")
{
    enum class dogshit
    {
        CHAR,
        LONG,
        FLOAT,
        INT,
        DOUBLE,
        LONG_LONG
    };

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

    auto bullshit = Overload{
        // (2)
        [](STRICT(char, ))
        { return dogshit::CHAR; },

        [](STRICT(long int, ))
        { return dogshit::LONG; },

        [](STRICT(float, ))
        { return dogshit::FLOAT; },

        [](STRICT(int, ))
        { return dogshit::INT; },

        [](STRICT(double, ))
        { return dogshit::DOUBLE; },

        [](STRICT(long long int, ))
        { return dogshit::LONG_LONG; }

    };

    REQUIRE(std::visit(
                bullshit,
                vecVariant[0]) == dogshit::INT);

    REQUIRE(std::visit(
                bullshit,
                vecVariant[1]) == dogshit::CHAR);

    REQUIRE(std::visit(
                bullshit,
                vecVariant[2]) == dogshit::DOUBLE);

    REQUIRE(std::visit(
                bullshit,
                vecVariant[3]) == dogshit::LONG_LONG);
    REQUIRE(std::visit(
                bullshit,
                vecVariant[4]) == dogshit::LONG);
    REQUIRE(std::visit(
                bullshit,
                vecVariant[5]) == dogshit::FLOAT);
    REQUIRE(std::visit(
                bullshit,
                vecVariant[6]) == dogshit::INT);
}
