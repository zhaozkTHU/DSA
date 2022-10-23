#include <iostream>
#define int long long
using namespace std;

int matrix[100][100];

int MaxSub(int A[], int n) {
    int tmpsum = A[0];
    int maxsum = A[0];
    for (int j = 1; j < n; j++) {
        tmpsum = (tmpsum + A[j]) > A[j] ? (tmpsum + A[j]) : A[j];
        if (tmpsum > maxsum) maxsum = tmpsum;
    }
    return maxsum;
}

signed main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }
    int result = matrix[0][0];
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int *arr = new int[100]();
            for (int k = 0; k < M; k++) {
                for (int l = i; l <= j; l++) {
                    arr[k] += matrix[l][k];
                }
            }
            result = max(result, MaxSub(arr, M));
            delete[] arr;
        }
    }
    cout << result << endl;
}