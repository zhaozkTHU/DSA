#include <iostream>
using namespace std;

struct HuffChar {
    char ch; int weight;
    HuffChar *lc, *rc;
    HuffChar() : ch('\0'), weight(0), lc(nullptr), rc(nullptr) {}
};

struct ListNode {
    HuffChar *value;
    ListNode *pred, *succ;
    ListNode() : value(nullptr), pred(nullptr), succ(nullptr) {}
};

int cmpfunc(const void *a, const void *b) {
    HuffChar *HuffA = (HuffChar *)a;
    HuffChar *HuffB = (HuffChar *)b;
    return HuffA->weight - HuffB->weight;
}

void get_result(HuffChar *root, string &path, string &result, int &cost) {
    // 到达Huffman树结尾
    if (root->ch != '\0') {
        // 对全文只有一个字母进行特判
        if (path.empty()) {
            cost += root->weight;
            result.push_back(root->ch);
            result.push_back(' ');
            result.push_back('0');
            result.push_back('\n');
            return;
        }
        cost += root->weight * path.length();
        result.push_back(root->ch);
        result.push_back(' ');
        result.append(path);
        result.push_back('\n');
        return;
    }
    // 向左遍历
    path.push_back('0');
    get_result(root->lc, path, result, cost);
    path.pop_back();
    //向右遍历
    path.push_back('1');
    get_result(root->rc, path, result, cost);
    path.pop_back();
}

int main() {
    string sentence;
    cin >> sentence;
    HuffChar *a = new HuffChar[26];
    for (int i = 0; i < 26; i++) {
        a[i].ch = 'a' + i;
    }
    for (auto i : sentence) a[i - 'a'].weight++;
    qsort(a, 26, sizeof(HuffChar), cmpfunc);

    ListNode *header(new ListNode), *trailer(new ListNode);
    header->succ = trailer; trailer->pred = header;

    for (int i = 0; i < 26; i++) {
        if (a[i].weight == 0) continue;
        ListNode *tmp = new ListNode;
        tmp->value = &a[i]; tmp->pred = trailer->pred; tmp->succ = trailer;
        trailer->pred->succ = tmp; trailer->pred = tmp;
    }
    while (header->succ->succ != trailer) {
        // 去掉Huffman树前两个节点并合为一个节点
        HuffChar *tmp = new HuffChar;
        tmp->lc = header->succ->value;
        tmp->rc = header->succ->succ->value;
        tmp->weight = header->succ->value->weight + header->succ->succ->value->weight;
        header->succ->succ->succ->pred = header; header->succ = header->succ->succ->succ;

        // 将新节点按顺序插入
        ListNode *new_node = new ListNode;
        new_node->value = tmp;
        if (header->succ == trailer) {
            new_node->succ = trailer; new_node->pred = header;
            header->succ = new_node; trailer->pred = new_node;
        }
        else {
            for (auto p = header->succ; p != trailer; p = p->succ) {
                if (p->value->weight >= new_node->value->weight) {
                    new_node->succ = p; new_node->pred = p->pred;
                    p->pred->succ = new_node; p->pred = new_node;
                    break;
                }
                if (p->succ == trailer) {
                    new_node->pred = p; new_node->succ = trailer;
                    p->succ = new_node; trailer->pred = new_node;
                    break;
                }
            }
        }
    }

    auto root = header->succ->value;
    string path;
    string result;
    int cost = 0;;
    get_result(root, path, result, cost);
    cout << cost << endl << result;

    return 0;
}