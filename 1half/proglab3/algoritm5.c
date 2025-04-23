#include<stdio.h>

int main() {
    int a;
    scanf("%d", &a);
    int s = 0;
    for (int n = 2; n < a; n++) {
        if (a%n==0) {
            s++;
}
}
    if (s == 0) {
        puts("1");
}  else {
        puts("0");
}
}
// простое или составное число
