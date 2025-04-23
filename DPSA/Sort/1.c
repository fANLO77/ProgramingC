#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc (int n,int A[]) {
    for (int i = 0; i<n; i++) {
        A[i] = i+1;
    }
}
void FillDec (int A[], int n) {
    for (int i = 0; i<n; i++) {
        A[i] = n-i;
    }
}

void FillRand (int A[], int n) {
    srand(time(NULL));
    for(int i = 0; i<n; i++){
        A[i] = rand();
    }
}

long long CheckSum (int A[], int n) {
    long long sum = 0;
    for (int i = 0; i<n; i++) {
        sum+=A[i];
    }
    return sum;
}
int RunNumber (int A[], int n) {
    int runs = 0;
    for (int i = 0; i<n; i++) {
        if (A[i-1] > A[i]) {
            runs++;
        }
    }
    return runs;
}

void PrintMas (int A[], int n) {
    for (int i = 0; i <n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main () {
    int n = 10;
    int A[n];
    FillInc(n,A);
    printf("Массив с возрастающими числами: ");
    PrintMas(A,n);
    printf("Сумма: %lld\n", CheckSum(A,n));
    printf("Серии: %d\n", RunNumber(A,n));
    FillDec(A,n);
    printf("Массив с убывающими числами: ");
    PrintMas(A,n);
    printf("Сумма: %lld\n", CheckSum(A,n));
    printf("Серии: %d\n", RunNumber(A,n));
    FillRand(A,n);
    printf("Массив с рандомными числами: ");
    PrintMas(A,n);
    printf("Сумма: %lld\n", CheckSum(A,n));
    printf("Серии: %d\n", RunNumber(A,n));
}





    // FillInc(n,A);
    // printf("Массив с возрастающими числами: ");
    // PrintMas(A,n);
    // printf("Сумма: %lld\n", CheckSum(A,n));
    // printf("Серии: %d\n", RunNumber(A,n));

    // FillDec(A,n);
    // printf("Массив с убывающими числами: ");
    // UpdateSelectionSort(A,n);
    // PrintMas(A,n);
    // printf("Сумма: %lld\n", CheckSum(A,n));
    // printf("Серии: %d\n", RunNumber(A,n));

    // FillRand(A,n);
    // printf("Массив с рандомными числами: ");
    // UpdateSelectionSort(A,n);
    // PrintMas(A,n);
    // printf("Сумма: %lld\n", CheckSum(A,n));
    // printf("Серии: %d\n", RunNumber(A,n));