#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SelectionSort(int A[], int n, int *C, int *M) {
    *C = 0;
    *M = 0;
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            (*C)++;
            if (A[j] < A[k]) {
                k = j;
            }
        }
        int temp = A[i];
        A[i] = A[k];
        A[k] = temp;
        *M += 3;
    }
}

void UpdateSelectionSort(int A[], int n, int *C, int *M) {
    *C = 0;
    *M = 0;
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            (*C)++;
            if (A[j] < A[k]) {
                k = j;
            }
        }
        if (k != i) {
            int temp = A[i];
            A[i] = A[k];
            A[k] = temp;
            *M += 3;
        }
    }
}

void FillInc(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
}

void FillDec(int A[], int n) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int A[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand();
    }
}

long long CheckSum(int A[], int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

int RunNumber(int A[], int n) {
    int runs = 1;
    for (int i = 1; i < n; i++) {
        if (A[i - 1] > A[i]) {
            runs++;
        }
    }
    return runs;
}

void PrintMas(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void TeorTable() {
    printf("%-5s | %-10s | %-10s %-10s %-10s | %-10s %-10s %-10s\n", "N", "M+C теор.", "Убыв.", "Случ.", "Возр.", "Убыв.", "Случ.", "Возр.");
    printf("%-5s | %-10s | %-10s %-10s %-10s | %-10s %-10s %-10s\n", "", "", "Исх.", "Исх.", "Исх.", "Улучш.", "Улучш.", "Улучш.");
    printf("----------------------------------------------------------------------------------------------------------\n");
}

void ZnachTable(int n, int M_C, int C1, int M1, int C2, int M2, int C3, int M3, int C4, int M4, int C5, int M5, int C6, int M6) {
    printf("%-5d | %-10d | %-10d %-10d %-10d | %-10d %-10d %-10d\n", n, M_C, C1 + M1, C2 + M2, C3 + M3, C4 + M4, C5 + M5, C6 + M6);
    printf("----------------------------------------------------------------------------------------------------------\n");
}

int main() {
    int n = 10;
    int A[n];
    int C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6;

    // n
    int C_N = ((n*n - n) / 2);
    int M_N = 3*(n-1);
    int M_C = C_N + M_N;



    // n
    TeorTable();

    FillDec(A, n);
    SelectionSort(A, n, &C1, &M1);
    FillRand(A, n);
    SelectionSort(A, n, &C2, &M2);
    FillInc(A, n);
    SelectionSort(A, n, &C3, &M3);
    
    FillDec(A, n);
    UpdateSelectionSort(A, n, &C4, &M4);
    FillRand(A, n);
    UpdateSelectionSort(A, n, &C5, &M5);
    FillInc(A, n);
    UpdateSelectionSort(A, n, &C6, &M6);

    ZnachTable(n, M_C, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);

    // b
    int b = 100;
    int L[b];

    int C_B = ((b*b - b) / 2);
    int M_B = 3*(b-1);
    int MC = C_B + M_B;

    TeorTable();

    FillDec(L, b);
    SelectionSort(L, b, &C1, &M1);
    FillRand(L, b);
    SelectionSort(L, b, &C2, &M2);
    FillInc(L, b);
    SelectionSort(L, b, &C3, &M3);
    
    FillDec(L, b);
    UpdateSelectionSort(L, b, &C4, &M4);
    FillRand(L, b);
    UpdateSelectionSort(L, b, &C5, &M5);
    FillInc(L, b);
    UpdateSelectionSort(L, b, &C6, &M6);

    ZnachTable(b, MC, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);
    
}
