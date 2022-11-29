#include <iostream>
#include <sstream>
#include <stdexcept>
#define DEFAULT_CAPACITY 3
using namespace std;

struct Node;

struct NodeList {
    Node *child, *parent;
    NodeList *succ, *pred;
    NodeList() : child(nullptr), parent(nullptr), succ(nullptr), pred(nullptr) {}
    NodeList(Node *child, Node *parent, NodeList *succ, NodeList *pred) :
        child(child), parent(parent), succ(succ), pred(pred) {}
};

struct Node {
    int value, size, height;
    NodeList *header, *trailer, *parent;
    Node() : value(0), size(0), height(0),
        header(new NodeList), trailer(new NodeList), parent(nullptr) {
        header->succ = trailer;
        trailer->pred = header;
    }
    int calculate_size() {
        if (size != 0) return size;
        size = 1;
        for (auto i = header->succ; i != trailer; i = i->succ)
            size += i->child->calculate_size();
        return size;
    }
    int calcu_height() {
        // if (height != 0) return size;
        height = 1;
        int max_height = 0;
        for (auto i = header->succ; i != trailer; i = i->succ)
            max_height = max(max_height, i->child->calcu_height());
        height += max_height;
        return height;
    }
    void update_height(int old_height, int new_height) {
        if (new_height > height - 1) {
            int old = height;
            height = new_height + 1;
            if (parent != nullptr)
                parent->parent->update_height(old, height);
            return;
        }
        if (old_height == height - 1) {
            int max_height = 0;
            for (auto i = header->succ; i != trailer; i = i->succ)
                max_height = max(max_height, i->child->height);
            if (max_height < height - 1) {
                int old = height;
                height = max_height + 1;
                if (parent != nullptr)
                    parent->parent->update_height(old, height);
            }
        }
    }
};

int N, M;
Node *tree;

auto get_node() {
    int path_size; scanf("%d", &path_size);
    int *path = new int[path_size];
    for (int i = 0; i < path_size; i++)
        scanf("%d", &path[i]);
    auto node = &tree[1];
    for (int i = 0; i < path_size; i++) {
        bool valid = true;
        auto tmp = node->header;
        for (int j = 0; j < path[i] + 1; j++) {
            tmp = tmp->succ;
            if (tmp == node->trailer) {
                valid = false;
                break;
            }
        }
        if (valid) node = tmp->child;
        else break;
    }
    delete[] path;
    if (node == nullptr) exit(EXIT_FAILURE);
    return node;
}

int main() {
    scanf("%d%d", &N, &M);
    tree = new Node[N + 1];
    for (int i = 1; i <= N; i++) {
        tree[i].value = i;
    }
    // 构造
    for (int i = 1; i <= N; i++) {
        int n;
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            int k; scanf("%d", &k);
            NodeList *tmp = new NodeList;
            tmp->child = &tree[k];
            tmp->parent = &tree[i];
            tmp->succ = tree[i].trailer;
            tmp->pred = tree[i].trailer->pred;
            tree[i].trailer->pred->succ = tmp;
            tree[i].trailer->pred = tmp;
            tree[k].parent = tmp;
        }
    }
    // 初始化size height
    tree[1].calcu_height();
    tree[1].calculate_size();

    while (M--) {
        int flag; scanf("%d", &flag);
        if (flag == 0) {
            // 移除源子树并更新size height
            auto src_node = get_node();
            src_node->parent->succ->pred = src_node->parent->pred;
            src_node->parent->pred->succ = src_node->parent->succ;
            src_node->parent->parent->update_height(src_node->height, 0);
            for (auto i = src_node->parent->parent;; i = i->parent->parent) {
                i->size -= src_node->size;
                if (i->parent == nullptr) break;
            }
            delete src_node->parent;
            
            auto des_node = get_node();
            int rank; scanf("%d", &rank);
            for (auto i = des_node;; i = i->parent->parent) {
                i->size += src_node->size;
                if (i->parent == nullptr) break;
            }

            des_node->update_height(0, src_node->height);
            auto tmp = des_node->header;
            for (int i = 0; i < rank; i++) tmp = tmp->succ;

            auto res = new NodeList;
            res->child = src_node;
            res->parent = des_node;
            res->pred = tmp; res->succ = tmp->succ;
            src_node->parent = res;
            tmp->succ->pred = res; tmp->succ = res;
        }
        else if (flag == 1) {
            auto node = get_node();
            printf("%d\n", node->height - 1);
        }
        else if (flag == 2) {
            auto node = get_node();
            printf("%d\n", node->size);
        }
        else exit(EXIT_FAILURE);
    }
}