#include <iostream>
#include "binfuncs.h"

using namespace std;

int res_size = 0;

void print(vector<bool> v) {
    for(auto i : v)
        cout << i;
    cout << endl;
}

vector<bool> negative(vector<bool> num) {
    for (int i = 0; i < size; i++)
        num[i] = static_cast<bool>(1 ^ num[i]);

    num = add(num, convert_to_binary(1));

    return num;
}

vector<bool> product(vector<bool> first_num, vector<bool> second_num) {
    vector<bool> a(res_size, 0), s(res_size, 0), p(res_size, 0);
    vector<bool> neg_first_num = negative(first_num);

    for (int i = 0; i < size; i++) {
        a[i] = first_num[i];
        s[i] = neg_first_num[i];
    }

    for (int i = size, j = 0; j < size; i++, j++)
        p[i] = second_num[j];

    for (int i = 0; i < size; i++) {
        int step = (int)p[res_size - 2] * 10 + (int)p[res_size - 1];

        if (step == 1)
            p = add(p, a);
        else if(step == 10)
            p = add(p, s);

        bool sign = p.front();
        p.pop_back();
        p.insert(p.begin(), sign);

        for(auto byte : vector<bool>(p.begin(), p.end() - 2))
            cout << byte;
        cout << " " << p[res_size - 2] << p[res_size - 1] << endl;
    }
    p.pop_back();

    return p;
}

int main() {
    long long first_number_dns, second_number_dns;
    vector<bool> first_number, second_number, ans;
    bool op;

    cout << "Input the first number in decimal base." << endl;
    cin >> first_number_dns;
    first_number = convert_to_binary(first_number_dns);

    cout << "Input the second number in decimal base." << endl;
    cin >> second_number_dns;
    second_number = convert_to_binary(second_number_dns);

    res_size = size * 2 + 1;

    if(first_number_dns == - (1LL << (size - 1)))
        swap(first_number_dns, second_number_dns);

    print(first_number);
    cout << "*" << endl;
    print(second_number);

    for (int i = 0; i < size * 2 + 2; i++)
        cout << "-";
    cout << endl;

    ans = product(first_number, second_number);

    for (int i = 0; i < size * 2 + 2; i++)
        cout << "-";
    cout << endl;

    print(ans);

    cout << "\nDecimal form is:" << endl;
    cout << convert_to_decimal(ans) << endl;

    return 0;
}

