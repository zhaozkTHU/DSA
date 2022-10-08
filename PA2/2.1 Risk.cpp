#include<iostream>
using namespace std;

struct Node {
    long long value;
    Node *next, *last;
};

int main() {
    long long n;
    cin >> n;
    long long *people_nums = new long long[n];
    long long *days = new long long[n];
    for (int i = 0; i < n; i++) {
        cin >> people_nums[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> days[i];
    }

    long long T;
    cin >> T;
    long long *p = new long long[T];
    long long *q = new long long[T];
    long long *low_risk_res = new long long[T]();
    long long *mid_risk_res = new long long[T]();
    for (long long i = 0; i < T; i++) {
        cin >> p[i] >> q[i];
    }

    Node *header, *trailer;
    header->next = trailer;
    header->last = nullptr;
    trailer->last = header;
    trailer->next = nullptr;

    long long *low_risk_days = new long long[T]((long long)(1));
    long long *mid_risk_days = new long long[T]();
    for (long long i = 1; i < n; i++) {
        long long start = 0;
        long long size = 0;

        Node *tmp = new Node();
        tmp->next = trailer;
        tmp->last = trailer->last;
        tmp->value = people_nums[i - 1];

        tmp->last = trailer->last;
        trailer->last->next = tmp;
        tmp->next = trailer;
        trailer->last = tmp;
    }

    delete[] people_nums;
    delete[] days;
    delete[] p;
    delete[] q;
    delete[] low_risk_res;
    delete[] mid_risk_res;
    delete[] low_risk_days;
    delete[] mid_risk_days;
}