#include <iostream>
using namespace std;

struct Trie;

Trie *root;

struct Trie {
    Trie *left, *right;
    int num, index;
    Trie(): left(nullptr), right(nullptr), num(0), index(0) {}
    ~Trie() {
        if (left) delete left;
        if (right) delete right;
    }
    void insert(const string &a, const int &index) {
        auto current = root;
        root->num += 1;
        for (int i = 0; i < 64; i++) {
            if (a[i] == '0') {
                if (current->left == nullptr)
                    current->left = new Trie();
                current = current->left;
            }
            else {
                if (current->right == nullptr) 
                    current->right = new Trie();
                current = current->right;
            }
            current->num += 1;
        }
        current->index = index;
    }
    void remove(const string &a) {
        auto current = root;
        root->num -= 1;
        for (int i = 0; i < 64; i++) {
            if (a[i] == '0') {
                current->left->num -= 1;
                if (current->left->num == 0) {
                    delete current->left;
                    current->left = nullptr;
                    break;
                }
                current = current->left;
            }
            else {
                current->right->num -= 1;
                if (current->right->num == 0) {
                    delete current->right;
                    current->right = nullptr;
                    break;
                }
                current = current->right;
            }
        }
    }
    int query(const string &a) {
        auto current = root;
        for (int i = 0; i < 64; i++) {
            if (a[i] == '0') {
                if (current->right) current = current->right;
                else current = current->left;
            }
            if (a[i] == '1') {
                if (current->left) current = current->left;
                else current = current->right;
            }
        }
        return current->index;
    }
};

int n, k;
int main() {
    root = new Trie;
    scanf("%d%d", &n, &k);
    string *str = new string[n];
    for (int i = 0; i < n; i++)
        cin >> str[i];
    int left(n), right(n - 1);
    int *res = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        int new_left = i - k - 1 < 0 ? 0 : i - k - 1;
        int new_right = i + k + 1 > n - 1 ? n - 1 : i + k + 1;
        for (int j = left - 1; j >= new_left; j--)
            root->insert(str[j], j);
        left = new_left;
        for (int j = right; j > new_right; j--)
            root->remove(str[j]);
        right = new_right;
        res[i] = root->query(str[i]);
    }
    for (int i = 0; i < n; i++)
        printf("%d\n", res[i]);
}