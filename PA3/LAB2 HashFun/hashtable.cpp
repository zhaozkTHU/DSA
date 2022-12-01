#include "hashtable.h"
int naive_hashing::operator()(char *str, int N) {
    if (str == NULL) return 0;
    else return (str[0] + N) % N;
}

int allplus_hashing::operator()(char *str, int N) {
    if (str == nullptr) return 0;
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        res += (int)str[i];
    }
    return (res + N) % N;
}

int code_hashing::operator()(char *str, int N) {
    if (str == nullptr) return 0;
    unsigned int res = 0;
    for (size_t n = strlen(str), i = 0; i < n; i++) {
        res = (res << 5) | (res >> 27);
        res += str[i];
    }
    return (res + N) % N;
}

int linear_probe::operator()(hash_entry *Table, int table_size, int last_choice) {
    return (last_choice + 1) % table_size;
}
void linear_probe::init() {
    return;// do nothing
}

void double_square_probe::init() {
    time = 0;
}

int double_square_probe::operator()(hash_entry *Table, int table_size, int last_choice) {
    int res = 0;
    time += 1;
    if (time % 2 != 0) {
        res = (last_choice + (time / 2) * (time / 2) + (time / 2 + 1) * (time / 2 + 1)) % table_size;
    }
    else {
        res = (last_choice - 2 * (time / 2) * (time / 2)) % table_size;
    }
    if (res < 0) res += table_size;
    return res;
}

void overflow_probe::init() {
    overflow = false;
}

int overflow_probe::operator()(hash_entry *Table, int table_size, int last_choice) {
    if (overflow) {
        return last_choice + 1;
    }
    else {
        overflow = true;
        return table_size / 2 + 1;
    }
}