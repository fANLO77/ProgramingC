#include <stdio.h>

int main() {
    int a;
    int k;
    int res;
    scanf("%d", &a);
    scanf("%d", &k);
    res = (a << k) | ((1 << k) - 1);
    printf("%d\n", res);

    
    
    // char x = 5
    // 00010100
    // 1 11 111 1111
    // 1 3 7 15 31

}