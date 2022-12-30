#include <iostream>
#define stature(p) ((p) ? (p)->height : -1)
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )
#define FromParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#define stature(p) ((p) ? (p)->height : -1)
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc \
   ) \
   ) \
)
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //理想平衡条件
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //平衡因子
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVL平衡条件
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T> *;
template <typename T> struct BinNode {
    T data; //数值
    BinNodePosi<T> parent, lc, rc;
    int height; //高度（通用）
    BinNode():
        parent(nullptr), lc(nullptr), rc(nullptr), height(0) {}
    BinNode(T e, BinNodePosi<T> p = nullptr, BinNodePosi<T> lc = nullptr, BinNodePosi<T> rc = nullptr,
        int h = 0, int l = 1):
        data(e), parent(p), lc(lc), rc(rc), height(h) {}
    BinNodePosi<T> succ() {
        BinNodePosi<T> s = this; //记录后继的临时变量
        if (rc) { //若有右孩子，则直接后继必在右子树中，具体地就是
            s = rc; //右子树中
            while (HasLChild(*s)) s = s->lc; //最靠左（最小）的节点
        }
        else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
            while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
            s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
        }
        return s;
    }
    BinNodePosi<T> insertAsLC(T const &e) {
        return lc = new BinNode(e, this);
    }
    BinNodePosi<T> insertAsRC(T const &e) {
        return rc = new BinNode(e, this);
    }
};

template <typename T> class BinTree {
protected:
    int _size; BinNodePosi<T> _root;
    virtual int updateHeight(BinNodePosi<T> x) {
        return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
    };
    void updateHeightAbove(BinNodePosi<T> x) {
        while (x) { updateHeight(x); x = x->parent; }
    } //从x出发，覆盖历代祖先。可优化
    int remove(BinNodePosi<T> x) { //assert: x为二叉树中的合法位置
        FromParentTo(*x) = nullptr; //切断来自父节点的指针
        updateHeightAbove(x->parent); //更新祖先高度
        int n = removeAt(x); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
    }
    static int removeAt(BinNodePosi<T> x) { //assert: x为二叉树中的合法位置
        if (!x) return 0; //递归基：空树
        int n = 1 + removeAt(x->lc) + removeAt(x->rc); //递归释放左、右子树
        delete x; return n; //释放被摘除节点，并返回删除节点总数
    }
public:
    BinTree(): _size(0), _root(nullptr) {}
    ~BinTree() { if (0 < _size) remove(_root); }
    int size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi<T> root() const { return _root; }
}; //BinTree

template <typename T> class BST: public BinTree<T> {
protected:
    using BinTree<T>::updateHeight;
    BinNodePosi<T> _hot;
    BinNodePosi<T> connect34(
        BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c,
        BinNodePosi<T> T0, BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3
    ) {
        a->lc = T0; if (T0) T0->parent = a;
        a->rc = T1; if (T1) T1->parent = a; updateHeight(a);
        c->lc = T2; if (T2) T2->parent = c;
        c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
        b->lc = a; a->parent = b;
        b->rc = c; c->parent = b; updateHeight(b);
        return b;
    }
    BinNodePosi<T> rotateAt(BinNodePosi<T> v) { //v为非空孙辈节点
        if (!v) { printf("\a\nFail to rotate a null node\n"); exit(-1); }
        BinNodePosi<T> p = v->parent; BinNodePosi<T> g = p->parent; //视v、p和g相对位置分四种情况
        if (IsLChild(*p)) /* zig */
            if (IsLChild(*v)) { /* zig-zig */ 
                p->parent = g->parent; //向上联接
                return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
            }
            else { /* zig-zag */  
                v->parent = g->parent; //向上联接
                return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
            }
        else  /* zag */
            if (IsRChild(*v)) { /* zag-zag */ 
                p->parent = g->parent; //向上联接
                return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
            }
            else { /* zag-zig */ 
                v->parent = g->parent; //向上联接
                return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
            }
    }
    static BinNodePosi<T> removeAt(BinNodePosi<T> &x, BinNodePosi<T> &hot) {
        BinNodePosi<T> w = x; //实际被摘除的节点，初值同x
        BinNodePosi<T> succ = NULL; //实际被删除节点的接替者
        if (!HasLChild(*x)) //若*x的左子树为空，则可
            succ = x = x->rc; //直接将*x替换为其右子树
        else if (!HasRChild(*x)) //若右子树为空，则可
            succ = x = x->lc; //对称地处理——注意：此时succ != NULL
        else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
            w = w->succ(); //（在右子树中）找到*x的直接后继*w
            std::swap(x->data, w->data); //交换*x和*w的数据元素
            BinNodePosi<T> u = w->parent;
            ((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w
        }
        hot = w->parent; //记录实际被删除节点的父亲
        if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
        delete w; return succ; //释放被摘除节点，返回接替者
    }
public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
    using BinTree<T>::_root;
    using BinTree<T>::_size;
    virtual BinNodePosi<T> &search(const T &e) {
        if (!_root || e == _root->data) { _hot = nullptr; return _root; } //空树，或恰在树根命中
        for (_hot = _root; ; ) { //否则，自顶而下
            BinNodePosi<T> &v = (e < _hot->data) ? _hot->lc : _hot->rc; //确定方向，深入一层
            if (!v || e == v->data) return v; _hot = v; //一旦命中或抵达叶子，随即返回
        } //返回目标节点位置的引用，以便后续插入、删除操作
    }
    virtual BinNodePosi<T> insert(const T &e) {
        BinNodePosi<T> &x = search(e); if (x) return x; //确认目标不存在（留意对_hot的设置）
        x = new BinNode<T>(e, _hot); //创建新节点x：以e为关键码，以_hot为父
        _size++; //更新全树规模
        BinTree<T>::updateHeightAbove(x); //更新x及其历代祖先的高度
        return x; //新插入的节点，必为叶子
    }
    virtual bool remove(const T &e) {
        BinNodePosi<T> &x = search(e); if (!x) return false; //确认目标存在（留意_hot的设置）
        removeAt(x, _hot); _size--; //实施删除
        BinTree<T>::updateHeightAbove(_hot); //更新_hot及其历代祖先的高度
        return true;
    }
    BinNodePosi<T> hot() {
        return _hot;
    }
    /*DSA*/void balance() { _root = _root->balance(); }
};

template <typename T> class AVL: public BST<T> { //由BST派生AVL树模板类
public:
    using BST<T>::_hot;
    using BST<T>::_size;
    using BST<T>::_root;
    BinNodePosi<T> insert(const T &e) {
        BinNodePosi<T> &x = BST<T>::search(e); if (x) return x; //确认目标节点不存在
        BinNodePosi<T> xx = x = new BinNode<T>(e, _hot); _size++; //创建新节点x
        // 此时，x的父亲_hot若增高，则其祖父有可能失衡
        for (BinNodePosi<T> g = _hot; g; g = g->parent) //从x之父出发向上，逐层检查各代祖先g
            if (!AvlBalanced(*g)) { //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将子树
                FromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g))); //重新接入原树
                break; //局部子树复衡后，高度必然复原；其祖先亦必如此，故调整结束
            }
            else //否则（g仍平衡）
                BST<T>::updateHeight(g); //只需更新其高度（注意：即便g未失衡，高度亦可能增加）
        return xx; //返回新节点位置
    }
    bool remove(const T &e) {
        BinNodePosi<T> &x = BST<T>::search(e); if (!x) return false; //确认目标存在（留意_hot的设置）
        BST<T>::removeAt(x, _hot); _size--; //先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
        for (BinNodePosi<T> g = _hot; g; g = g->parent) { //从_hot出发向上，逐层检查各代祖先g
            if (!AvlBalanced(*g)) //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至
                g = FromParentTo(*g) = BST<T>::rotateAt(tallerChild(tallerChild(g))); //原父亲
            BST<T>::updateHeight(g); //更新高度（注意：即便g未失衡或已恢复平衡，高度均可能降低）
        } //可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
        return true; //删除成功
    }
    // BST::search()等其余接口可直接沿用
};

template <typename T> class Splay: public BST<T> { //由BST派生的Splay树模板类
protected:
    using BST<T>::_root;
    using BST<T>::_size;
    using BST<T>::_hot;
    using BST<T>::updateHeight;
    using BST<T>::updateHeightAbove;
    void attachAsLC(BinNodePosi<T> lc, BinNodePosi<T> p) { p->lc = lc; if (lc) lc->parent = p; }
    void attachAsRC(BinNodePosi<T> p, BinNodePosi<T> rc) { p->rc = rc; if (rc) rc->parent = p; }
    BinNodePosi<T> splay(BinNodePosi<T> v) {
        if (!v) return NULL; BinNodePosi<T> p; BinNodePosi<T> g; //*v的父亲与祖父
        while ((p = v->parent) && (g = p->parent)) { //自下而上，反复对*v做双层伸展
            BinNodePosi<T> gg = g->parent; //每轮之后*v都以原曾祖父（great-grand parent）为父
            if (IsLChild(*v))
                if (IsLChild(*p)) { //zig-zig
                    attachAsLC(p->rc, g); attachAsLC(v->rc, p);
                    attachAsRC(p, g); attachAsRC(v, p);
                }
                else { //zig-zag
                    attachAsLC(v->rc, p); attachAsRC(g, v->lc);
                    attachAsLC(g, v); attachAsRC(v, p);
                }
            else if (IsRChild(*p)) { //zag-zag
                attachAsRC(g, p->lc); attachAsRC(p, v->lc);
                attachAsLC(g, p); attachAsLC(p, v);
            }
            else { //zag-zig
                attachAsRC(p, v->lc); attachAsLC(v->rc, g);
                attachAsRC(v, g); attachAsLC(p, v);
            }
            if (!gg) v->parent = NULL; //若*v原先的曾祖父*gg不存在，则*v现在应为树根
            else //否则，*gg此后应该以*v作为左或右孩子
                (g == gg->lc) ? attachAsLC(v, gg) : attachAsRC(gg, v);
            updateHeight(g); updateHeight(p); updateHeight(v);
        } //双层伸展结束时，必有g == NULL，但p可能非空
        if (p = v->parent) { //若p果真非空，则额外再做一次单旋
            if (IsLChild(*v)) { attachAsLC(v->rc, p); attachAsRC(v, p); }
            else { attachAsRC(p, v->lc); attachAsLC(p, v); }
            updateHeight(p); updateHeight(v);
        }
        v->parent = NULL; return v;
    }
public:
    BinNodePosi<T> &search(const T &e) {
        BinNodePosi<T> p = BST<T>::search(e);
        _root = splay(p ? p : _hot); //将最后一个被访问的节点伸展至根
        return _root;
    }
    BinNodePosi<T> insert(const T &e) {
        if (!_root) { _size = 1; return _root = new BinNode<T>(e); } //原树为空
        BinNodePosi<T> t = search(e); if (e == t->data) return t; //目标节点t若存在，伸展至根
        if (t->data < e) { //在右侧嫁接
            t->parent = _root = new BinNode<T>(e, NULL, t, t->rc); //lc == t必非空
            if (t->rc) { t->rc->parent = _root; t->rc = NULL; } //rc或为空
        }
        else { //在左侧嫁接
            t->parent = _root = new BinNode<T>(e, NULL, t->lc, t); //rc == t必非空
            if (t->lc) { t->lc->parent = _root; t->lc = NULL; } //lc或为空
        }
        _size++; updateHeightAbove(t); return _root; //更新规模及高度，报告插入成功
    }
    bool remove(const T &e) {
        if (!_root || (e != search(e)->data)) return false; //若目标存在，则伸展至根
        BinNodePosi<T> L = _root->lc, R = _root->rc; delete _root; //记下左、右子树L、R后，释放之
        if (!R) { //若R空，则
            if (L) L->parent = NULL; _root = L; //L即是余树
        }
        else { //否则
            _root = R; R->parent = NULL; search(e); //在R中再次查找e：注定失败，但其中的最小节点必
            if (L) L->parent = _root; _root->lc = L; //伸展至根（且无左孩子），故可令其以L作为左子树
        }
        if (--_size) updateHeight(_root); return true; //更新规模及树高，报告删除成功
    }
};

int main(int argc, char **argv) {
    BST<int> *test;
    test = new AVL<int>;
#ifdef _OJ_
    test = new AVL<int>;
#else
    if (argc != 2) {
        printf("Please choose AVL or splay\n");
        exit(EXIT_FAILURE);
    }
    if (std::string(argv[1]) == "AVL") {
        test = new BST<int>;
    }
    else if (std::string(argv[1]) == "splay") {
        test = new Splay<int>;
    }
    else {
        printf("Please choose AVL or splay\n");
        exit(EXIT_FAILURE);
    }
#endif
    int n;
    char op;
    int num;
    double start = clock();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf(" %c%d", &op, &num);
        if (op == 'A') test->insert(num);
        if (op == 'B') test->remove(num);
        if (op == 'C') {
            auto res = test->search(num);
            if (res) printf("%d\n", res->data);
            else {
                if (test->hot())
                    if (test->hot()->data <= num)
                        printf("%d\n", test->hot()->data);
                    else if (test->hot()->parent)
                        printf("%d\n", test->hot()->parent->data);
                    else
                        printf("-1\n");
                else
                    printf("-1\n");
            }
        }
    }
    double end = clock();
    printf("%s: %lfs\n", argv[1], (end - start) / CLOCKS_PER_SEC);
}