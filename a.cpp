#include <bitsdc++.h>
using namespace std;

int n, m, sum, cur;
int arr[25], vis[25];
bool fp;
bool mycmp(int a, int b) { return a > b; }

void dfs(int s, int len, int num) {    //当前位置，目前长度，成功条数
    if (num == 4) { fp = true; return; }
    if (len == cur)dfs(1, 0, num + 1);   //如果这一轮凑够了一根木棍，那么接下来继续从第一根开始搜索
    for (int i = s; i <= n; i++) {
        if (!vis[i] && len + arr[i] <= cur) {
            vis[i] = 1;    //当前木棍选或者不选
            dfs(i + 1, len + arr[i], num);
            vis[i] = 0;
            if (fp)return;     //如果已经成功，所有搜索分支全部暂停
        }
    }
}
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        sum = 0;
        for (int i = 1; i <= n; i++) { scanf("%d", &arr[i]), sum += arr[i]; }
        sort(arr + 1, arr + 1 + n, mycmp);    //优化搜索顺序
        cur = sum / 4;
        if (sum % 4 != 0 || cur < arr[1])puts("no");
        else {
            fp = false;
            dfs(1, 0, 0);
            fp ? puts("yes") : puts("no");
        }
    }
}
