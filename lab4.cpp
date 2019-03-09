#include <iostream>
#include "float_funcs.h"

#define mul asfafjafs

string mul(__int128 mantis_a, __int128 exp_a, int sign_a, __int128 mantis_b, __int128 exp_b, int sign_b) {
    __int128 mantis_res = 0;
    __int128 exp_res = 0;

    exp_res = exp_a + exp_b;
    mantis_res = mantis_a + mantis_b + (mantis_a * mantis_b  >> 23);

    while (mantis_res >= (1LL << 23)) {
        exp_res++;
        mantis_res = (mantis_res + (1LL << 23) - (1LL << 24)) / 2;
    }

    return convert_to_float(sign_a ^ sign_b, exp_res, mantis_res);
}

string product(string a, string b) {
    int mantis_a, mantis_b, exp_a, exp_b, sign_a, sign_b;
    fullconvert(a, sign_a, exp_a, mantis_a);
    fullconvert(b, sign_b, exp_b, mantis_b);
    return mul(mantis_a, exp_a, sign_a, mantis_b, exp_b, sign_b);
}


string div(__int128 mantis_a, __int128 exp_a, int sign_a, __int128 mantis_b, __int128 exp_b, int sign_b) {
    __int128 mantis_res = 0;
    __int128 exp_res = 0;

    exp_res = exp_a - exp_b;
    mantis_res = ((mantis_a - mantis_b) << 23) / ((1 << 23) + mantis_b);

    while (mantis_res >= (1LL << 23)) {
        exp_res++;
        mantis_res = (mantis_res + (1LL << 23) - (1LL << 24)) / 2;
    }

    while (mantis_res < 0) {
        exp_res--;
        mantis_res = (mantis_res * 2 + (1 << 23));
    }

    return convert_to_float(sign_a ^ sign_b, exp_res, mantis_res);
}

string division(string a, string b) {
    int mantis_a, mantis_b, exp_a, exp_b, sign_a, sign_b;
    fullconvert(a, sign_a, exp_a, mantis_a);
    fullconvert(b, sign_b, exp_b, mantis_b);
    return div(mantis_a, exp_a, sign_a, mantis_b, exp_b, sign_b);
}


const double eps = 1e-5;

bool eqf(double a, double b) {
    return fabs(a - b) < eps;
}

void test_product() {
    for (int iter = 0; iter < 500; iter++) {
        double a = double(rand() % 100 + 1) / 100;
        double b = double(rand() % 100 + 1) / 100;

        cout << a << '*' << b << endl;

        assert(eqf(atof(product(to_string(a), to_string(b)).c_str()), a * b));
    }
}


void test_division() {
    for (int iter = 0; iter < 500; iter++) {
        double a = double(rand() % 100 + 1) / 100;
        double b = double(rand() % 100 + 1) / 100;

        cout << a << '/' << b << endl;

        assert(eqf(atof(division(to_string(a), to_string(b)).c_str()), a / b));
    }
}


int main() {
    test_division();
}

