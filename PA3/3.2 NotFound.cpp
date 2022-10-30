#include <iostream>
#define MAX_CAPACITY 524288
using namespace std;

class Bit {
    unsigned *content;
public:
    Bit() : content(new unsigned[MAX_CAPACITY]()) {}
    ~Bit() { delete[] content; }
    unsigned operator[] (unsigned num) {
        return (content[num / 32] >> (num % 32)) & 1;
    }
    void set(unsigned num, unsigned value) {
        if (value == 0) {
            content[num / 32] &= ~(1 << (num % 32));
        }
        else {
            content[num / 32] |= (1 << (num % 32));
        }
    }
    void init() {
        for (int i = 0; i < MAX_CAPACITY; i++) content[i] = 0;
    }
};

/// @param a 待取数组
/// @param num 取第num位0或1
inline int get_01(unsigned *a, unsigned num) {
    return (a[num / 32] >> (num % 32)) & 1;
}

int main() {
    unsigned *a = new unsigned[MAX_CAPACITY]();
    char c;
    unsigned len = 0;
    while (scanf("%c", &c) != EOF) {
        if (c == '0') a[len / 32] += 0 << len % 32;
        else if (c == '1') a[len / 32] += 1 << len % 32;
        else break;
        len++;
    }

    for (unsigned answer_length = 1; answer_length <= 24; answer_length++) { // 对答案长度进行迭代
        Bit exist;
        unsigned exists = 0;

        unsigned answer = 0;
        for (unsigned i = 0; i < answer_length; i++) answer += get_01(a, i) << (answer_length - i - 1);
        if (exist[answer] == 0) {
            exist.set(answer, 1);
            exists += 1;
            if (exists == (1 << answer_length)) break;
        }

        for (unsigned start = 1; start <= len - answer_length; start++) {
            answer &= ~(1 << (answer_length - 1));
            answer <<= 1;
            answer += get_01(a, start + answer_length - 1);
            if (exist[answer] == 0) {
                exist.set(answer, 1);
                exists += 1;
                if (exists == (1 << answer_length)) break;
            }
        }
        if (exists != (1 << answer_length)) {
            for (unsigned i = 0; i < 1 << answer_length; i++) {
                if (exist[i] == 0) {
                    for (unsigned j = 0; j < answer_length; j++) {
                        printf("%d", (i >> (answer_length - j - 1)) & 1);
                    }
                    printf("\n");
                    delete[] a;
                    return 0;
                }
            }
        }
    }
}