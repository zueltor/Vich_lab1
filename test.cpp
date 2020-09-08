#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <sstream>
#include <utility>
#include "equation.h"


bool answerEquals(Roots &r1, Roots &r2) {
    if (r1.count != r2.count) {
        return false;
    }
    for (int i = 0; i < r1.count; i++) {
        if (std::abs(r1.r[i] - r2.r[i]) > EPS) {
            return false;
        }
    }
    return true;
}

TEST_CASE("Answer test") {
    Parameters cubic{};
    Roots r, test_r;
    cubic.eps = 1e-20;
    cubic.delta = 1;
    test_r.count = 3;

    test_r.r[0] = 1;
    test_r.r[1] = 2;
    test_r.r[2] = 3;
    cubic.setParametersByRoot(test_r);
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.r[0] = -109990;
    test_r.r[1] = -23212;
    test_r.r[2] = 313123;
    cubic.setParametersByRoot(test_r);
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.count = 1;
    test_r.r[0] = 1;
    cubic.setParametersByRoot(test_r);
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.r[0] = -99999;
    cubic.setParametersByRoot(test_r);
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.r[0] = 99999;
    cubic.setParametersByRoot(test_r);
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.count = 3;
    test_r.r[0] = 1;
    test_r.r[1] = 2;
    test_r.r[2] = 1;
    cubic.setParametersByRoot(test_r);
    test_r.count = 2;
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.count = 3;
    test_r.r[0] = -9999;
    test_r.r[1] = 12345;
    test_r.r[2] = 12345;
    cubic.setParametersByRoot(test_r);
    test_r.count = 2;
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.count = 3;
    test_r.r[0] = 100;
    test_r.r[1] = 100;
    test_r.r[2] = 100;
    cubic.setParametersByRoot(test_r);
    test_r.count = 1;
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    cubic.a = 0;
    cubic.b = 0;
    cubic.c = 0;
    test_r.count = 1;
    test_r.r[0] = 0;
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    cubic.a = 30;
    cubic.b = 300;
    cubic.c = 1000;
    test_r.count = 1;
    test_r.r[0] = -10;
    solve(cubic, r);
    REQUIRE(answerEquals(r, test_r));

    test_r.count = 3;
    cubic.eps = 1e-10;
    test_r.r[0] = 1;
    test_r.r[1] = 1 + 1e-5;
    test_r.r[2] = 1 + 1e-5;
    cubic.setParametersByRoot(test_r);
    test_r.count = 1;
    test_r.r[0] = (test_r.r[0] + 3 * test_r.r[1]) / 4;
    solve(cubic, r);
    REQUIRE((r.count == test_r.count && r.r[0] > 1 && r.r[0] < 1 + 1e-5));
}
