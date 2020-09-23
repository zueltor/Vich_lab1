//
// Created by Damir on 08.09.2020.
//

#include "equation.h"

void Parameters::findDerivative(Parameters &in) {
    a = 3;
    b = in.a * 2;
    c = in.b;
    delta = in.delta;
    eps = in.eps;
}

long double Parameters::calculateCubicValue(long double p) {
    return p * p * p + a * p * p + b * p + c;
}

void Parameters::setParametersByRoot(Roots &roots) {
    if (roots.count == 3) {
        a = -roots.r[0] - roots.r[1] - roots.r[2];
        b = roots.r[0] * roots.r[1] + roots.r[0] * roots.r[2] + roots.r[1] * roots.r[2];
        c = -roots.r[0] * roots.r[1] * roots.r[2];
    } else if (roots.count == 1) {
        a = 1 - roots.r[0];
        b = 1 - roots.r[0];
        c = -roots.r[0];
    }
}

Roots::Roots() {
    r[0] = UNKNOWN;
    r[1] = UNKNOWN;
    r[2] = UNKNOWN;
}

long double Roots::findDiscriminant(Parameters &quadratic) {
    return quadratic.b * quadratic.b - 4 * quadratic.a * quadratic.c;
}

void Roots::findIntervals(Parameters &cubic, Parameters &quadratic) {
    long double desc = findDiscriminant(quadratic);
    r[0] = UNKNOWN;
    r[1] = UNKNOWN;
    r[2] = UNKNOWN;
    if (desc < EPS) {
        printf("1\n");
        count = 1;
        long double val = cubic.calculateCubicValue(0);
        if (std::abs(val) < EPS) {
            printf("2\n");
            r[0] = 0;
        } else if (val < -EPS) {
            printf("3\n");
            interval[0].lb = 0;
            interval[0].ub = INF;
        } else if (val > EPS) {
            printf("4\n");
            interval[0].lb = -INF;
            interval[0].ub = 0;
        }
    } else if (desc > EPS) {
        long double eps = cubic.eps;
        desc = std::sqrt(desc);
        long double alpha = (-quadratic.b - desc) / 2.0 / quadratic.a;
        long double beta = (-quadratic.b + desc) / 2.0 / quadratic.a;
        long double val_alpha = cubic.calculateCubicValue(alpha);
        long double val_beta = cubic.calculateCubicValue(beta);
        if (val_alpha > eps && val_beta > eps) {
            printf("5\n");
            count = 1;
            interval[0].lb = -INF;
            interval[0].ub = alpha;
        } else if (val_alpha < -eps && val_beta < -eps) {
            printf("6\n");
            count = 1;
            interval[0].lb = beta;
            interval[0].ub = INF;
        } else if (val_alpha > eps && std::abs(val_beta) < eps) {
            printf("7\n");
            count = 2;
            interval[0].lb = -INF;
            interval[0].ub = alpha;
            r[1] = beta;
        } else if (std::abs(val_alpha) < eps && val_beta < -eps) {
            printf("8\n");
            count = 2;
            interval[0].lb = beta;
            interval[0].ub = INF;
            r[1] = alpha;
        } else if (val_alpha > eps && val_beta < -eps) {
            printf("9\n");
            count = 3;
            interval[0].lb = -INF;
            interval[0].ub = alpha;
            interval[1].lb = alpha;
            interval[1].ub = beta;
            interval[2].lb = beta;
            interval[2].ub = INF;
        } else if (std::abs(val_alpha) < eps && std::abs(val_beta) < eps) {
            printf("10\n");
            count = 1;
            r[0] = (alpha + beta) / 2;
        }
    }
}

void Roots::localiseRoots(Parameters &cubic) {
    for (int i = 0; i < count; i++) {
        if (r[i] != UNKNOWN) {
            continue;
        }
        long double sign;
        long double eps = cubic.eps;
        long double delta = cubic.delta;
        long double val;
        if (interval[i].lb == -INF) {
            sign = cubic.calculateCubicValue(interval[i].ub);
            if (std::abs(sign) < eps) {
                r[i] = interval[i].ub;
                continue;
            }
            long double lb = interval[i].ub;
            do {
                interval[i].ub = lb;
                lb -= delta;
                val = cubic.calculateCubicValue(lb);
                if (std::abs(val) < eps) {
                    r[i] = lb;
                    break;
                }
            } while (sign * cubic.calculateCubicValue(lb) > 0);
            interval[i].lb = lb;
        } else if (interval[i].ub == INF) {
            sign = cubic.calculateCubicValue(interval[i].lb);
            if (std::abs(sign) < eps) {
                r[i] = interval[i].lb;
                continue;
            }
            long double ub = interval[i].lb;
            do {
                interval[i].lb = ub;
                ub += delta;
                val = cubic.calculateCubicValue(ub);
                if (std::abs(val) < eps) {
                    r[i] = ub;
                    break;
                }
            } while (sign * cubic.calculateCubicValue(ub) > 0);
            interval[i].ub = ub;
        } /*else {
                val = cubic.calculateCubicValue(interval[i].lb);
                if (fabs(val) < eps) {
                    r[i] = interval[i].lb;
                    continue;
                }
                val = cubic.calculateCubicValue(interval[i].ub);
                if (fabs(val) < eps) {
                    r[i] = interval[i].ub;
                    continue;
                }
            }*/
    }
}

void Roots::findRoots(Parameters &cubic) {
    long double x, val1, val2;
    long double eps = cubic.eps;
    for (int i = 0; i < count; i++) {
        if (r[i] == UNKNOWN) {
            do {
                x = (interval[i].lb + interval[i].ub) / 2.0;
                if (x == interval[i].lb || x == interval[i].ub) {
                    std::cout << "Value of #" << i + 1 << " root might not be accurate due to lack of precision\n";
                    break;
                }
                val1 = cubic.calculateCubicValue(x);
                val2 = cubic.calculateCubicValue(interval[i].lb);
                if (val1 * val2 < 0) {
                    interval[i].ub = x;

                } else {
                    interval[i].lb = x;
                }
            } while (std::abs(val1) > eps && interval[i].ub - interval[i].lb > EPS);
            r[i] = x;
        }
    }

    if (r[0] > r[1]) {
        long double tmp = r[1];
        r[1] = r[0];
        r[0] = tmp;
    }
    if (r[1] > r[2]) {
        long double tmp = r[2];
        r[2] = r[1];
        r[1] = tmp;
    }
}

void Roots::printAnwer() {
    std::cout << count << " roots:\n";
    for (int i = 0; i < count; i++) {
        if (r[i] != UNKNOWN) {
            std::cout << r[i] << "\n";
        } else {
            std::cout << "from " << interval[i].lb << " to " << interval[i].ub << "\n";
        }
    }
}

void solve(Parameters &cubic, Roots &r) {
    Parameters quadratic{};
    quadratic.findDerivative(cubic);
    r.findIntervals(cubic, quadratic);
    r.localiseRoots(cubic);
    r.findRoots(cubic);
}
