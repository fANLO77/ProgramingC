#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void InsertSort(int A[], int n, int *M, int *C) {
    (*M) = 0;
    (*C) = 0;
    for (int i = 1; i < n; i++) {
        (*M)++;
        int t = A[i];
        int j = i - 1;
        while (j >= 0 && ((*C)++, t < A[j])) {
            (*M)++;
            A[j + 1] = A[j];
            j = j - 1;
        }
        (*M)++;
        A[j + 1] = t;
    }
}

void ShellSort(int A[], int n, int *M, int *C) {
    int k, i, j, temp;
    for (k = n/2; k > 0; k /= 2) {
        for (i = k; i < n; i++) {
            temp = A[i];
            (*M)++;
            for (j = i; j >= k && A[j - k] > temp; j -= k) {
                A[j] = A[j - k];
                (*M)++;
                (*C)++;
            }
            A[j] = temp;
            (*M)++;
        }
    }
}

void TeorTable() {
    printf("%-5s | %-10s | %-10s | %-20s\n", "", "ShellSort", "InsertrSort", "Knut");
    printf("%-5s | %-10s | %-10s | %-20s \n", "N", "M+C", "M+C", "Steps");
    printf("---------------------------------------------------------------------\n");
}

void ZnachTable(int n, int T1, int T2, int steps[], int stepCount) {
    printf("%-5d | %-10d | %-10d | ", n, T1, T2);
    for (int i = 0; i < stepCount; i++) {
        printf("%d ", steps[i]);
    }
    printf("\n");
    printf("---------------------------------------------------------------------\n");
}

void Knut(int n, int *steps, int *stepsCount) {
    int h = 1;
    *stepsCount = 0;
    int count = 0;
    while(count < (int)(log2(n)) - 1) {
        steps[(*stepsCount)++] = h;
        h = 2 * h + 1;
        count++;
    }
}

int main () {
    int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    TeorTable();

    for (int k = 0; k < num_sizes; k++) {
        int n = sizes[k];
        int *A = (int *)malloc(n * sizeof(int));
        FillRand(A, n);

        int M_shell = 0, C_shell = 0;
        int M_insert = 0, C_insert = 0;

        int *A_shell = (int *)malloc(n * sizeof(int));
        int *A_insert = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            A_shell[i] = A[i];
            A_insert[i] = A[i];
        }

        ShellSort(A_shell, n, &M_shell, &C_shell);
        InsertSort(A_insert, n, &M_insert, &C_insert);

        int steps[100];
        int stepCount;
        Knut(n, steps, &stepCount);

        int T_Shell = C_shell + M_shell;
        int T_Insert =  C_insert + M_insert;

        ZnachTable(n, T_Shell, T_Insert, steps, stepCount);

        free(A);
        free(A_shell);
        free(A_insert);
    }
}