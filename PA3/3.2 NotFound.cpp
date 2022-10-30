#include <iostream>
#define MAX_CAPACITY 524288
using namespace std;

// 压缩内存占用
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
};

int main() {
    Bit a;
    char c;
    unsigned len = 0;
    while (scanf("%c", &c) != EOF) {
        if (c == '0') a.set(len, 0);
        else if (c == '1') a.set(len, 1);
        else break;
        len++;
    }

    for (unsigned answer_length = 1; answer_length <= 24; answer_length++) { // 对答案长度进行迭代
        Bit exist;
        unsigned exists = 0;

        // 计算第一个待验证答案
        unsigned answer = 0;
        for (unsigned i = 0; i < answer_length; i++) answer += a[i] << (answer_length - i - 1);
        if (exist[answer] == 0) {
            exist.set(answer, 1);
            exists += 1;
            if (exists == (1 << answer_length)) break;
        }

        for (unsigned start = 1; start <= len - answer_length; start++) {
            // 由前一个答案递推
            answer &= ~(1 << (answer_length - 1));
            answer <<= 1;
            answer += a[start + answer_length - 1];
            
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
                    return 0;
                }
            }
        }
    }
}