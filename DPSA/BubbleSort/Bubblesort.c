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

void TeorTable() {
    printf("%-5s | %-10s | %-10s %-10s %-10s |\n", "N", "M+C теор.", "Убыв.", "Случ.", "Возр.");
    printf("-----------------------------------------------------\n");
}

void ZnachTable(int n, int T, int C1, int M1, int C2, int M2, int C3, int M3) {
    printf("%-5d | %-10d | %-10d %-10d %-10d \n", n, T, C1 + M1, C2 + M2, C3 + M3);
    printf("-----------------------------------------------------\n");
}

int main () {
    int n1 = 100;
    int A1[n1];
    int C1, M1, C2, M2, C3, M3;

    int C_1 = (n1*n1 - n1) / 2;
    int M_1 = (3*(n1*n1 - n1)) / 4;
    int T1 = M_1 + C_1;

    TeorTable();

    FillDec(A1, n1);
    BubbleSort(A1, n1, &C1, &M1);
    FillRand(A1, n1);
    BubbleSort(A1, n1, &C2, &M2);
    FillInc(A1, n1);
    BubbleSort(A1, n1, &C3, &M3);

    ZnachTable(n1, T1, C1, M1, C2, M2, C3, M3);


    int n2 = 200;
    int A2[n2];

    int C_2 = (n2*n2 - n2) / 2;
    int M_2 = (3*(n2*n2 - n2)) / 4;
    int T2 = M_2 + C_2;

    // TeorTable();

    FillDec(A2, n2);
    BubbleSort(A2, n2, &C1, &M1);
    FillRand(A2, n2);
    BubbleSort(A2, n2, &C2, &M2);
    FillInc(A2, n2);
    BubbleSort(A2, n2, &C3, &M3);

    ZnachTable(n2, T2, C1, M1, C2, M2, C3, M3);


    int n3 = 300;
    int A3[n3];

    int C_3 = (n3*n3 - n3) / 2;
    int M_3 = (3*(n3*n3 - n3)) / 4;
    int T3 = M_3 + C_3;

    // TeorTable();

    FillDec(A3, n3);
    BubbleSort(A3, n3, &C1, &M1);
    FillRand(A3, n3);
    BubbleSort(A3, n3, &C2, &M2);
    FillInc(A3, n3);
    BubbleSort(A3, n3, &C3, &M3);

    ZnachTable(n3, T3, C1, M1, C2, M2, C3, M3);


    int n4 = 400;
    int A4[n4];

    int C_4 = (n4*n4 - n4) / 2;
    int M_4 = (3*(n4*n4 - n4)) / 4;
    int T4 = M_4 + C_4;

    // TeorTable();

    FillDec(A4, n4);
    BubbleSort(A4, n4, &C1, &M1);
    FillRand(A4, n4);
    BubbleSort(A4, n4, &C2, &M2);
    FillInc(A4, n4);
    BubbleSort(A4, n4, &C3, &M3);

    ZnachTable(n4, T4, C1, M1, C2, M2, C3, M3);


    int n5 = 500;
    int A5[n5];

    int C_5 = (n5*n5 - n5) / 2;
    int M_5 = (3*(n5*n5 - n5)) / 4;
    int T5 = M_5 + C_5;

    // TeorTable();

    FillDec(A5, n5);
    BubbleSort(A5, n5, &C1, &M1);
    FillRand(A5, n5);
    BubbleSort(A5, n5, &C2, &M2);
    FillInc(A5, n5);
    BubbleSort(A5, n5, &C3, &M3);

    ZnachTable(n5, T5, C1, M1, C2, M2, C3, M3);
}