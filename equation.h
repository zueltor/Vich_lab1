//
// Created by Damir on 08.09.2020.
//

#ifndef LAB1CPP_EQUATION_H
#define LAB1CPP_EQUATION_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cfloat>
#include <algorithm>
#include "equation.h"

#define EPS (1e-10)
#define UNKNOWN DBL_MAX
#define INF DBL_MAX

class Roots;

class Parameters {
public:
    void findDerivative(Parameters &in);

    long double calculateCubicValue(long double p);

    void setParametersByRoot(Roots &roots);

public:
    long double a;
    long double b;
    long double c;
    long double eps;
    long double delta;
};

class Interval {
public:
    long double lb;
    long double ub;
};

class Roots {
public:
    Roots();

    static long double findDiscriminant(Parameters &quadratic);

    void findIntervals(Parameters &cubic, Parameters &quadratic);

    void localiseRoots(Parameters &cubic);

    void findRoots(Parameters &cubic);

    void printAnwer();

public:
    long double r[3]{};
    Interval interval[3]{};
    int count{};
};

void solve(Parameters &cubic, Roots &r);

#endif //LAB1CPP_EQUATION_H
