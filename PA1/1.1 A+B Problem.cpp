#include<iostream>
#include<cmath>
using namespace std;

void reverse(string &a) {
    for (int i = 0, j = a.length() - 1; i < j; i++, j--) {
        char tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        reverse(a);
        reverse(b);
        int a_len = a.length() / 8 + (a.length() % 8 == 0 ? 0 : 1);
        int b_len = b.length() / 8 + (b.length() % 8 == 0 ? 0 : 1);
        long long *a_long = new long long[a_len]();
        long long *b_long = new long long[b_len]();
        for (int i = 0; i < a_len; i++) {
            long long res = 0;
            for (int j = 8 * i; j < a.length() && j < 8 * (i + 1); j++) {
                res += (int(a[j]) - int('0')) * (long long)(pow(10, j - 8 * i));
            }
            a_long[i] = res;
        }
        for (int i = 0; i < b_len; i++) {
            long long res = 0;
            for (int j = 8 * i; j < b.length() && j < 8 * (i + 1); j++) {
                res += (int(b[j]) - int('0')) * (long long)(pow(10, j - 8 * i));
            }
            b_long[i] = res;
        }

        long long *res = new long long[a_len + b_len]();
        for (int i = 0; i < a_len; i++) {
            for (int j = 0; j < b_len; j++) {
                long long tmp = a_long[i] * b_long[j];
                res[i + j] += tmp;
            }
        }

        for (int i = 0; i < a_len + b_len; i++) {
            res[i + 1] += res[i] / 100000000;
            res[i] %= 100000000;
        }

        bool zero = true;
        bool first = true;
        for (int i = a_len + b_len - 1; i >= 0; i--) {
            if (res[i] == 0 && zero) {
                continue;
            }
            string tmp = to_string(res[i]);
            if (first) {
                cout << tmp;
                first = false;
            }
            else {
                for (int i = 0; i < 8 - tmp.length(); i++) {
                    cout << "0";
                }
                cout << tmp;
            }
            zero = false;
        }
        if (zero) {
            cout << "0";
        }
        cout << endl;
        delete[] a_long, b_long, res;
    }
}