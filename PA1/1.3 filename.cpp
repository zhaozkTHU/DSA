#include <iostream>
#include <string>
using namespace std;

int lcs(const string &a, const string &b, int a_len, int b_len, int k) {
    int *p = new int[b_len + 1]();
    int *q = new int[b_len + 1]();
    int *current = p, *former = q;
    for (int i = 0; i <= a_len; i++) {
        for (int j = i - k; j <= i + k; j++) {
            if (j < 0 || j > b_len) {
                continue;
            }
            if (i == 0 || j == 0) {
                current[j] = 0;
            }
            else if (a[i - 1] == b[j - 1]) {
                current[j] = former[j - 1] + 1;
            }
            else {
                current[j] = former[j] < current[j - 1] ? current[j - 1] : former[j];
            }
        }
        int *tmp = former;
        former = current;
        current = tmp;
    }
    int res = former[b_len];
    delete[] p;
    delete[] q;
    return res;
}

int main() {
    int a_len, b_len, k;
    cin >> a_len >> b_len >> k;
    string a, b;
    cin >> a >> b;
    if (abs(a_len - b_len) > k) {
        cout << -1 << endl;
        return 0;
    }
    int l = lcs(a, b, a_len, b_len, k);
    int res = a_len + b_len - 2 * l;
    if (res > k) {
        cout << -1 << endl;
    }
    else {
        printf("%d\n", res);
    }
    return 0;
}