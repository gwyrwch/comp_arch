#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int convert_double_to_binary(int integer, int real, int tenpow) {
    if (integer == 0) {
        if (real == 0) {
            return -127;
        }
        int e = 0;
        while (real < tenpow) {
            real *= 2;
            e--;
        }
        return e;
    } else {
        int e = 0;
        while ((1 << e) <= integer) {
            e++;
        }
        return e - 1;
    }
}

int getM(int integer, int real, int tenpow) {
    int e = convert_double_to_binary(integer, real, tenpow);
    if (e >= 0) {
        integer -= 1 << e;

        long long p = integer * tenpow + real;
        long long q = tenpow * (1 << e);

        return int((p * (1 << 23) + q - 1) / q);
    } else {
        long long p = real * (1LL << -e) - tenpow;
        long long q = tenpow;

        return int((p * (1 << 23) + q - 1) / q);
    }
}


vector<bool> fullconvert(string number, int& sign, int &e, int &mantis) {
    sign = 0;
    if (number[0] == '-') {
        sign = 1;
        number.erase(number.begin());
    }

    size_t dotpos = number.find('.');

    if (dotpos == string::npos) {
        dotpos = number.size();
    }

    int integer = 0;
    for (size_t i = 0; i < dotpos; i++) {
        integer = integer * 10 + (number[i] - '0');
    }

    int real = 0, tenpow = 1;
    for (size_t i = dotpos + 1; i < number.size(); i++) {
        real = real * 10 + (number[i] - '0');
        tenpow *= 10;
    }

    e = convert_double_to_binary(integer, real, tenpow);
    mantis = getM(integer, real, tenpow);

    vector<bool> ans;
    ans.push_back(sign);

    for (int i = 7; i >= 0; i--) {
        if (e & (1 << i))
            ans.push_back(1);
        else
            ans.push_back(0);
    }

    // 10101010
    // 10000000
    // ->
    // 00000000
    // 10000000
    // 7

    for (int i = 22; i >= 0; i--) {
        if (mantis & (1 << i))
            ans.push_back(1);
        else
            ans.push_back(0);
    }

    assert(ans.size() == 32);
    return ans;
}


void print(vector<bool> v) {
    for(auto i : v)
        cout << i;
    cout << endl;
}

string to_string(__int128 kek, string s = "") {
    if (!kek)
        return "0";
    while (kek) {
        s += char(kek % 10 + '0');
        kek /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

string convert_to_float(int sign, int exp, int mantis) {
    int minpow = 0;
    __int128 ans = 0;

    for (int i = 0; i <= 23; i++) {
        if ((mantis & (1 << i)) || i == 23) {
            if (exp + i - 23 >= 0) {

            } else {
                if (minpow == 0)
                    minpow = -(i + exp - 23);
            }
            ans += 1LL << (exp + i + minpow - 23);
        }
    }

    for (int i = 0; i < minpow; i++)
        ans *= 5;

    string s_ans = to_string(ans);

    while (s_ans.size() < minpow)
        s_ans = '0' + s_ans;

    s_ans.insert(s_ans.size() - minpow, ".");

    if (s_ans[0] == '.')
        s_ans = '0' + s_ans;

    return s_ans;

}

int compare(__int128 mantis_a, int exp_a, __int128 mantis_b, int exp_b) {
    if (exp_a == exp_b) {
        if ( mantis_a < mantis_b)
            return -1;
        else if (mantis_a > mantis_b)
            return 1;
        else return 0;
    } else if (exp_a > exp_b)
        return 1;
    else return -1;
}
