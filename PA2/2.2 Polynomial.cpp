#include <iostream>
#define DEFAULT_CAPACITY 3
using namespace std;

const int M = 1000000007;

// 报错
void print_error(int line) {
    printf("Error in line %d\n", line);
    exit(1);
}

template <typename T>
class Vector {
    int _size; int _capacity; T *_elem;
    void copyFrom(const T *A, int lo, int hi) {
        _elem = new T[_capacity = (DEFAULT_CAPACITY < 2 * (hi - lo)) ? 2 * (hi - lo) : DEFAULT_CAPACITY];
        for (_size = 0; lo < hi; _size++, lo++)
            _elem[_size] = A[lo];
    }
    void expand() {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T *oldElem = _elem; _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldElem[i];
        delete[] oldElem;
    }
    void shrink() {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;
        T *oldElem = _elem; _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
        delete[] oldElem;
    }
public:
    Vector() : _size(0), _capacity(DEFAULT_CAPACITY) {
        _elem = new T[DEFAULT_CAPACITY];
    }
    ~Vector() {
        delete[] _elem;
    }
    int size() const { return _size; }
    bool empty() const { return _size == 0; }
    T &operator[] (int r) {
        if (r >= _size || r < 0) print_error(__LINE__);
        return _elem[r];
    }
    void push_back(T r) {
        expand();
        _elem[_size++] = move(r);
    }
    T pop_back() {
        T e = _elem[--_size];
        shrink();
        return e;
    }
};

// 多项式类
class Poly {
public:
    int *content;
    Poly() : content(new int[65]()) {};
    Poly(const Poly &other) : content(new int[65]()) {
        for (int i = 0; i < 65; i++) {
            content[i] = other.content[i];
        }
    }
    ~Poly() { delete[] content; }
    Poly &operator*(const Poly &other) {
        int *result = new int[65]();
        for (int i = 0; i < 65; i++) {
            if (other.content[i] == 0) continue;
            for (int j = 0; j < 65; j++) {
                if (content[j] == 0) continue;
                result[i + j] =
                    int((((long long)result[i + j] + (long long)other.content[i] * (long long)content[j]) % M + M) % M);
            }
        }
        delete[] content;
        content = result;
        return *this;
    }
    Poly &operator+(const Poly &other) {
        for (int i = 0; i < 65; i++) {
            content[i] += other.content[i];
            content[i] = (content[i] % M + M) % M;
        }
        return *this;
    }
    Poly &operator-(const Poly &other) {
        for (int i = 0; i < 65; i++) {
            content[i] -= other.content[i];
            content[i] = (content[i] % M + M) % M;
        }
        return *this;
    }
    Poly &operator=(const Poly &other) {
        if (this == &other) return *this;
        for (int i = 0; i < 65; i++) {
            content[i] = other.content[i];
        }
        return *this;
    }
    Poly &operator^(const Poly &other) {
        Poly res = *this;
        for (int i = 1; i < other.content[0]; i++) {
            *this = *this * res;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Poly &x);
};

ostream &operator<<(ostream &out, const Poly &x) {
    bool zero = false;
    for (int i = 64; i >= 0; i--) {
        if (x.content[i] != 0) {
            zero = true;
        }
        if (zero) {
            out << x.content[i] << " ";
        }
    }
    if (!zero) out << '0';
    return out;
}

const char pri[7][7] = {
    //+  -    *    ^    (    )    \0
    '>', '>', '<', '<', '<', '>', '>',
    '>', '>', '<', '<', '<', '>', '>',
    '>', '>', '>', '<', '<', '>', '>',
    '>', '>', '>', '>', '<', '>', '>',
    '<', '<', '<', '<', '<', '=', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    '<', '<', '<', '<', '<', ' ', '='
};

int priority(char a) {
    switch (a) {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '^':
        return 3;
    case '(':
        return 4;
    case ')':
        return 5;
    case '\0':
        return 6;
    default:
        print_error(__LINE__);
    }
}

// 读取常数并将其转为多项式类
void readNumber(string::const_iterator &p, Vector<Poly> &stk) {
    int res = 0;
    while (isdigit(*p)) {
        res = res * 10 + (int)(*p - '0');
        p++;
    }
    Poly pres;
    pres.content[0] = res;
    stk.push_back(move(pres));
}

Poly calculate(Poly &p1, Poly &p2, char op) {
    switch (op) {
    case '+':
        return p1 + p2;
    case '-':
        return p1 - p2;
    case '^':
        return p1 ^ p2;
    case '*':
        return p1 * p2;
    default:
        print_error(__LINE__);
    }
}

Poly evaluate(const string &s) {
    Vector<Poly> opnd; Vector<char> optr;
    string::const_iterator S = s.cbegin();
    optr.push_back('\0');
    while (!optr.empty()) {
        if (isdigit(*S)) {
            readNumber(S, opnd);
        }
        else if (*S == 'x') {
            Poly tmp;
            tmp.content[1] = 1;
            opnd.push_back(move(tmp));
            S++;
        }
        else switch (pri[priority(optr[optr.size() - 1])][priority(*S)]) {
        case '<':
            optr.push_back(*S); S++;
            break;
        case '=':
            optr.pop_back(); S++;
            break;
        case '>': {
            char op = optr.pop_back();
            Poly p2 = opnd.pop_back(), p1 = opnd.pop_back();
            opnd.push_back(calculate(p1, p2, op));
            break;
        }
        default:
            print_error(__LINE__);
        }
    }
    return opnd.pop_back();
}

int main() {
    string s;
    cin >> s;
    s.push_back('\0');
    // 对字符串进行预处理，添加省略的乘号
    for (string::iterator S = s.begin(); S != s.end(); S++) {
        if (*S == '(') {
            if (isdigit(*(S - 1)) || *(S - 1) == ')' || *(S - 1) == 'x') {
                s.insert(S, '*');
            }
        }
        if (*S == 'x') {
            if (isdigit(*(S - 1)) || *(S - 1) == ')') {
                s.insert(S, '*');
            }
        }
    }
    cout << evaluate(s) << endl;
}