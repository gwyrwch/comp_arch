#include "float_funcs.h"

// 101011,10101001
// E = 5
// 0,10101001
// E = -1
// 0,00001
// E = -5

using namespace std;

string sub(__int128 mantis_a, __int128 exp_a, __int128 mantis_b, __int128 exp_b) {
    __int128 mantis_res = 0;
    __int128 exp_res = 0;

    exp_res = exp_a;
    mantis_res = mantis_a - ((1 << 23) + mantis_b) / (1LL << (exp_a - exp_b));

    while (mantis_res < 0) {
        exp_res--;
        mantis_res = (mantis_res * 2 + (1 << 23));
    }

    return convert_to_float(0, exp_res, mantis_res);
}

string add(__int128 mantis_a, __int128 exp_a, int sign_a, __int128 mantis_b, __int128 exp_b, int sign_b) {
    __int128 mantis_res = 0;
    __int128 exp_res = 0;

    if (sign_a == sign_b) {
        if (exp_a >= exp_b){
            exp_res = exp_a;
            mantis_res = mantis_a + ((1 << 23) + mantis_b) / (1LL << (exp_a - exp_b));
        } else if (exp_b > exp_a) {
            exp_res = exp_b;
            mantis_res = mantis_b + ((1 << 23) + mantis_a) / (1LL << (exp_b - exp_a));
        }

        while (mantis_res >= (1LL << 23)) {
            exp_res++;
            mantis_res = (mantis_res + (1LL << 23) - (1LL << 24)) / 2;
        }
    } else {
        int c = compare(mantis_a, exp_a, mantis_b, exp_b);
        if (c == -1) {
            swap(mantis_a, mantis_b);
            swap(exp_a, exp_b);
            swap(sign_a, sign_b);
        }
        string result = sub(mantis_a, exp_a, mantis_b, exp_b);
        if (sign_a == 1)
            result = '-' + result;
        return result;
    }

    return convert_to_float(0, exp_res, mantis_res);

}

string sum(string a, string b) {
    int mantis_a, mantis_b, exp_a, exp_b, sign_a, sign_b;
    fullconvert(a, sign_a, exp_a, mantis_a);
    fullconvert(b, sign_b, exp_b, mantis_b);
    return add(mantis_a, exp_a, sign_a, mantis_b, exp_b, sign_b);
}

string dif(string a, string b) {
    int mantis_a, mantis_b, exp_a, exp_b, sign_a, sign_b;
    fullconvert(a, sign_a, exp_a, mantis_a);
    fullconvert(b, sign_b, exp_b, mantis_b);
    sign_b ^= 1;
    return add(mantis_a, exp_a, sign_a, mantis_b, exp_b, sign_b);
}


const double eps = 1e-5;
bool eqf(double a, double b) {
    return fabs(a - b) < eps;
}

void test_sum() {
    for (int iter = 0; iter < 500; iter++) {
        double a = double(rand() % 100 + 1) / 100;
        double b = double(rand() % 100 + 1) / 100;

        cout << a << '+' << b << endl;

        assert(eqf(atof(sum(to_string(a), to_string(b)).c_str()), a + b));
    }
}

void test_dif() {
    for (int iter = 0; iter < 500; iter++) {
        double a = double(rand() % 100 + 1) / 100;
        double b = double(rand() % 100 + 1) / 100;

        if (fabs(a - b) < eps)
            continue;

        cout << a << '-' << b << endl;

        assert(eqf(atof(dif(to_string(a), to_string(b)).c_str()), a - b));
    }
}


int main() {
    test_sum();
    test_dif();
//    print(fullconvert("0.666", exp_a, mantis_a));
//    fullconvert("4.333", exp_b, mantis_b);
//    cout << exp_a << " " << exp_b << endl;
//    cout << add(mantis_a, exp_a, 1, mantis_b, exp_b, 1);


    return 0;
}
