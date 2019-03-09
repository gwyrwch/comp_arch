#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>
#include "binfuncs.h"

using namespace std;

void print(vector<bool> v) {
    for (auto i : v)
        cout << i;
    cout << endl;
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

    string operation;

    while (true) {
        cout << "What would you like to do?" << endl;
        cout << "1. Addition of numbers. (type 1 or +)" << endl;
        cout << "2. Subtraction of numbers. (type 2 or -)" << endl;

        string choice;
        cin >> choice;

        if (choice == "+" || choice == "1") {
            operation = "+";
            ans = add(first_number, second_number);
            break;
        } else if (choice == "-" || choice == "2") {
            operation = "-";
            ans = sub(first_number, second_number);
            break;
        }
        else cout << "Invalid input, try again.";
    }

    print(first_number);
    cout << operation << endl;
    print(second_number);

    for (int i = 0; i < size; i++)
        cout << "-";
    cout << endl;

    print(ans);

    cout << "\nDecimal form is:" << endl;
    cout << convert_to_decimal(ans) << endl;
    return 0;
}