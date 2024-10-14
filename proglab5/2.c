#include <stdio.h>

int main() {
    int a;
    int k;
    scanf("%d", &a);
    scanf("%d", &k);
    int bits = sizeof(a);
    k = k%bits;
    int res = (a << k) | (a >> (bits - k));
    printf("%d\n", res);

}