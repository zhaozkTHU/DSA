#include <iostream>
#define print_error() printf("Error in line %d\n", __LINE__); exit(1);
using namespace std;

struct TreeNode;

struct ChildListNode {
    TreeNode *value;
    ChildListNode *pred, *succ;
    ChildListNode() : value(nullptr), pred(nullptr), succ(nullptr) {}
};

struct TreeNode {
    int value;
    TreeNode *parent;
    ChildListNode *header, *trailer;
    TreeNode() : value(), parent(nullptr), header(new ChildListNode), trailer(new ChildListNode) {}
};

int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    TreeNode *tree = new TreeNode[N]();
    for (int i = 0; i < N; i++) {
        TreeNode &parent = tree[i];
        parent.value = i + 1;
        parent.header->succ = parent.trailer;
        parent.trailer->pred = parent.header;
        int childnum;
        scanf("%d", &childnum);
        while (childnum--) {
            int child;
            scanf("%d", &child);
            tree[child - 1].parent = &parent;
            ChildListNode *tmp = new ChildListNode;
            tmp->value = &tree[child - 1]; tmp->pred = parent.trailer->pred; tmp->succ = parent.trailer;
            parent.trailer->pred->succ = tmp; parent.trailer->pred = tmp;
        }
    }
    while (M--) {
        int flag;
        scanf("%d", &flag);
        if (flag == 0) {

        }
        else if (flag == 1) {

        }
        else print_error();
    }
}