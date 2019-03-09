#include <assert.h>
#include <vector>
#include <iostream>

using namespace std;

const int n = 5;
const int size = 1 << n;

vector<bool> convert_to_binary(long long num) {
    vector<bool> ans(size, 0);

    if (num < 0) {
        ans[size - 1] = 1;
        num += 1LL << (size - 1);
        assert(num >= 0);
    }

    for (int i = 0; i < size - 1; i++) {
        if(num % 2 == 1)
            ans[i] = 1;
        num /= 2;

    }

    if (num != 0) {
        cout << "The number is too big. Change the size and restart the program." << endl;
        exit(0);
    }

    reverse(ans.begin(), ans.end());

    for(auto i : ans)
        cout << i;
    cout << endl;

    return ans;
}

long long convert_to_decimal(vector<bool> bin_num) {
    long long ans = 0;

    for (int i = 1; i < bin_num.size(); i++) {
        ans = ans * 2;
        ans += bin_num[i];
    }

    if (bin_num[0]) {
        ans -= 1LL << (bin_num.size() - 1);
    }

    return ans;
}

vector<bool> add(vector<bool> first_num, vector<bool> second_num) {
    vector<bool> res(first_num.size(), 0);
    bool carry = 0;

    for (int i = (int)first_num.size() - 1; i >= 0; i--) {
        int cur = (int)first_num[i] + (int)second_num[i] + (int)carry;
        res[i] = (bool)(cur % 2);
        carry = (bool)(cur / 2);
    }

    if (first_num[0] == second_num[0] && res[0] != first_num[0]) {
        cout << "Overflow happened" << endl;
        exit(0);
    }

    return res;
}

vector<bool> smallest_number() {
    vector<bool> res(size, 0);
    res[0] = 1;

    return res;
}

vector<bool> sub(vector<bool> first_num, vector<bool> second_num) {
    if (second_num == smallest_number()) {
        cout << "Impossible operation" << endl;
        exit(0);
    }

    for (int i = 0; i < first_num.size(); i++) {
        second_num[i] = static_cast<bool>(1 ^ second_num[i]);
    }

    second_num = add(second_num, convert_to_binary(1));

    return add(first_num, second_num);
}

