#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        vector<int> sticks(x);
        for (int i = 0; i < x; i++)
            cin >> sticks[i];
        sort(sticks.begin(), sticks.end());
        int sum = 0;
        for (auto i = sticks.begin(); i != sticks.end(); i++)
            sum += *i;
        if (sum % 4 != 0) cout << "no" << endl;
    }
}