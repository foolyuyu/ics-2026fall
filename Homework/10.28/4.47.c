#include <stdio.h>

void bubble_a (long *data, long count) {
    long *p, *last;
    for (last = data + count - 1; last > data; last--) {
        for (p = data; p < last; p++) {
            if (*(p + 1) < *p) {
                long t = *(p + 1);
                *(p + 1) = *p;
                *p = t;
            }
        }
    }
}



long array[6] = {
    0xbca, 0xcba, 0xacb,
    0xcab, 0xabc, 0xbac
};

int main() {
    long count = sizeof(array) / 8;
    bubble_a(array, count);
    for (long *p = array; p != array + count; ++p) {
        printf("%ld ", *p);
    }
}
