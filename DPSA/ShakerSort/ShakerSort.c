#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void BubbleSort (int A[], int n, int *C, int *M) {
    *C = 0;
    *M = 0;
    for (int i = 0; i < n -1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*C)++;
            if (A[j] > A[j+1]) {
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                (*M)+=3;
            }
        }
    }
}


void ShakerSort (int A[], int n, int *C, int *M) {
    *C = 0;
    *M = 0;
    int R = n-1;
    int k = n-1;
    int L = 0;
    do {
        for (int j = R; j > L; j--) {
            (*C)++;
            if (A[j] < A[j-1]) {
                int temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                k = j;
                (*M)+=3;
            }
        }
        L = k;
        for (int j = L; j < R; j++) {
            (*C)++;
            if (A[j] > A[j+1]) {
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                k = j;
                (*M)+=3;
            }
        }
        R = k;
    } while (L<R);
}

void TeorTable() {
    printf("%-5s | %-20s | %-20s\n", "", "BubbleSort", "ShakerSort");
    printf("%-5s | %-10s %-10s %-10s | %-10s %-10s %-10s \n", "N", "Убыв.", "Случ.", "Возр.", "Убыв.", "Случ.", "Возр.");
    printf("-----------------------------------------------------\n");
}

void ZnachTable(int n, int C1, int M1, int C2, int M2, int C3, int M3, int C4, int M4, int C5, int M5, int C6, int M6) {
    printf("%-5d | %-6d %-6d %-6d | %-6d %-6d %-6d \n", n, C1 + M1, C2 + M2, C3 + M3, C4 + M4, C5 + M5, C6 + M6);
    printf("-----------------------------------------------------\n");
}

int main () {
    int n1 = 100;
    int A1[n1];
    int C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6;

    TeorTable();

    FillDec(A1, n1);
    BubbleSort(A1, n1, &C1, &M1);
    FillRand(A1, n1);
    BubbleSort(A1, n1, &C2, &M2);
    FillInc(A1, n1);
    BubbleSort(A1, n1, &C3, &M3);

    FillDec(A1, n1);
    ShakerSort(A1, n1, &C4, &M4);
    FillRand(A1, n1);
    ShakerSort(A1, n1, &C5, &M5);
    FillInc(A1, n1);
    ShakerSort(A1, n1, &C6, &M6);

    ZnachTable(n1, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);

    
    int n2 = 200;
    int A2[n2];

    FillDec(A2, n2);
    BubbleSort(A2, n2, &C1, &M1);
    FillRand(A2, n2);
    BubbleSort(A2, n2, &C2, &M2);
    FillInc(A2, n2);
    BubbleSort(A2, n2, &C3, &M3);

    FillDec(A2, n2);
    ShakerSort(A2, n2, &C4, &M4);
    FillRand(A2, n2);
    ShakerSort(A2, n2, &C5, &M5);
    FillInc(A2, n2);
    ShakerSort(A2, n2, &C6, &M6);

    ZnachTable(n2, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);


    int n3 = 300;
    int A3[n3];

    FillDec(A3, n3);
    BubbleSort(A3, n3, &C1, &M1);
    FillRand(A3, n3);
    BubbleSort(A3, n3, &C2, &M2);
    FillInc(A3, n3);
    BubbleSort(A3, n3, &C3, &M3);

    FillDec(A3, n3);
    ShakerSort(A3, n3, &C4, &M4);
    FillRand(A3, n3);
    ShakerSort(A3, n3, &C5, &M5);
    FillInc(A3, n3);
    ShakerSort(A3, n3, &C6, &M6);

    ZnachTable(n3, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);

    int n4 = 400;
    int A4[n4];

    FillDec(A4, n4);
    BubbleSort(A4, n4, &C1, &M1);
    FillRand(A4, n4);
    BubbleSort(A4, n4, &C2, &M2);
    FillInc(A4, n4);
    BubbleSort(A4, n4, &C3, &M3);

    FillDec(A4, n4);
    ShakerSort(A4, n4, &C4, &M4);
    FillRand(A4, n4);
    ShakerSort(A4, n4, &C5, &M5);
    FillInc(A4, n4);
    ShakerSort(A4, n4, &C6, &M6);

    ZnachTable(n4, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);


    int n5 = 500;
    int A5[n5];

    FillDec(A5, n5);
    BubbleSort(A5, n5, &C1, &M1);
    FillRand(A5, n5);
    BubbleSort(A5, n5, &C2, &M2);
    FillInc(A5, n5);
    BubbleSort(A5, n5, &C3, &M3);

    FillDec(A5, n5);
    ShakerSort(A5, n5, &C4, &M4);
    FillRand(A5, n5);
    ShakerSort(A5, n5, &C5, &M5);
    FillInc(A5, n5);
    ShakerSort(A5, n5, &C6, &M6);

    ZnachTable(n5, C1, M1, C2, M2, C3, M3, C4, M4, C5, M5, C6, M6);
}