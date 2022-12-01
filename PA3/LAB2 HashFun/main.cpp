#include <cstdio>
#include <iostream>
#include "hashtable.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Two options are required:\n");
        printf("0 allplus_hashing 1 code_hashing\n");
        printf("0 linear_probe 1 double_square_probe 2 overflow_probe\n");
        exit(EXIT_FAILURE);
    }
    int type;
    char buffer[1000]; int data;
    hashing_strategy *hashing;
    collision_strategy *collision;

    if (argv[1][0] == '0') hashing = new allplus_hashing;
    else if (argv[1][0] == '1') hashing = new code_hashing;
    else exit(EXIT_FAILURE);

    if (argv[2][0] == '0') collision = new linear_probe;
    else if (argv[2][0] == '1') collision = new double_square_probe;
    else if (argv[2][0] == '2') collision = new overflow_probe;

    hashtable table(TABLE_SIZE, hashing, collision);
    double t1 = clock();
    while (true) {
        scanf("%d", &type);
        if (type == 0) {
            scanf("%s", buffer); scanf("%d", &data);
            table.insert(hash_entry(buffer, data));
        }
        else if (type == 1) {
            scanf("%s", buffer);
            printf("%d\n", table.query(buffer));
        }
        else break;
    }
    double t2 = clock();
    printf("TIME: %lf\n", (t2 - t1) / CLOCKS_PER_SEC);
    return 0;
}